/*******************************************************************************
 * Simple FIFO Order Server Implementation with Queue and Worker Thread
 *
 * Description:
 *     A server implementation designed to process client requests in First In,
 *     First Out (FIFO) order. The server binds to the specified port number
 *     provided as a parameter upon launch. Additionally, it uses a request queue
 *     and spawns a worker thread to process the requests.
 *
 * Usage:
 *     <build directory>/server_qt <port_number>
 *
 * Parameters:
 *     port_number - The port number to bind the server to.
 *
 * Author:
 *     Renato Mancuso
 *
 * Affiliation:
 *     Boston University
 *
 * Creation Date:
 *     September 10, 2023
 *
 * Last Changes:
 *     September 21, 2024
 *
 * Notes:
 *     Ensure to have proper permissions and available port before running the
 *     server. The server relies on a FIFO mechanism to handle requests, thus
 *     guaranteeing the order of processing. For debugging or more details, refer
 *     to the accompanying documentation and logs.
 *
 *******************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

/* Needed for wait(...) */
#include <sys/types.h>
#include <sys/wait.h>

/* Needed for semaphores */
#include <semaphore.h>

/* Include struct definitions and other libraries that need to be
 * included by both client and server */
#include "common.h"

#define BACKLOG_COUNT 100
#define USAGE_STRING				\
	"Missing parameter. Exiting.\n"		\
	"Usage: %s <port_number>\n"

/* 4KB of stack for the worker thread */
#define STACK_SIZE (4096)

/* START - Variables needed to protect the shared queue. DO NOT TOUCH */
sem_t * queue_mutex;
sem_t * queue_notify;
/* END - Variables needed to protect the shared queue. DO NOT TOUCH */

/* Max number of requests that can be queued */
#define QUEUE_SIZE 500

struct queue {
    struct request requests[QUEUE_SIZE]; 
    int head;    
    int tail;    
    int size;   
};

struct worker_params {
    struct queue *the_queue;  
    int conn_socket;          
};

/* Macro wrapper for formatting timestamp */
#define FORMAT_TIMESTAMP(ts, buffer, size) \
    snprintf(buffer, size, "%.6f", (double)(ts.tv_sec) + (double)(ts.tv_nsec)/1e9)

/* Function prototypes */
int add_to_queue(struct request to_add, struct queue * the_queue);
struct request get_from_queue(struct queue * the_queue);
void dump_queue_status(struct queue * the_queue);
void *worker_main(void *arg);
uint64_t busywait_timespec(struct timespec delay);

/* Main logic of the worker thread (defined later) */

/* Function to add a new request to the queue */
int add_to_queue(struct request to_add, struct queue *the_queue)
{
    int retval = 0;
    /* QUEUE PROTECTION INTRO START --- DO NOT TOUCH */
    sem_wait(queue_mutex);
    /* QUEUE PROTECTION INTRO END --- DO NOT TOUCH */

    if (the_queue->size < QUEUE_SIZE) {
        the_queue->requests[the_queue->tail] = to_add;
        the_queue->tail = (the_queue->tail + 1) % QUEUE_SIZE;
        the_queue->size++;
        retval = 1; // 成功添加
    } else {
        // 队列已满，无法添加
        fprintf(stderr, "Queue is full. Dropping request ID: %lu\n", to_add.req_id);
        retval = 0;
    }

    /* QUEUE PROTECTION OUTRO START --- DO NOT TOUCH */
    sem_post(queue_mutex);
    sem_post(queue_notify);
    /* QUEUE PROTECTION OUTRO END --- DO NOT TOUCH */
    return retval;
}

/* Function to get a request from the queue */
struct request get_from_queue(struct queue *the_queue)
{
    struct request retval;
    /* QUEUE PROTECTION INTRO START --- DO NOT TOUCH */
    sem_wait(queue_notify);
    sem_wait(queue_mutex);
    /* QUEUE PROTECTION INTRO END --- DO NOT TOUCH */

    if (the_queue->size > 0) {
        retval = the_queue->requests[the_queue->head];
        the_queue->head = (the_queue->head + 1) % QUEUE_SIZE;
        the_queue->size--;
    } else {
       
        memset(&retval, 0, sizeof(struct request));
    }

    /* QUEUE PROTECTION OUTRO START --- DO NOT TOUCH */
    sem_post(queue_mutex);
    /* QUEUE PROTECTION OUTRO END --- DO NOT TOUCH */
    return retval;
}

/* Function to dump the current status of the queue */
void dump_queue_status(struct queue *the_queue)
{
    /* QUEUE PROTECTION INTRO START --- DO NOT TOUCH */
    sem_wait(queue_mutex);
    /* QUEUE PROTECTION INTRO END --- DO NOT TOUCH */

    printf("Q:[");
    for(int i = 0; i < the_queue->size; i++) {
        int index = (the_queue->head + i) % QUEUE_SIZE;
        printf("R%lu", the_queue->requests[index].req_id);
        if(i != the_queue->size -1 ) {
            printf(",");
        }
    }
    printf("]\n");

    /* QUEUE PROTECTION OUTRO START --- DO NOT TOUCH */
    sem_post(queue_mutex);
    /* QUEUE PROTECTION OUTRO END --- DO NOT TOUCH */
}


