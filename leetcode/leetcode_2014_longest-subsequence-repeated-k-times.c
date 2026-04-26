#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool findsub(const char* sub, const char* s, int k) {
    int len_sub = strlen(sub);
    if (len_sub == 0)
        return false;

    int count = 0;
    int idx = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == sub[idx]) {
            idx++;
            if (idx == len_sub) {
                idx = 0;
                count++;
                if (count == k)
                    return true;
            }
        }
    }
    return false;
}

char* longestSubsequenceRepeatedK(char* s, int k) {
    typedef struct Node {
        char* str;
        struct Node* next;
    } Node;

    typedef struct {
        Node* front;
        Node* rear;
    } Queue;

    Queue q = {NULL, NULL};

    char* empty = (char*)malloc(1);
    *empty = '\0';
    Node* firstNode = (Node*)malloc(sizeof(Node));
    firstNode->str = empty;
    firstNode->next = NULL;
    q.front = q.rear = firstNode;

    char* result = (char*)malloc(1);
    *result = '\0';

    while (q.front != NULL) {
        Node* node = q.front;
        char* curr = node->str;
        q.front = node->next;
        if (q.front == NULL)
            q.rear = NULL;
        free(node);

        for (char c = 'a'; c <= 'z'; c++) {
            int len = strlen(curr);
            char* next = (char*)malloc(len + 2);
            strcpy(next, curr);
            next[len] = c;
            next[len + 1] = '\0';

            if (findsub(next, s, k)) {
                free(result);
                result = (char*)malloc(len + 2);
                strcpy(result, next);

                Node* newNode = (Node*)malloc(sizeof(Node));
                newNode->str = next;
                newNode->next = NULL;
                if (q.rear == NULL) {
                    q.front = q.rear = newNode;
                } else {
                    q.rear->next = newNode;
                    q.rear = newNode;
                }
            } else {
                free(next);
            }
        }
        free(curr);
    }
    return result;
}