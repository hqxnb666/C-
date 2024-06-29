#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
/*****�������͹���ṹ��*****/
typedef struct OrderingManagement {
    char number[10];        // ���ͱ��
    char table[20];         // ����
    char date[10];          // ��������
    char time[10];          // ����ʱ��
    char name[4];           // ����������
    char phonenumber[30];   // �����˵绰
    char people[20];        // �ò�����
} OrderingManagement;

#define N 10
OrderingManagement Ordering[N];

/*****����������ṹ*****/
typedef struct Node {
    struct OrderingManagement data;
    struct Node* next;
} LNode;

/*****����������ָ��*****/
typedef LNode* LinkList;

/*****���嵥����S*****/
LinkList S;

int COUNT = 0; // ����������ݸ����������ͼ�¼�ĸ���
char filename[30];

/*****��������*****/
void create();      /*�½����͹������*/
void load();        /*�򿪶��͹�����򣬽��ļ��е����ݵ��뵽����Ordering��*/
void display();     /*��ʾ����Ordering�е�Ԫ��*/
void savefile();    /*�����������д���ļ������б���*/
void append();      /*������Ľ�β���һ���������¼*/
void modify();      /*���������޸ĵ绰����*/

void query();       /*���Ҽ�¼*/
void query_date();  /*���ն������ڲ��Ҽ�¼*/
void query_table(); /*�������Ų��Ҽ�¼*/
void del_record();  /*���ն��ͱ��ɾ����¼*/
void sort();        /*�����¼*/
void sort_date();   /*���ն������������¼*/
void sort_table();  /*�������������¼*/
void clear_screen();/*��������*/

/*****��������*****/
void clear_screen() {
    // ��������
    printf("\033[H\033[J");
}

/*****�½����͹������*****/
void create() {
    int num, i;
    OrderingManagement record;
    FILE* fp;      /*�ļ�ָ��*/
    fp = fopen(filename, "wb");      /*�Զ�����ֻд��ʽ���ļ�*/
    if (fp == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    printf("�������½��ļ�¼������");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {    /*����¼����д���ļ�*/
        printf("\n��%d����¼��", i + 1);
        printf("\n�����붩�ͱ�ţ�");
        scanf("%s", record.number);
        printf("\n���������ţ�");
        scanf("%s", record.table);
        printf("\n�����붩�����ڣ�");
        scanf("%s", record.date);
        printf("\n�����붩��ʱ�䣺");
        scanf("%s", record.time);
        printf("\n�����붩����������������3���ַ�����");
        scanf("%s", record.name);
        printf("\n�����붩���˵绰(������11���ַ�)��");
        scanf("%s", record.phonenumber);
        printf("\n�������ò�������");
        scanf("%s", record.people);
        fwrite(&record, sizeof(record), 1, fp);     /*�ɿ�д���ļ���һ��д��һ�м�¼*/
    }
    printf("\n���͹���ϵͳ���½����!\n");
    fclose(fp);
}

/*****��ʾ���͹�����Ϣ*****/
void display() {
    int i;
    for (i = 0; i < COUNT; i++) {
        printf("���ͱ�ţ�%s\n", Ordering[i].number);
        printf("���ţ�%s\n", Ordering[i].table);
        printf("�������ڣ�%s\n", Ordering[i].date);
        printf("����ʱ�䣺%s\n", Ordering[i].time);
        printf("������������%s\n", Ordering[i].name);
        printf("�����˵绰��%s\n", Ordering[i].phonenumber);
        printf("�ò�������%s\n", Ordering[i].people);
    }
    getchar();
}

/*****�����ļ�*****/
void savefile() {
    int i;
    FILE* fp; /*�ļ�ָ��*/
    fp = fopen(filename, "wb");      /*�Զ�����ֻд��ʽ���ļ�*/
    if (fp == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    for (i = 0; i < COUNT; i++) {    /*����¼����д���ļ�*/
        fwrite(&Ordering[i], sizeof(OrderingManagement), 1, fp);    /*�ɿ�д���ļ���һ��д��һ�м�¼*/
    }
    printf("\n ���͹���ϵͳ�ѱ���!\n");
    fclose(fp);
}

/*****��Ӷ�����Ϣ*****/
/*****������֤����*****/
int is_valid_date(const char* date) {
    // ����֤���ڸ�ʽYYYY-MM-DD��ʵ�ʿɸ�����Ҫ������
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    return 1;
}

void append() {
    char ch;
    do {
        if (COUNT >= N) {
            printf("���ͼ�¼�������޷�����¼�¼��\n");
            return;
        }
        printf("���붩�ͱ�ţ�");
        scanf("%s", Ordering[COUNT].number);
        printf("���붩����������");
        scanf("%s", Ordering[COUNT].name);
        printf("���붩�����ڣ���ʽYYYY-MM-DD����");
        scanf("%s", Ordering[COUNT].date);
        if (!is_valid_date(Ordering[COUNT].date)) {
            printf("���ڸ�ʽ���Ϸ���\n");
            continue;
        }
        printf("���붩��ʱ�䣨��ʽHH:MM����");
        scanf("%s", Ordering[COUNT].time);
        printf("�������ţ�");
        scanf("%s", Ordering[COUNT].table);
        printf("���붩���˵绰��");
        scanf("%s", Ordering[COUNT].phonenumber);
        printf("�����ò�������");
        scanf("%s", Ordering[COUNT].people);
        COUNT++;
        printf("��Ӷ�����Ϣ�ɹ���\n");
        printf("������ӣ� (Y/N): ");
        getchar();
        scanf("%c", &ch);
    } while (ch == 'Y' || ch == 'y');
}

/*****���������ں����Ų�ѯ��Ϣ*****/
void query() {
    int choice;
    printf("\t*********1.���������ڲ�ѯ*********\n");
    printf("\t*********2.�����Ų�ѯ*********\n");
    printf("\t*********3.�������˵�*********\n");
    while (1) {
        scanf("%d", &choice);
        if (choice != 2 && choice != 1 && choice != 3)
            printf("���������밴ָʾ����!\n");
        else break;
    }
    switch (choice) {
    case 1: query_date(); break;
    case 2: query_table(); break;
    }
}

void query_date() {
    char ch, date[15];
    int i, flag;
    while (1) {
        flag = 0;
        printf("\n������Ҫ���ҵ�����:");
        scanf("%s", date);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].date, date) == 0) { /*�ҵ���¼*/
                flag = 1;
                printf("\n�����ڶ�Ӧ�ļ�¼Ϊ:\n");
                printf("���ͱ�ţ�%s\n", Ordering[i].number);
                printf("���ţ�%s\n", Ordering[i].table);
                printf("�������ڣ�%s\n", Ordering[i].date);
                printf("����ʱ�䣺%s\n", Ordering[i].time);
                printf("������������%s\n", Ordering[i].name);
                printf("�����˵绰��%s\n", Ordering[i].phonenumber);
                printf("�ò�������%s\n", Ordering[i].people);
            }
        if (flag == 0)
            printf("û�и����ڵļ�¼!\n");
        printf("\n�������Ҽ�¼��? (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n')
            break;
    }
}