void *worker_main(void *arg)
{
    struct worker_params *params = (struct worker_params *)arg;
    struct queue *the_queue = params->the_queue;
    int conn_socket = params->conn_socket;

    while (1) {
        
        struct request req = get_from_queue(the_queue);

        
        busywait_timespec(req.req_length);

       
        struct response resp;
        resp.req_id = req.req_id;
        resp.reserved = 0;
        resp.ack = 1;

      
        if (send(conn_socket, &resp, sizeof(resp), 0) == -1) {
            perror("send failed");
            break;
        }

       
        char req_timestamp[32];
        FORMAT_TIMESTAMP(req.req_timestamp, req_timestamp, sizeof(req_timestamp));
        char req_length[32];
        FORMAT_TIMESTAMP(req.req_length, req_length, sizeof(req_length));

        printf("Processed Request ID: %lu at %s with Length: %s\n",
               resp.req_id, req_timestamp, req_length);

      
        dump_queue_status(the_queue);
    }

    close(conn_socket);
    free(params); 
    return NULL;
}

/* Function to handle client connection */
void handle_connection(int conn_socket)
{
    struct queue *the_queue = (struct queue *)malloc(sizeof(struct queue));
    if (the_queue == NULL) {
        ERROR_INFO();
        fprintf(stderr, "Failed to allocate memory for queue.\n");
        close(conn_socket);
        return;
    }
    the_queue->head = 0;
    the_queue->tail = 0;
    the_queue->size = 0;

   
    struct worker_params *params = (struct worker_params *)malloc(sizeof(struct worker_params));
    if (params == NULL) {
        ERROR_INFO();
        fprintf(stderr, "Failed to allocate memory for worker parameters.\n");
        free(the_queue);
        close(conn_socket);
        return;
    }
    params->the_queue = the_queue;
    params->conn_socket = conn_socket;

   
    pthread_t worker_thread_id;
    int pthread_ret = pthread_create(&worker_thread_id, NULL, worker_main, (void *)params);
    if (pthread_ret != 0) {
        ERROR_INFO();
        fprintf(stderr, "Failed to create worker thread: %s\n", strerror(pthread_ret));
        free(params);
        free(the_queue);
        close(conn_socket);
        return;
    }

   
    pthread_detach(worker_thread_id);

   
    struct request req;
    ssize_t in_bytes;

    while (1) {
        in_bytes = recv(conn_socket, &req, sizeof(req), 0);
        if (in_bytes <= 0) {
            if (in_bytes == 0) {
                printf("Client disconnected.\n");
            } else {
                perror("recv failed");
            }
            break;
        }

       
        clock_gettime(CLOCK_REALTIME, &req.req_timestamp);

       
        struct timespec req_length = {1, 0};
        req.req_length = req_length;

        // 添加请求到队列
        if (!add_to_queue(req, the_queue)) {
            fprintf(stderr, "Failed to add request ID: %lu to queue.\n", req.req_id);
           
        }
    }

 
    free(the_queue);
    close(conn_socket);
}

/* Main function */
int main (int argc, char ** argv) {
    int sockfd, retval, accepted, optval;
    in_port_t socket_port;
    struct sockaddr_in addr, client;
    struct in_addr any_address;
    socklen_t client_len;

  
    if (argc > 1) {
        socket_port = strtol(argv[1], NULL, 10);
        printf("INFO: setting server port as: %d\n", socket_port);
    } else {
        ERROR_INFO();
        fprintf(stderr, USAGE_STRING, argv[0]);
        return EXIT_FAILURE;
    }

    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        ERROR_INFO();
        perror("Unable to create socket");
        return EXIT_FAILURE;
    }

    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

    any_address.s_addr = htonl(INADDR_ANY);


    addr.sin_family = AF_INET;
    addr.sin_port = htons(socket_port);
    addr.sin_addr = any_address;


    retval = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

    if (retval < 0) {
        ERROR_INFO();
        perror("Unable to bind socket");
        close(sockfd);
        return EXIT_FAILURE;
    }


    retval = listen(sockfd, BACKLOG_COUNT);

    if (retval < 0) {
        ERROR_INFO();
        perror("Unable to listen on socket");
        close(sockfd);
        return EXIT_FAILURE;
    }

    queue_mutex = (sem_t *)malloc(sizeof(sem_t));
    queue_notify = (sem_t *)malloc(sizeof(sem_t));
    retval = sem_init(queue_mutex, 0, 1);
    if (retval < 0) {
        ERROR_INFO();
        perror("Unable to initialize queue mutex");
        free(queue_mutex);
        free(queue_notify);
        close(sockfd);
        return EXIT_FAILURE;
    }
    retval = sem_init(queue_notify, 0, 0);
    if (retval < 0) {
        ERROR_INFO();
        perror("Unable to initialize queue notify");
        sem_destroy(queue_mutex);
        free(queue_mutex);
        free(queue_notify);
        close(sockfd);
        return EXIT_FAILURE;
    }
   
    printf("INFO: Waiting for incoming connection...\n");
    client_len = sizeof(struct sockaddr_in);
    accepted = accept(sockfd, (struct sockaddr *)&client, &client_len);

    if (accepted == -1) {
        ERROR_INFO();
        perror("Unable to accept connections");
        sem_destroy(queue_mutex);
        sem_destroy(queue_notify);
        free(queue_mutex);
        free(queue_notify);
        close(sockfd);
        return EXIT_FAILURE;
    }

   
    handle_connection(accepted);

    sem_destroy(queue_mutex);
    sem_destroy(queue_notify);
    free(queue_mutex);
    free(queue_notify);

    close(sockfd);
    return EXIT_SUCCESS;
}
