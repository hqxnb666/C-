#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
/*****声明订餐管理结构体*****/
typedef struct OrderingManagement {
    char number[10];        // 订餐编号
    char table[20];         // 桌号
    char date[10];          // 订餐日期
    char time[10];          // 订餐时间
    char name[4];           // 订餐人姓名
    char phonenumber[30];   // 订餐人电话
    char people[20];        // 用餐人数
} OrderingManagement;

#define N 10
OrderingManagement Ordering[N];

/*****声明单链表结构*****/
typedef struct Node {
    struct OrderingManagement data;
    struct Node* next;
} LNode;

/*****声明单链表指针*****/
typedef LNode* LinkList;

/*****定义单链表S*****/
LinkList S;

int COUNT = 0; // 单链表的数据个数，即订餐记录的个数
char filename[30];

/*****函数声明*****/
void create();      /*新建订餐管理程序*/
void load();        /*打开订餐管理程序，将文件中的数据导入到数组Ordering中*/
void display();     /*显示数组Ordering中的元素*/
void savefile();    /*将数组的数据写入文件，进行保存*/
void append();      /*在数组的结尾添加一条或多条记录*/
void modify();      /*按照桌号修改电话号码*/

void query();       /*查找记录*/
void query_date();  /*按照订餐日期查找记录*/
void query_table(); /*按照桌号查找记录*/
void del_record();  /*按照订餐编号删除记录*/
void sort();        /*排序记录*/
void sort_date();   /*按照订餐日期排序记录*/
void sort_table();  /*按照桌号排序记录*/
void clear_screen();/*清屏函数*/

/*****函数定义*****/
void clear_screen() {
    // 清屏函数
    printf("\033[H\033[J");
}