void query_table() {
    char ch, table[10];
    int i, flag;
    while (1) {
        flag = 0;
        printf("\n������Ҫ���ҵ�����:");
        scanf("%s", table);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].table, table) == 0) { /*�ҵ���¼*/
                flag = 1;
                printf("\n�����Ŷ�Ӧ�ļ�¼Ϊ:\n");
                printf("���ͱ�ţ�%s\n", Ordering[i].number);
                printf("���ţ�%s\n", Ordering[i].table);
                printf("�������ڣ�%s\n", Ordering[i].date);
                printf("����ʱ�䣺%s\n", Ordering[i].time);
                printf("������������%s\n", Ordering[i].name);
                printf("�����˵绰��%s\n", Ordering[i].phonenumber);
                printf("�ò�������%s\n", Ordering[i].people);
            }
        if (flag == 0)
            printf("û�и����ŵļ�¼!\n");
        printf("\n�������Ҽ�¼��? (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n') break;
    }
}

/*****�޸Ķ�����Ϣ*****/
void modify() {
    char ch, tablenumber[10];
    int i, flag;
    printf("\n�޸ļ�¼�ĵ绰����\n");
    while (1) {
        flag = 0;
        printf("\n����������:");
        scanf("%s", tablenumber);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].table, tablenumber) == 0) { /*�ҵ���¼*/
                printf("\nԭ�绰����Ϊ��%s\n", Ordering[i].phonenumber);
                printf("�������µĵ绰����:");
                scanf("%s", Ordering[i].phonenumber);
                flag = 1;
            }
        if (flag == 0)
            printf("���޴�����!\n");
        printf("\n�����޸ļ�¼��? (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n') break;
    }
    printf("\n��Ҫ�����޸ĺ�ļ�¼��? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n�޸ĺ�ļ�¼û�б��浽�ļ���!\n");
}

/*****ɾ��������Ϣ*****/
void del_record() {
    char ch, number[10];
    int i, j, flag;
    while (1) {
        flag = 0;
        printf("\n������Ҫɾ���Ķ��ͱ�ţ�");
        scanf("%s", number);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].number, number) == 0) {   /*�ҵ���¼*/
                for (j = i; j < COUNT - 1; j++)   /*��һ����¼����ǰ��ļ�¼*/
                    Ordering[j] = Ordering[j + 1];
                COUNT--;        /*ɾ��һ����¼��������1*/
                flag = 1;
                break;
            }
        if (flag == 0)
            printf("\nû�������Ŷ�Ӧ�ļ�¼!");

        printf("\n����ɾ����¼��?  (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n')
            break;
    }
    savefile();
}

