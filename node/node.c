#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

const int cnr = 787;
const int cipher = 1234;

struct _node {
    int canary1;
    int val;
    int checksum;
    struct _node* prev;
    struct _node* next;
    int canary2;
};
typedef struct _node node;

node* CreateNode (int val_, node* prev_, node* next_);
void ConnectNodes (node* left, node* right);
void DeleteNode (node* delnode);
void InsertNode (node* insert, node* left);
void CheckNode (node* first);

int main() {
    node* new;
    node* old;

    node* last = CreateNode (9999, NULL, NULL);
    node* first = CreateNode (1000, NULL, NULL);
    ConnectNodes(first, last);

    new = first;
    old = first;
    for ( int cntr = 0; cntr < 5; cntr++ ) {
        new = CreateNode (1 + cntr, new, last);
        ConnectNodes(old, new);
        old = new;
    }
    char* a;
    a = (char*)calloc(1, sizeof(char));
    for (int i = 0; i < 17; i++) {
        *(a + i) = 'a';
    }

    CheckNode(first);
}

void InsertNode (node* insert, node* left) {
    // assert (!insert);
    // assert (!left);
    // assert (!left->next);
    // assert (!insert->prev);
    // assert (!insert->next);
    insert->next = left->next;
    insert->prev = left;
    left->next->prev = insert;
    left->next = insert;
}

void DeleteNode (node* delnode) {
    // assert (!delnode);
    // assert (!delnode->prev);
    // assert (!delnode->next);
    delnode->prev->next = delnode->next;
    delnode->next->prev = delnode->prev;
    free(delnode);
}

node* CreateNode (int val_, node* prev_, node* next_) {
    // assert (prev_ == next_);
    // assert (!prev_);
    // assert (!next_);
    node* ret = (node*) calloc (1, sizeof(node));
    ret->canary1 = cnr;
    ret->canary2 = cnr;
    ret->prev = prev_;
    ret->next = next_;
    ret->val = val_;
    ret->checksum = val_ ^ cipher;
    return ret;
}

void ConnectNodes (node* left, node* right) {
    // assert (!left);
    // assert (!right);
    // assert (left == right);
    // assert (left->prev == right);
    // assert (right->next == left);
    right->prev = left;
    left->next = right;
}

void CheckNode (node* first) {
  if ( first ) {
    if (((first->checksum) == (first->val ^ cipher)) && (first->canary1 == cnr) && (first->canary2 == cnr)) {
      printf("%d\n", first->val);
      CheckNode (first->next);
    }
    else
    printf("error\n");
  }
  else
  printf("end\n");
}

/*
//------------------------//
    разбиение на файлы
//------------------------//


//main.c:

#include <list.h>

int main()
..

list.h:
#include <stdlib.h>

struct node {
    ..
}

node* CreateNode ();
void ConnectNodes ();
int ok ();

#include <list.cpp>

//------------------------//

//list.cpp:

node* CreateNode (int val_, node* prev_, node* next_) {
    assert (prev == next);
    assert (!prev);
    assert (!next);
    node ret = (node*) calloc (1, sizeof(node));
    ret->prev = prev_;
    ret->next = next_;
    ret->val = val_;
    return ret;
}

void ConnectNodes (node* left, node* right) {
    assert (!left);
    assert (!right);
    assert (left == right);
    assert (left->prev == right);
    assert (right->next == left);
    right->prev = left;
    left->next = right;
}
*/
