#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "list.h"

//------------------------------------------------------------------------------

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

    list_insert_before(list, 0, 100);

    list_print(list);
    //Node* hack = list->head;
    //hack->next = NULL;
    //hack->prev = NULL;

    list_print(list);
    list_dot (list);

    return 0;
}

//------------------------------------------------------------------------------

// List* list_create();
// создание и инициализация списка

// void list_delete(List** list);
// удалить список

// void list_push_front(List* list, Data data);
// создать узел в начале списка

// void list_push_back(List* list, Data data);
// создать узел в конце списка

// Data list_pop_front(List* list);
// возвращает значение из узла в начале списка и удалить узел

// Data list_pop_back(List* list);
// возвращает значение из узла в конце списка и удалить узел

// Node* list_get_node(List* list, int number);
// возвращает адрес Nого узла от начала списка

// Data list_pop_node(List* list, int number);
// возвращает значение из Nого узла от начала списка и удалить узел

// void list_print(List* list);
// вывести значения в узлах списка через пробел

// void recount_node_sum(Node* node);
// пересчитать checksum у узла

// int check_node_data(Node* node);
// проверить целостность структуры поданного узла

// void recount_list_sum(List* list);
// пересчитать checksum у списка

// int check_list_data(List* list);
// проверить целостность структуры поданного списка

// Node* list_find(List* list, Data fdata);
// найти узел по значению

// void list_insert_before(List* list, int number, Data data);
// вставить узел перед Nым узлом

// void list_insert_after(List* list, int number, Data data);
// вставить узел перед Nым узлом

// int list_ok(List* list);
// проверить целостность всего поданного списка
