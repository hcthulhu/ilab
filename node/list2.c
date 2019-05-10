#include "list.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

const int CNR = 787;
const int CIPHER = 19238471;
const int MAXKEYS = 2000;
const int MAXSMB = 200;
const int MAXSTR = 30000;

//#define _SAFE_MODE_

typedef int Data;

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

#ifndef _SAFE_MODE_
    push->cnr1 = CNR;
    push->cnr2 = CNR;
    recount_node_sum(push->next);
    recount_node_sum(push);
    recount_list_sum(list);
#endif

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

#ifndef _SAFE_MODE_
    push->cnr1 = CNR;
    push->cnr2 = CNR;
    recount_node_sum(push->prev);
    recount_node_sum(push);
    recount_list_sum(list);
#endif

}

Data list_pop_front(List *list) {
    Node* node;
    Data ret;

    if (list->head == NULL) {
        printf("empty list");
        exit(0);
    }
    node = list->head;

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

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

#ifndef _SAFE_MODE_
    recount_node_sum(list->head);
    recount_list_sum(list);
#endif

    return ret;
}

Data list_pop_back(List *list) {
    Node* node;
    Data ret;

    if (list->tail == NULL) {
        printf("empty list\n");
        exit(0);
    }
    node = list->tail;

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

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

#ifndef _SAFE_MODE_
    recount_node_sum(list->tail);
    recount_list_sum(list);
#endif

    return ret;
}

Node* list_get_node(List *list, int number) {
    Node* node = list->head;

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    if (number > list->size - 1) {
        printf("out of list\n");
        exit(0);
    }
    int n = 0;
    while ((node != NULL) && (n < number)) {
        node = node->next;
        n++;
    }

    return node;
}

Data list_pop_node(List *list, int number) {
    Node* node = NULL;
    Data ret = 0;
    node = list_get_node(list, number);

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

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

    if (node->prev == NULL) {
        list->head = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    }

    ret = node->data;
    free(node);
    list->size--;

#ifndef _SAFE_MODE_
    recount_node_sum(list->tail);
    recount_node_sum(list->head);
    recount_node_sum(node->next);
    recount_node_sum(node->prev);
    recount_list_sum(list);
#endif

    return ret;
}

void list_print(List *list) {
    Node *node = list->head;

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    while (node != NULL) {
            printf("%d ", node->data);
            node = node->next;
    }
    if (list->size == 0) {
        printf("empty list\n");
    } else {
        printf("\n");
    }
}

void recount_node_sum(Node* node) {
    if (node != NULL) {
        node->checksum = node->data ^ (17*((int)node->next)) ^ (13*((int)node->prev)) ^ CIPHER;
    }
}

int check_node_data(Node* node) {
    if ((node->checksum == (node->data ^ (17*((int)node->next)) ^ (13*((int)node->prev)) ^ CIPHER)) &&
        (node->cnr1 == CNR) && (node->cnr2 == CNR)) {
        return 0;
    }
    return -1;
}

void recount_list_sum(List* list) {
    if (list != NULL) {
        list->checksum = list->size ^ (13*((int)list->head)) ^ (17*((int)list->tail)) ^ CIPHER;
    }
}

int check_list_data(List* list) {
    if (list->checksum == (list->size ^ (13*((int)list->head)) ^ (17*((int)list->tail)) ^ CIPHER)) {
        return 0;
    }
    return -1;
}

Node* list_find(List* list, Data fdata) {

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    if (list->size == 0) {
        printf("empty list\n");
        exit(0);
    }
    Node* node = NULL;
    for (int number = 0;  number <= list->size; number++) {
        node = list_get_node(list, number);
        if (node->data == fdata) {
            return node;
        }
    }
    printf("no such data\n");
    return NULL;
}

void list_insert_before(List* list, int number, Data data) {
    Node *nthnode = NULL;
    Node *insert = NULL;
    nthnode = list_get_node(list, number);

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    if (number > list->size - 1) {
        printf("out of list");
        exit(0);
    }

    insert = (Node*) calloc(1, sizeof(Node));
    insert->data = data;
    insert->prev = nthnode->prev;
    insert->next = nthnode;
    if (nthnode->prev != NULL) {
        nthnode->prev->next = insert;
        recount_node_sum(nthnode->prev);
    }
    if (nthnode->prev == NULL) {
        list->head = insert;
    }

    nthnode->prev = insert;
    list->size++;

#ifndef _SAFE_MODE_
    insert->cnr1 = CNR;
    insert->cnr2 = CNR;
    recount_node_sum(insert);
    recount_node_sum(nthnode);
    recount_list_sum(list);
#endif

}

void list_insert_after(List* list, int number, Data data) {
    Node *nthnode = NULL;
    Node *insert = NULL;
    nthnode = list_get_node(list, number);

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    if (number > list->size - 1) {
        printf("out of list");
        exit(0);
    }

    insert = (Node*) calloc(1, sizeof(Node));
    insert->data = data;
    insert->prev = nthnode;
    insert->next = nthnode->next;
    if (nthnode->next != NULL) {
        nthnode->next->prev = insert;
        recount_node_sum(nthnode->next);
    }
    if (nthnode->next == NULL) {
        list->tail = insert;
    }

    nthnode->next = insert;
    list->size++;

#ifndef _SAFE_MODE_
    insert->cnr1 = CNR;
    insert->cnr2 = CNR;
    recount_node_sum(insert);
    recount_node_sum(nthnode);
    recount_list_sum(list);
#endif

}

int list_ok(List* list) {

#ifndef _SAFE_MODE_
    Node *node = list->head;

    if (check_list_data(list) != 0) {
        return -1;
    }

    while (node != NULL) {
        if (check_node_data(node) != 0) {
            return -1;
        }
        node = node->next;
    }
#endif

    return 0;
}

void list_dot (List* list) {

#ifndef _SAFE_MODE_
    if (list_ok(list) != 0) {
        printf("data was damaged\n");
        exit(0);
    }
#endif

    FILE * output = fopen("list.dot", "w");
    fprintf(output, "digraph G{\nrankdir = LR;\n\tnode [shape = \"box\", color = \"black\"");
    fprintf(output, ", fontsize = 14];\n\tedge [color = \"black\"];\n\t");
    fprintf(output, "size [label = \"Size = %d\"]\n\n", list->size);

    Node* cur = list->head;
    int counter = 1;
    while (cur != NULL) {
        fprintf(output, "\telem_%d [shape = \"record\", label = \"<ptr>%d\\n", counter, counter);
        if(cur == list->head)
            fprintf(output, "HEAD\\n");
        if (cur == list->tail)
            fprintf(output, "TAIL\\n");
        fprintf(output, "%p | %d |\n\t\t{<prev> prev \\n%p\\n ", cur, cur->data, cur->prev);
        fprintf(output, "| <next> next\\n %p}", cur->next);

#ifndef _SAFE_MODE_
        fprintf(output, " | checksum\\n %d}", cur->checksum);
#endif

        fprintf(output," \"]\n");
        counter++;
        cur = cur->next;
    }

    fprintf(output, "\n");
    cur = list->head;
    counter = 1;
    while (cur != NULL) {
        if (cur->prev != NULL)
            fprintf(output, "\telem_%d:<prev>->elem_%d:<ptr>\n", counter, counter - 1);
        if (cur->next != NULL)
            fprintf(output, "\telem_%d:<next>->elem_%d:<ptr>\n", counter, counter + 1);
        counter++;
        cur = cur->next;
    }
    fprintf(output, "}");
    fclose(output);
    system("dot -Tpng list.dot -o MyList.png");
}
