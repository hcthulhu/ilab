#ifndef _HASH_H_INCLUDED_
#define _HASH_H_INCLUDED_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

const int MAXSMB = 40;
const int MAXCELLS = 100;
const long long int KEY = 23456274187;
const int ANSSIZE = 50;

typedef struct _Contact {
    long long int num;
    char name[MAXSMB];
} Contact;

typedef Contact Data;

typedef struct _Node {
    Data data;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct _List {
    int size;
    Node* head;
    Node* tail;
    int key;
} List;

typedef struct _HashTable {
    List** list;
    int size;
} HashTable;

List* list_create();
void list_delete(List** list);
void list_push(List* list, Data data);
Node* list_get_node(List* list, int number);
void list_print(List* list);
int list_find(List* list, long long int fdata);
void file_read (FILE* phones, HashTable* htable, int (*Hash) (long long int));
int hash_find (HashTable* htable, int key);
void hash_insert (Contact new, HashTable* htable, int (*Hash) (long long int));
int hash_mod (long long int number);
int hash_xor (long long int number);
int hash_sum (long long int number);
int hash_bit (long long int number);
int hash_add (long long int number);
void hash_print (HashTable* htable);
int find_contact (HashTable* htable, long long int num, int (*Hash) (long long int));
void interface (HashTable* htable, int (*Hash) (long long int), FILE* phones);
void fill_file (HashTable* htable, FILE* file);

#include "hash2.c"

#endif /* _HASH_H_INCLUDED_ */