/*****新建订餐管理程序*****/
void create() {
    int num, i;
    OrderingManagement record;
    FILE* fp;      /*文件指针*/
    fp = fopen(filename, "wb");      /*以二进制只写方式打开文件*/
    if (fp == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    printf("请输入新建的记录个数：");
    scanf("%d", &num);
    for (i = 0; i < num; i++) {    /*将记录逐条写入文件*/
        printf("\n第%d条记录：", i + 1);
        printf("\n请输入订餐编号：");
        scanf("%s", record.number);
        printf("\n请输入桌号：");
        scanf("%s", record.table);
        printf("\n请输入订餐日期：");
        scanf("%s", record.date);
        printf("\n请输入订餐时间：");
        scanf("%s", record.time);
        printf("\n请输入订餐人姓名（不超过3个字符）：");
        scanf("%s", record.name);
        printf("\n请输入订餐人电话(不超过11个字符)：");
        scanf("%s", record.phonenumber);
        printf("\n请输入用餐人数：");
        scanf("%s", record.people);
        fwrite(&record, sizeof(record), 1, fp);     /*成块写入文件，一次写入一行记录*/
    }
    printf("\n订餐管理系统已新建完成!\n");
    fclose(fp);
}

/*****显示订餐管理信息*****/
void display() {
    int i;
    for (i = 0; i < COUNT; i++) {
        printf("订餐编号：%s\n", Ordering[i].number);
        printf("桌号：%s\n", Ordering[i].table);
        printf("订餐日期：%s\n", Ordering[i].date);
        printf("订餐时间：%s\n", Ordering[i].time);
        printf("订餐人姓名：%s\n", Ordering[i].name);
        printf("订餐人电话：%s\n", Ordering[i].phonenumber);
        printf("用餐人数：%s\n", Ordering[i].people);
    }
    getchar();
}

/*****保存文件*****/
void savefile() {
    int i;
    FILE* fp; /*文件指针*/
    fp = fopen(filename, "wb");      /*以二进制只写方式打开文件*/
    if (fp == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    for (i = 0; i < COUNT; i++) {    /*将记录逐条写入文件*/
        fwrite(&Ordering[i], sizeof(OrderingManagement), 1, fp);    /*成块写入文件，一次写入一行记录*/
    }
    printf("\n 订餐管理系统已保存!\n");
    fclose(fp);
}

/*****添加订餐信息*****/
/*****输入验证函数*****/
int is_valid_date(const char* date) {
    // 简单验证日期格式YYYY-MM-DD，实际可根据需要更复杂
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    return 1;
}

void append() {
    char ch;
    do {
        if (COUNT >= N) {
            printf("订餐记录已满，无法添加新记录。\n");
            return;
        }
        printf("输入订餐编号：");
        scanf("%s", Ordering[COUNT].number);
        printf("输入订餐人姓名：");
        scanf("%s", Ordering[COUNT].name);
        printf("输入订餐日期（格式YYYY-MM-DD）：");
        scanf("%s", Ordering[COUNT].date);
        if (!is_valid_date(Ordering[COUNT].date)) {
            printf("日期格式不合法！\n");
            continue;
        }
        printf("输入订餐时间（格式HH:MM）：");
        scanf("%s", Ordering[COUNT].time);
        printf("输入桌号：");
        scanf("%s", Ordering[COUNT].table);
        printf("输入订餐人电话：");
        scanf("%s", Ordering[COUNT].phonenumber);
        printf("输入用餐人数：");
        scanf("%s", Ordering[COUNT].people);
        COUNT++;
        printf("添加订餐信息成功！\n");
        printf("继续添加？ (Y/N): ");
        getchar();
        scanf("%c", &ch);
    } while (ch == 'Y' || ch == 'y');
}

/*****按订餐日期和桌号查询信息*****/
void query() {
    int choice;
    printf("\t*********1.按订餐日期查询*********\n");
    printf("\t*********2.按桌号查询*********\n");
    printf("\t*********3.返回主菜单*********\n");
    while (1) {
        scanf("%d", &choice);
        if (choice != 2 && choice != 1 && choice != 3)
            printf("输入有误，请按指示输入!\n");
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
        printf("\n请输入要查找的日期:");
        scanf("%s", date);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].date, date) == 0) { /*找到记录*/
                flag = 1;
                printf("\n该日期对应的记录为:\n");
                printf("订餐编号：%s\n", Ordering[i].number);
                printf("桌号：%s\n", Ordering[i].table);
                printf("订餐日期：%s\n", Ordering[i].date);
                printf("订餐时间：%s\n", Ordering[i].time);
                printf("订餐人姓名：%s\n", Ordering[i].name);
                printf("订餐人电话：%s\n", Ordering[i].phonenumber);
                printf("用餐人数：%s\n", Ordering[i].people);
            }
        if (flag == 0)
            printf("没有该日期的记录!\n");
        printf("\n继续查找记录吗? (Y/N):");
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
        printf("\n请输入要查找的桌号:");
        scanf("%s", table);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].table, table) == 0) { /*找到记录*/
                flag = 1;
                printf("\n该桌号对应的记录为:\n");
                printf("订餐编号：%s\n", Ordering[i].number);
                printf("桌号：%s\n", Ordering[i].table);
                printf("订餐日期：%s\n", Ordering[i].date);
                printf("订餐时间：%s\n", Ordering[i].time);
                printf("订餐人姓名：%s\n", Ordering[i].name);
                printf("订餐人电话：%s\n", Ordering[i].phonenumber);
                printf("用餐人数：%s\n", Ordering[i].people);
            }
        if (flag == 0)
            printf("没有该桌号的记录!\n");
        printf("\n继续查找记录吗? (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n') break;
    }
}

/*****修改订餐信息*****/
void modify() {
    char ch, tablenumber[10];
    int i, flag;
    printf("\n修改记录的电话号码\n");
    while (1) {
        flag = 0;
        printf("\n请输入桌号:");
        scanf("%s", tablenumber);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].table, tablenumber) == 0) { /*找到记录*/
                printf("\n原电话号码为：%s\n", Ordering[i].phonenumber);
                printf("请输入新的电话号码:");
                scanf("%s", Ordering[i].phonenumber);
                flag = 1;
            }
        if (flag == 0)
            printf("查无此桌号!\n");
        printf("\n继续修改记录吗? (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n') break;
    }
    printf("\n需要保存修改后的记录吗? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n修改后的记录没有保存到文件中!\n");
}

/*****删除订餐信息*****/
void del_record() {
    char ch, number[10];
    int i, j, flag;
    while (1) {
        flag = 0;
        printf("\n请输入要删除的订餐编号：");
        scanf("%s", number);
        for (i = 0; i < COUNT; i++)
            if (strcmp(Ordering[i].number, number) == 0) {   /*找到记录*/
                for (j = i; j < COUNT - 1; j++)   /*后一条记录覆盖前面的记录*/
                    Ordering[j] = Ordering[j + 1];
                COUNT--;        /*删除一条记录后，总数减1*/
                flag = 1;
                break;
            }
        if (flag == 0)
            printf("\n没有这个编号对应的记录!");

        printf("\n继续删除记录吗?  (Y/N):");
        getchar();
        scanf("%c", &ch);
        if (ch == 'N' || ch == 'n')
            break;
    }
    savefile();
}

