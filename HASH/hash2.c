#ifndef _HASH_C_INCLUDED_
#define _HASH_C_INCLUDED_


#include "hash.h"

typedef Contact Data;

List* list_create() {
    List* ret = (List*)calloc(1, sizeof(List));
    ret->size = 0;
    ret->head = ret->tail = NULL;
    ret->key = -1;

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

void list_push(List *list, Data data) {
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
}

Node* list_get_node(List *list, int number) {
    Node* node = list->head;

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

void list_print(List *list) {
    Node* node = list->head;

    while (node != NULL) {
            printf("%lld %s", node->data.num, node->data.name);
            node = node->next;
    }
    if (list->size == 0) {
        printf("empty list\n");
    }
    printf("\n");
}

int list_find(List* list, long long int num) {
    for (int cntr = 0;  cntr < list->size; cntr++) {
        if (list_get_node(list, cntr)->data.num == num) {
            return cntr;
        }
    }

    return -1;
}

void file_read (FILE* phones, HashTable* htable, int (*Hash) (long long int)) {
    Contact new = {};
    while (fscanf (phones, "%lld ", &new.num) != EOF) {
        fgets (new.name, MAXSMB, phones);
        hash_insert(new, htable, Hash);
    }
}

void hash_insert (Contact new, HashTable* htable, int (*Hash) (long long int)) {
    long long int newKey = Hash (new.num);

    int cntr = hash_find (htable, newKey);

    if (list_find (htable->list[cntr], new.num) >= 0) {
      return;
    }

    list_push (htable->list[cntr], new);
    htable->list[cntr]->key = newKey;
    htable->size++;
}

int hash_find (HashTable* htable, int key) {
    for (int cntr = 0; cntr < MAXCELLS; cntr++) {
        if ((htable->list[cntr]->key == key) || (htable->list[cntr]->key == -1)) {
            return cntr;
        }
    }
    return -1;
}

int hash_mod (long long int number) {
    return (number % MAXCELLS);
}

int hash_xor (long long int number) {
    return ((number ^ KEY) % MAXCELLS);
}

int hash_sum (long long int number) {
    int sum = 0;
    long long int temp = number;
    for (int cntr = 0; cntr < 11; cntr ++) {
        sum += temp % 10;
        temp /= 10;
    }
    return sum;
}

int hash_bit (long long int number) {
    return ((number >> 4) % MAXCELLS);
}

int hash_add (long long int number) {
    return (-(~number) % MAXCELLS);
}

HashTable* hash_create() {
    HashTable* ret = (HashTable*)calloc(1, sizeof(HashTable));
    ret->size = 0;
    ret->list = (List**)calloc(MAXCELLS, sizeof(List*));
    for (int cntr = 0; cntr < MAXCELLS; cntr++) {
        ret->list[cntr] = list_create();
    }
    return ret;
}

void hash_print (HashTable* htable) {
    for (int cntr = 0; cntr < MAXCELLS; cntr++) {
        printf("key: %d\n", htable->list[cntr]->key);
        list_print(htable->list[cntr]);
    }
    printf("end\n");
}

void hash_plot (HashTable* htable, FILE* file) {
    for (int cntr = 0; cntr < MAXCELLS; cntr++) {
        fprintf(file, "%d;%d\n", htable->list[cntr]->key, htable->list[cntr]->size);
    }
}

int find_contact (HashTable* htable, long long int num, int (*Hash) (long long int)) {
    int cntr = hash_find (htable, Hash(num));
    if (cntr < 0) {
        printf ("not found\n");
        return -1;
    }

    int lcntr = list_find(htable->list[cntr], num);
    if (lcntr < 0) {
        printf ("not found\n");
        return -1;
    }
    Node* node = list_get_node(htable->list[cntr], lcntr);
    printf("%lld %s", node->data.num, node->data.name);
    return 0;
}

void interface (HashTable* htable, int (*Hash) (long long int), FILE* phones) {
    char* answer = (char*)calloc(ANSSIZE, sizeof(char));
    char* name = (char*)calloc(20, sizeof(char));
    char* surname = (char*)calloc(20, sizeof(char));
    Contact new = {};
    long long int num = 0;
    for ( ; ; ) {
        printf ("what do you want?\n1 - find number\n2 - add number\n3 - quit\n");
        char ans = 0;
        scanf("%c", &ans);
        switch(ans) {
            case '1': {
                printf ("what number do you want to find?\n");
                scanf ("%lld", &num);
                if (find_contact (htable, num, hash_mod) != 0) {
                    printf ("do you want to add this number?\n");
                    scanf("%s", answer);
                    if (strcmp(answer, "yes") == 0) {
                        printf ("print \"num name surname\"\n");
                        scanf("%lld %s %s", &new.num, name, surname);

                        size_t n = strlen(name);
                        strcat(new.name, name);
                        new.name[n] = ' ';
                        strcat(new.name, surname);
                        n = strlen(new.name);
                        new.name[n] = '\n';

                        hash_insert(new, htable, Hash);
                    }
                }

                break;
            }

            case '2': {
                printf ("print \"num name surname\"\n");
                scanf("%lld %s %s", &new.num, name, surname);

                size_t n = strlen(name);
                strcat(new.name, name);
                new.name[n] = ' ';
                strcat(new.name, surname);
                n = strlen(new.name);
                new.name[n] = '\n';

                hash_insert(new, htable, Hash);

                break;
            }

            case '3': {
                exit(0);
            }

            default: {
                printf ("print 1, 2 or 3\n");
            }
        }
    }
}

void fill_file (HashTable* htable, FILE* file) {
    for (int cntr = 0; cntr < MAXCELLS; cntr++) {
        Node* node = htable->list[cntr]->head;

        while (node != NULL) {
                fprintf(file, "%lld %s", node->data.num, node->data.name);
                node = node->next;
        }
    }
}

#endif /* _HASH_C_INCLUDED_ */
