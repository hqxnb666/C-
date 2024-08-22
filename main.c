#define _CRT_SECURE_NO_WARNINGS 1
//#include"BinarySearchTree.h"
//#include <iostream>
//using namespace std;
//int main()
//{
//	TestBSTree1();
//	return 0;
//}
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREES 1000
#define MAX_APPLES 100000

// 比较函数，用于qsort排序
int compare(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int main() {
    int n, m, k;
    int* apples[MAX_TREES + 1];  // 用于存储每棵树上的苹果高度的数组指针
    int count[MAX_TREES + 1] = { 0 }; // 记录每棵树的苹果数量
    int max_apples_count = 0;

    // 读取输入
    scanf("%d %d %d", &n, &m, &k);

    // 动态分配数组空间
    for (int i = 0; i <= n; i++) {
        apples[i] = (int*)malloc(MAX_APPLES * sizeof(int));
        if (apples[i] == NULL) {
            printf("内存分配失败\n");
            return 1;
        }
    }

    // 将每棵树的苹果高度分类
    for (int i = 0; i < m; i++) {
        int posi, hi;
        scanf("%d %d", &posi, &hi);
        apples[posi][count[posi]++] = hi;
    }

    // 对每棵树进行处理
    for (int i = 1; i <= n; i++) {
        if (count[i] == 0) continue;

        // 对苹果高度排序
        qsort(apples[i], count[i], sizeof(int), compare);

        int current_max = 0;
        int left = 0;

        // 使用滑动窗口寻找区间长度为k的最多苹果数
        for (int right = 0; right < count[i]; right++) {
            while (apples[i][right] - apples[i][left] > k) {
                left++;
            }
            int current_apples = right - left + 1;
            if (current_apples > current_max) {
                current_max = current_apples;
            }
        }

        if (current_max > max_apples_count) {
            max_apples_count = current_max;
        }
    }

    // 输出结果
    printf("%d\n", max_apples_count);

    // 释放动态分配的内存
    for (int i = 0; i <= n; i++) {
        free(apples[i]);
    }

    return 0;
}
