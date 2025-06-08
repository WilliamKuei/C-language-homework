#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義 DNode：具有 buffer、前後指標，透過 union 支援線性存取
union DNode {
    struct {
        char buf[100];
        char *nptr;
        char *fptr;
    } part;
    char data[104];
};

// 建立新節點
union DNode *getNode(void) {
    union DNode *tmp;
    tmp = (union DNode *)malloc(sizeof(union DNode));
    if (tmp != NULL) {
        tmp->part.nptr = NULL;
        tmp->part.fptr = NULL;
        memset(tmp->part.buf, 0, sizeof(tmp->part.buf));
    }
    return tmp;
}

// 加入一個字元到 buffer 中
union DNode *addBuf(union DNode *buf, int *n, char c) {
    int i = *n;
    buf->data[i++] = c;
    if (i == 100) {
        buf->part.nptr = (char *)getNode();
        ((union DNode *)buf->part.nptr)->part.fptr = (char *)buf;
        buf = (union DNode *)buf->part.nptr;
        i = 0;
    }
    *n = i;
    return buf;
}

// 刪除一個字元（往前移並清除）
union DNode *delBuf(union DNode *buf, int *n) {
    int i = *n;
    if (i == 0) {
        if (buf->part.fptr != NULL) {
            buf = (union DNode *)buf->part.fptr;
            i = 99;
        }
    } else {
        i--;
    }
    buf->data[i] = '\0';
    *n = i;
    return buf;
}

// 印出所有 buffer 中的資料
void printBuf(union DNode *buf) {
    int i = 0;
    char c;
    while (buf != NULL) {
        while (i < 100 && (c = buf->data[i]) != '\0') {
            putchar(c);
            i++;
        }
        if (i < 100)
            break;
        buf = (union DNode *)buf->part.nptr;
        i = 0;
    }
    putchar('\n');
}

// 主程式
int main() {
    union DNode *head, *buf;
    head = buf = getNode();
    int i = 0;
    char c;

    printf("請輸入字元（按 Enter 結束輸入）：\n");
    while ((c = getchar()) != '\n') {
        buf = addBuf(buf, &i, c);
    }

    printf("\n原始內容：\n");
    printBuf(head);

    // 重新定位 buf 和 i 到最後有效字元
    buf = head;
    i = 0;
    while (buf->part.nptr != NULL && ((union DNode *)buf->part.nptr)->data[0] != '\0') {
        buf = (union DNode *)buf->part.nptr;
    }
    while (i < 100 && buf->data[i] != '\0') {
        i++;
    }

    // 開始刪除
    int del_count;
    printf("\n請輸入要刪除的字元數：");
    scanf("%d", &del_count);
    for (int j = 0; j < del_count; j++) {
        buf = delBuf(buf, &i);
    }

    printf("\n刪除後內容：\n");
    printBuf(head);

    return 0;
}
