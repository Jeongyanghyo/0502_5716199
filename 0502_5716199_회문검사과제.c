#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_QUEUE_SIZE 100

typedef char element;
typedef char element1;

// 스택
typedef struct {
    element data[MAX_SIZE];
    int top;
} Stack;

// 큐
typedef struct {
    element1 data[MAX_SIZE];
    int front, rear;
} Queue;

// 스택 함수
void init_stack(Stack* sptr) {
    sptr->top = -1;
}

int is_emptyStack(Stack* sptr) {
    return sptr->top == -1;
}

int is_fullStack(Stack* sptr) {
    return sptr->top == MAX_SIZE - 1;
}

void push(Stack* sptr, element item) {
    if (is_fullStack(sptr)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    else {
        sptr->top = sptr->top + 1;
        sptr->data[sptr->top] = item;
    }
}

element pop(Stack* sptr) {

    if (is_emptyStack(sptr)) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    else {

        return sptr->data[(sptr->top)--];
    }
}

// 큐 함수

void error(char* message) {
    fprintf(stderr, "%s", message);
    return -1;
}

void init_queue(Queue* q) {
    q->front = q->rear = 0;
}

int is_empty(Queue* q) {
    return q->front == q->rear;
}

int is_full(Queue* q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

void enqueue(Queue* q, element1 item) {
    if (is_full(q)) {
        error("큐가 포화상태입니다.\n");
    }
    else {
        q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
        q->data[q->rear] = item;
    }
}

element dequeue(Queue* q) {
    if (is_empty(q)) {
        error("현재 큐의 상태: 큐가 비어있습니다\n");
    }
    else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        return (q->data[q->front]);
    }
}

int is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

// 회문 검사 함수
int is_palindrome(char* str) {
    Stack stack;
    Queue queue;
    int len = strlen(str);

    init_stack(&stack);
    init_queue(&queue);

    for (int i = 0; i < len; i++) {
        char c = str[i];
        if (is_alpha(c)) {
            c = to_lower(c);
            push(&stack, c);
            enqueue(&queue, c);
        }
    }

    while (!is_emptyStack(&stack) && !is_empty(&queue)) {
        if (pop(&stack) != dequeue(&queue)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[MAX_SIZE];
    int choice;

    while (1) {
        printf("1. 확인하고 싶은 회문을 입력하세요\n");
        printf("2. 회문을 검사합니다\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            fgets(str, sizeof(str), stdin);
            break;
        case 2:
            if (strlen(str) == 0) {
                printf("먼저 확인하고 싶은 회문을 입력하세요.\n");
            }
            else {
                if (is_palindrome(str)) {
                    printf("회문입니다.\n");
                }
                else {
                    printf("회문이 아닙니다.\n");
                }
            }
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            exit(0);
        default:
            printf("잘못된 메뉴 선택입니다. 다시 선택하세요.\n");
            break;
        }
    }

    return 0;
}
