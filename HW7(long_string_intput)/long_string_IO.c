#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data[100];
    struct Node *front;
    struct Node *next;
};

struct Node *getBufNode(void) {
    struct Node* buf = (struct Node *)malloc(sizeof(struct Node));
    if (buf != NULL) {
        buf->front = NULL;
        buf->next = NULL;
        memset(buf->data, 0, sizeof(buf->data));
    }
    return buf;
}

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

void printBuffer(struct Node *buf) {
    while (buf != NULL) {
        for (int i = 0; i < 100 && buf->data[i] != '\0'; i++)
            putchar(buf->data[i]);
        buf = buf->next;
    }
    putchar('\n');
}

int main() {
    struct Node *head = getBufNode();
    struct Node *cur = head;
    int index = 0;
    char msg[300];

    printf("請輸入: ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0;

    for (int i = 0; msg[i] != '\0'; i++) {
        cur = addBuf(cur, &index, msg[i]);
    }

    printf("結果: ");
    printBuffer(head);

    return 0;
}
