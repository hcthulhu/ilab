#ifndef _LIST_H_INCLUDED_
#define _LIST_H_INCLUDED_


typedef int Data;
typedef struct _Node {
    int cnr1;
    Data data;
    Data key;
    struct _Node* next;
    struct _Node* prev;
    int checksum;
    int cnr2;
} Node;

typedef struct _List {
    int size;
    Node* head;
    Node* tail;
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
Node* list_find(List* list, Data fdata);
void list_insert_before(List* list, int number, Data data);
void list_insert_after(List* list, int number, Data data);
int list_ok(List* list);
void list_dot (List* list);

#endif /* _LIST_H_INCLUDED_ */
