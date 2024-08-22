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

// �ȽϺ���������qsort����
int compare(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

int main() {
    int n, m, k;
    int* apples[MAX_TREES + 1];  // ���ڴ洢ÿ�����ϵ�ƻ���߶ȵ�����ָ��
    int count[MAX_TREES + 1] = { 0 }; // ��¼ÿ������ƻ������
    int max_apples_count = 0;

    // ��ȡ����
    scanf("%d %d %d", &n, &m, &k);

    // ��̬��������ռ�
    for (int i = 0; i <= n; i++) {
        apples[i] = (int*)malloc(MAX_APPLES * sizeof(int));
        if (apples[i] == NULL) {
            printf("�ڴ����ʧ��\n");
            return 1;
        }
    }

    // ��ÿ������ƻ���߶ȷ���
    for (int i = 0; i < m; i++) {
        int posi, hi;
        scanf("%d %d", &posi, &hi);
        apples[posi][count[posi]++] = hi;
    }

    // ��ÿ�������д���
    for (int i = 1; i <= n; i++) {
        if (count[i] == 0) continue;

        // ��ƻ���߶�����
        qsort(apples[i], count[i], sizeof(int), compare);

        int current_max = 0;
        int left = 0;

        // ʹ�û�������Ѱ�����䳤��Ϊk�����ƻ����
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

    // ������
    printf("%d\n", max_apples_count);

    // �ͷŶ�̬������ڴ�
    for (int i = 0; i <= n; i++) {
        free(apples[i]);
    }

    return 0;
}
