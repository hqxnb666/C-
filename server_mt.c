/*******************************************************************************
 * Simple FIFO Order Server Implementation with Worker Thread
 *
 * Description:
 *     A server implementation designed to process client requests in First In,
 *     First Out (FIFO) order. The server binds to the specified port number
 *     provided as a parameter upon launch. Additionally, it spawns a worker
 *     thread that periodically prints status messages.
 *
 * Usage:
 *     <build directory>/server_mt <port_number>
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

/* Include struct definitions and other libraries that need to be
 * included by both client and server */
#include "common.h"

#define BACKLOG_COUNT 100
#define USAGE_STRING				\
	"Missing parameter. Exiting.\n"		\
	"Usage: %s <port_number>\n"

/* 4KB of stack for the worker thread */
#define STACK_SIZE (4096)

/* Macro wrapper for formatting timestamp */
#define FORMAT_TIMESTAMP(ts, buffer, size) \
    snprintf(buffer, size, "%.6f", (double)(ts.tv_sec) + (double)(ts.tv_nsec)/1e9)

/* Function prototypes */
void *worker_main(void *arg);
void handle_connection(int conn_socket);
void busywait_one_second();

int main (int argc, char ** argv) {
	int sockfd, retval, accepted, optval;
	in_port_t socket_port;
	struct sockaddr_in addr, client;
	struct in_addr any_address;
	socklen_t client_len;

	/* Get port to bind our socket to */
	if (argc > 1) {
		socket_port = strtol(argv[1], NULL, 10);
		printf("INFO: setting server port as: %d\n", socket_port);
	} else {
		ERROR_INFO();
		fprintf(stderr, USAGE_STRING, argv[0]);
		return EXIT_FAILURE;
	}

	/* Now onward to create the right type of socket */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) {
		ERROR_INFO();
		perror("Unable to create socket");
		return EXIT_FAILURE;
	}

	/* Before moving forward, set socket to reuse address */
	optval = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(optval));

	/* Convert INADDR_ANY into network byte order */
	any_address.s_addr = htonl(INADDR_ANY);

	/* Time to bind the socket to the right port  */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(socket_port);
	addr.sin_addr = any_address;

	/* Attempt to bind the socket with the given parameters */
	retval = bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	if (retval < 0) {
		ERROR_INFO();
		perror("Unable to bind socket");
		close(sockfd);
		return EXIT_FAILURE;
	}

	/* Let us now proceed to set the server to listen on the selected port */
	retval = listen(sockfd, BACKLOG_COUNT);

	if (retval < 0) {
		ERROR_INFO();
		perror("Unable to listen on socket");
		close(sockfd);
		return EXIT_FAILURE;
	}

	/* Ready to accept connections! */
	printf("INFO: Waiting for incoming connection...\n");
	client_len = sizeof(struct sockaddr_in);
	accepted = accept(sockfd, (struct sockaddr *)&client, &client_len);

	if (accepted == -1) {
		ERROR_INFO();
		perror("Unable to accept connections");
		close(sockfd);
		return EXIT_FAILURE;
	}

	/* Ready to handle the new connection with the client. */
	handle_connection(accepted);

	close(sockfd);
	return EXIT_SUCCESS;
}


void *worker_main(void *arg) {
	char timestamp[32];
	struct timespec ts;

	
	clock_gettime(CLOCK_REALTIME, &ts);
	FORMAT_TIMESTAMP(ts, timestamp, sizeof(timestamp));

	printf("[#WORKER#] %s Worker Thread Alive!\n", timestamp);


	while (1) {
	
		busywait_one_second();

	
		clock_gettime(CLOCK_REALTIME, &ts);
		FORMAT_TIMESTAMP(ts, timestamp, sizeof(timestamp));

		
		printf("[#WORKER#] %s Still Alive!\n", timestamp);

		
		sleep(1);
	}

	return NULL;
}


void busywait_one_second() {
	struct timespec start, current;
	clock_gettime(CLOCK_MONOTONIC, &start);
	while (1) {
		clock_gettime(CLOCK_MONOTONIC, &current);
		double elapsed = (current.tv_sec - start.tv_sec) + 
						 (current.tv_nsec - start.tv_nsec) / 1e9;
		if (elapsed >= 1.0) {
			break;
		}
	}
}


void handle_connection(int conn_socket)
{
	pthread_t worker_thread_id;
	int pthread_ret;

	// 创建工作线程
	pthread_ret = pthread_create(&worker_thread_id, NULL, worker_main, NULL);
	if (pthread_ret != 0) {
		ERROR_INFO();
		fprintf(stderr, "Failed to create worker thread: %s\n", strerror(pthread_ret));
		
	} else {
	
		pthread_detach(worker_thread_id);
	}

	
	struct request req;
	struct response resp;
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

	
		char req_timestamp[32];
		FORMAT_TIMESTAMP(req.req_timestamp, req_timestamp, sizeof(req_timestamp));

		
		char req_length[32];
		FORMAT_TIMESTAMP(req.req_length, req_length, sizeof(req_length));

		
		printf("Received Request ID: %lu, Timestamp: %s, Length: %s\n",
			   req.req_id, req_timestamp, req_length);

		
		busywait_one_second();

		// 准备响应
		resp.req_id = req.req_id;
		resp.reserved = 0;
		resp.ack = 1;

	
		if (send(conn_socket, &resp, sizeof(resp), 0) == -1) {
			perror("send failed");
			break;
		}

		// 输出完整报告
		printf("Processed Request ID: %lu at %s with Length: %s\n",
			   resp.req_id, req_timestamp, req_length);
	}

	close(conn_socket);
}
