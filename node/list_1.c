#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int CNR = 787;
const int cipher = 19238471;

typedef int Data;

typedef struct _Node {
    int cnr1;
    Data data;
    struct _Node *next;
    struct _Node *prev;
    int checksum;
    int cnr2;
} Node;

typedef struct _List {
    int size;
    Node *head;
    Node *tail;
    int checksum;
} List;

List* list_create();
void list_delete(List** list);
void list_push_front(List* list, Data data);
void list_push_back(List* list, Data data);
Data list_pop_front(List* list);
Data list_pop_back(List* list);
Node* list_get_node(List* list, int number);
Data list_pop_node(List* list, int number);
void list_print(List* list);
void recount_node_sum(Node* node);
int check_node_data(Node* node);
void recount_list_sum(List* list);
int check_list_data(List* list);

int main() {
    List* list = list_create();
    list_push_front(list, 1);
    list_push_front(list, 2);
    list_push_front(list, 3);
    list_push_front(list, 4);
    list_push_back(list, 5);
    list_push_back(list, 6);
    list_push_back(list, 7);
    list_push_back(list, 8);
     list_pop_back(list);
     list_pop_front(list);

    list_print(list);


    Node* hack = list->head;
    hack->next = NULL;
    hack->prev = NULL;

    //list_print(list);

    return 0;
}

List* list_create() {
    List* ret = (List*)calloc(1, sizeof(List));
    ret->size = 0;
    ret->head = ret->tail = NULL;

    return ret;
}

void list_delete(List** list) {
    Node* node = (*list)->head;
    Node* next = NULL;
    while (node != NULL) {
        next = node->next;
        free(node);
        node = next;
    }
    free(*list);
    (*list) = NULL;

}

void list_push_front(List *list, Data data) {
    Node* push = (Node*) calloc(1, sizeof(Node));
    push->data = data;
    push->next = list->head;
    push->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = push;
    }
    list->head = push;

    if (list->tail == NULL) {
        list->tail = push;
    }
    list->size++;
    push->cnr1 = CNR;
    push->cnr2 = CNR;
    recount_node_sum(push->next);
    recount_node_sum(push);
    recount_list_sum(list);
}

void list_push_back(List *list, Data data) {
    Node* push = (Node*) calloc(1, sizeof(Node));
    push->data = data;
    push->next = NULL;
    push->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = push;
    }
    list->tail = push;

    if (list->head == NULL) {
        list->head = push;
    }
    list->size++;
    push->cnr1 = CNR;
    push->cnr2 = CNR;
    recount_node_sum(push->prev);
    recount_node_sum(push);
    recount_list_sum(list);
}

Data list_pop_front(List *list) {
    Node* node;
    Data ret;
    if (list->head == NULL) {
        printf("empty list");
        exit(0);
    }
    node = list->head;
    if ((check_node_data(node) == 0) && (check_list_data(list) == 0)) {
        list->head = list->head->next;
        if (list->head != NULL) {
            list->head->prev = NULL;
        }
        if (node == list->tail) {
            list->tail = NULL;
        }
        ret = node->data;
        free(node);
        list->size--;
        recount_node_sum(list->head);
        recount_list_sum(list);
        return ret;
    } else {
        printf("data was damaged\n");
        exit(0);
    }
}

Data list_pop_back(List *list) {
    Node* node;
    Data ret;
    if (list->tail == NULL) {
        printf("empty list\n");
        exit(0);
    }
    node = list->tail;
    if ((check_node_data(node) == 0) && (check_list_data(list) == 0)) {
        list->tail = list->tail->prev;
        if (list->tail != NULL) {
            list->tail->next = NULL;
        }
        if (node == list->head) {
            list->head = NULL;
        }
        ret = node->data;
        free(node);
        list->size--;
        recount_node_sum(list->tail);
        recount_list_sum(list);
        return ret;
    } else {
        printf("data was damaged\n");
        exit(0);
    }

}

Node* list_get_node(List *list, int number) {
    Node* node = list->head;
    if (number > list->size) {
        printf("out of list\n");
        exit(0);
    }
    int n = 0;
    while ((node != NULL) && (n < number)) {
        node = node->next;
        n++;
    }

    if ((check_node_data(node) == 0) && (check_list_data(list) == 0)) {
        return node;
    } else {
        printf("data was damaged\n");
        exit(0);
    }
}

Data list_pop_node(List *list, int number) {
    Node* node = NULL;
    if ((check_node_data(node) == 0) && (check_list_data(list) == 0)) {
        Data ret = 0;
        node = list_get_node(list, number);
        if (node == NULL) {
            printf("empty node\n");
            exit(0);
        }
        if (node->prev != NULL) {
            node->prev->next = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        ret = node->data;

        if (node->prev == NULL) {
            list->head = node->next;
        }
        if (node->next == NULL) {
            list->tail = node->prev;
        }
        free(node);
        list->size--;
        recount_node_sum(list->tail);
        recount_node_sum(list->head);
        recount_list_sum(list);

        return ret;
    } else {
        printf("data was damaged\n");
        exit(0);
    }
}

void list_print(List *list) {
    Node *node = list->head;

    while (node != NULL) {
         if ((check_node_data(node) == 0) && (check_list_data(list) == 0)) {
            printf("%d ", node->data);
            node = node->next;

        } else {
            printf("data was damaged\n");
            exit(0);
        }
    }
    if (list->size == 0) {
        printf("empty list\n");
    } else {
        printf("\n");
    }
}

void recount_node_sum(Node* node) {
    if (node != NULL) {
        node->checksum = node->data ^ (17*((int)node->next)) ^ (13*((int)node->prev)) ^ cipher;
    }
}

int check_node_data(Node* node) {
    if ((node->checksum == (node->data ^ (17*((int)node->next)) ^ (13*((int)node->prev)) ^ cipher)) &&
        (node->cnr1 == CNR) && (node->cnr2 == CNR)) {
        return 0;
    }
    return -1;
}

void recount_list_sum(List* list) {
    if (list != NULL) {
        list->checksum = list->size ^ (13*((int)list->head)) ^ (17*((int)list->tail)) ^ cipher;
    }
}

int check_list_data(List* list) {
    if (list->checksum == (list->size ^ (13*((int)list->head)) ^ (17*((int)list->tail)) ^ cipher)) {
        return 0;
    }
    return -1;
}