/*****排序函数*****/
void sort() {
    int choice;
    printf("\t*********1.按订餐日期排序*********\n");
    printf("\t*********2.按桌号排序*********\n");
    printf("\t*********3.返回主菜单*********\n");
    while (1) {
        scanf("%d", &choice);
        if (choice != 2 && choice != 1 && choice != 3)
            printf("输入有误，请按指示输入!\n");
        else break;
    }
    switch (choice) {
    case 1: sort_date(); break;
    case 2: sort_table(); break;
    }
}

void sort_date() { /*选择排序，升序*/
    int i, j, min;
    char ch;
    OrderingManagement temp; /*用于交换的结构体变量，中间变量*/
    for (i = 0; i < COUNT; i++) {
        min = i;
        for (j = i + 1; j < COUNT; j++)
            if (strcmp(Ordering[j].date, Ordering[min].date) < 0)
                min = j;
        temp = Ordering[i];
        Ordering[i] = Ordering[min];
        Ordering[min] = temp;
    }
    printf("\n按照订餐日期排序后的结果为:\n");
    display();
    printf("\n需要保存排序后的记录吗? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n排序后的记录没有保存到文件中!\n");
}

void sort_table() { /*选择排序，升序*/
    int i, j, min;
    char ch;
    OrderingManagement temp; /*用于交换的结构体变量，中间变量*/
    for (i = 0; i < COUNT; i++) {
        min = i;
        for (j = i + 1; j < COUNT; j++)
            if (strcmp(Ordering[j].table, Ordering[min].table) < 0)
                min = j;
        temp = Ordering[i];
        Ordering[i] = Ordering[min];
        Ordering[min] = temp;
    }
    printf("\n按照桌号排序后的结果为:\n");
    display();
    printf("\n需要保存排序后的记录吗? (Y/N):");
    getchar();
    scanf("%c", &ch);
    if (ch == 'Y' || ch == 'y')
        savefile();
    else
        printf("\n排序后的记录没有保存到文件中!\n");
}

/*****打开文件*****/
void load() {
    int i = 0;
    FILE* fp;     /*文件指针*/
    if ((fp = fopen(filename, "rb")) == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }
    while (!feof(fp)) { /*文件没有读到末尾*/
        if (fread(&Ordering[i], sizeof(OrderingManagement), 1, fp) == 1)
            i++;
    }
    COUNT = i;
    printf("\n 订餐管理系统打开成功，共导入%d条记录。\n", COUNT);
    fclose(fp);
}

/*****查询菜单函数*****/
int Menu_Find() {
    int choose;
    clear_screen();
    printf("\n\n**************查找菜单**************\n");
    printf("\t 1.按订餐日期查找\n");
    printf("\t 2.按桌号查找\n");
    printf("\t 3.返回主菜单\n");
    printf("*****************Ordering Management*****************\n");
    printf("\n请输入选项：\n");
    scanf("%d", &choose);
    return choose;    //返回用户输入的选项    
}

/*****主菜单函数*****/
int Menu_Main() {
    int choose;
    clear_screen();
    printf("\n\n       欢迎使用订餐管理系统\n\n");
    printf("**************主菜单**************\n");
    printf("\t 0.新建订餐信息\n");
    printf("\t 1.显示订餐信息\n");
    printf("\t 2.添加订餐信息\n");
    printf("\t 3.查找订餐信息\n");
    printf("\t 4.更新订餐信息\n");
    printf("\t 5.删除订餐信息\n");
    printf("\t 6.排序订餐信息\n");
    printf("\t 7.打开订餐信息\n");
    printf("\t 8.保存订餐信息\n");
    printf("\t 9.退出订餐管理系统\n");
    printf("*****************Ordering Management*****************\n");
    printf("\n请输入选项：\n");
    scanf("%d", &choose);
    return choose;    //返回用户输入的选项    
}

int main() {
    int choose, choose_find;
    int flag;
    printf("请输入文件名：");
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
                default: printf("输入错误，请重新输入!\n");
                }
            }
            break;
        case 4: modify(); break;
        case 5: del_record(); break;
        case 6: sort(); break;
        case 7: load(); break;
        case 8: savefile(); break;
        case 9: exit(0); break;
        default: printf("输入错误，请重新输入!\n");
        }
        printf("按任意键返回主菜单...\n");
        getchar(); // 等待用户按键
        getchar(); // 清除输入缓冲区
    }
}
