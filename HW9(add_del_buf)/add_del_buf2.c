#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[100];
    struct Node *front;
    struct Node *next;
};

// 建立新節點
struct Node *getBufNode(void) {
    struct Node* buf = (struct Node *)malloc(sizeof(struct Node));
    if (buf != NULL) {
        buf->front = NULL;
        buf->next = NULL;
        memset(buf->data, 0, sizeof(buf->data));
    }
    return buf;
}

// 加入字元
struct Node *addBuf(struct Node *buf, int *n, char c) {
    if (*n >= 100) {
        if (buf->next == NULL) {
            buf->next = getBufNode();
            buf->next->front = buf;
        }
        *n = 0;
        return addBuf(buf->next, n, c);
    }
    buf->data[(*n)++] = c;
    return buf;
}

// 向前移動 index
struct Node *decBufIndex(struct Node *buf, int *k) {
    if (*k > 0) {
        (*k)--;
        return buf;
    }
    if (buf->front != NULL) {
        buf = buf->front;
        *k = 99;
    }
    return buf;
}

// 刪除目前位置的字元
// 刪除目前位置的字元，並跨節點左移補位
struct Node *delBufChar(struct Node *buf, int *k) {
    struct Node *cur = buf;
    int pos = *k;

    while (cur != NULL) {
        // 將後一格補到前一格
        for (int i = pos; i < 99; i++) {
            cur->data[i] = cur->data[i + 1];
        }

        // 如果有下一節點，把它的第0個字元搬過來
        if (cur->next != NULL && cur->next->data[0] != '\0') {
            cur->data[99] = cur->next->data[0]; // 搬過來
            // 接著從下一節點開始左移補
            cur = cur->next;
            pos = 0;
        } else {
            // 最後一節點時，將最後一格設為 \0
            cur->data[99] = '\0';
            break;
        }
    }

    return buf;
}


// 印出整個 buffer
void printBuffer(struct Node *buf) {
    while (buf != NULL) {
        for (int i = 0; i < 100 && buf->data[i] != '\0'; i++)
            putchar(buf->data[i]);
        buf = buf->next;
    }
    putchar('\n');
}

// 主程式
int main() {
    struct Node *head = getBufNode();
    struct Node *cur = head;
    int index = 0;
    char msg[300];
    int del_count;

    printf("請輸入一段字串（最多 300 字元）：\n");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    // 加入每個字元
    for (int i = 0; msg[i] != '\0'; i++) {
        cur = addBuf(cur, &index, msg[i]);
    }

    printf("\n原始內容：\n");
    printBuffer(head);

    // 使用者輸入要刪除的字元數
    printf("\n請輸入要刪除的字元數：");
    scanf("%d", &del_count);

    // 定位至最後有效字元
    while (cur->next != NULL && cur->next->data[0] != '\0')
        cur = cur->next;
    while (index > 0 && cur->data[index] == '\0')
        index--;
    if (cur->data[index] != '\0') index++;

    // 刪除
    for (int i = 0; i < del_count; i++) {
        if (index == 0 && cur->front != NULL) {
            cur = cur->front;
            index = 100;
        }
        cur = decBufIndex(cur, &index);
        cur = delBufChar(cur, &index);
    }

    printf("\n刪除後內容：\n");
    printBuffer(head);

    return 0;
}