/*****������*****/
void sort() {
    int choice;
    printf("\t*********1.��������������*********\n");
    printf("\t*********2.����������*********\n");
    printf("\t*********3.�������˵�*********\n");
    while (1) {
        scanf("%d", &choice);
        if (choice != 2 && choice != 1 && choice != 3)
            printf("���������밴ָʾ����!\n");
        else break;
    }
    switch (choice) {
    case 1: sort_date(); break;
    case 2: sort_table(); break;
    }
}

void sort_date() { /*ѡ����������*/
    int i, j, min;
    char ch;
    OrderingManagement temp; /*���ڽ����Ľṹ��������м����*/
    for (i = 0; i < COUNT; i++) {
        min = i;
        for (j = i + 1; j < COUNT; j++)
            if (strcmp(Ordering[j].date, Ordering[min].date) < 0)
                min = j;
        temp = Ordering[i];
        Ordering[i] = Ordering[min];
        Ordering[min] = temp;
    }
    printf("\n���ն������������Ľ��Ϊ:\n");
    display();
    printf("\n��Ҫ���������ļ�¼��? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n�����ļ�¼û�б��浽�ļ���!\n");
}

void sort_table() { /*ѡ����������*/
    int i, j, min;
    char ch;
    OrderingManagement temp; /*���ڽ����Ľṹ��������м����*/
    for (i = 0; i < COUNT; i++) {
        min = i;
        for (j = i + 1; j < COUNT; j++)
            if (strcmp(Ordering[j].table, Ordering[min].table) < 0)
                min = j;
        temp = Ordering[i];
        Ordering[i] = Ordering[min];
        Ordering[min] = temp;
    }
    printf("\n�������������Ľ��Ϊ:\n");
    display();
    printf("\n��Ҫ���������ļ�¼��? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n�����ļ�¼û�б��浽�ļ���!\n");
}

/*****���ļ�*****/
void load() {
    int i = 0;
    FILE* fp;     /*�ļ�ָ��*/
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    while (!feof(fp)) { /*�ļ�û�ж���ĩβ*/
        if (fread(&Ordering[i], sizeof(OrderingManagement), 1, fp) == 1)
            i++;
    }
    COUNT = i;
    printf("\n ���͹���ϵͳ�򿪳ɹ���������%d����¼��\n", COUNT);
    fclose(fp);
}

/*****��ѯ�˵�����*****/
int Menu_Find() {
    int choose;
    clear_screen();
    printf("\n\n**************���Ҳ˵�**************\n");
    printf("\t 1.���������ڲ���\n");
    printf("\t 2.�����Ų���\n");
    printf("\t 3.�������˵�\n");
    printf("*****************Ordering Management*****************\n");
    printf("\n������ѡ�\n");
    scanf("%d", &choose);
    return choose;    //�����û������ѡ��    
}

/*****���˵�����*****/
int Menu_Main() {
    int choose;
    clear_screen();
    printf("\n\n       ��ӭʹ�ö��͹���ϵͳ\n\n");
    printf("**************���˵�**************\n");
    printf("\t 0.�½�������Ϣ\n");
    printf("\t 1.��ʾ������Ϣ\n");
    printf("\t 2.��Ӷ�����Ϣ\n");
    printf("\t 3.���Ҷ�����Ϣ\n");
    printf("\t 4.���¶�����Ϣ\n");
    printf("\t 5.ɾ��������Ϣ\n");
    printf("\t 6.���򶩲���Ϣ\n");
    printf("\t 7.�򿪶�����Ϣ\n");
    printf("\t 8.���涩����Ϣ\n");
    printf("\t 9.�˳����͹���ϵͳ\n");
    printf("*****************Ordering Management*****************\n");
    printf("\n������ѡ�\n");
    scanf("%d", &choose);
    return choose;    //�����û������ѡ��    
}

int main() {
    int choose, choose_find;
    int flag;
    printf("�������ļ�����");
    scanf("%s", filename);
    while (1) {
        flag = 1;
        choose = Menu_Main();
        switch (choose) {
        case 0: create(); break;
        case 1: display(); break;
        case 2: append(); break;
        case 3:
            while (flag) {
                choose_find = Menu_Find();
                switch (choose_find) {
                case 1: query_date(); break;
                case 2: query_table(); break;
                case 3: flag = 0; break;
                default: printf("�����������������!\n");
                }
            }
            break;
        case 4: modify(); break;
        case 5: del_record(); break;
        case 6: sort(); break;
        case 7: load(); break;
        case 8: savefile(); break;
        case 9: exit(0); break;
        default: printf("�����������������!\n");
        }
        printf("��������������˵�...\n");
        getchar(); // �ȴ��û�����
        getchar(); // ������뻺����
    }
}
