#include "tree.h"

// int tree_insert(struct node** n, int val) {
//     if ( !(*n) ) {
//         if (!(*n = (node*)malloc(sizeof(struct node))))
//             return -1;
//         (*n)->val = val;
//         return 0;
//     }
//     if ( val > (*n)->val)
//         return tree_insert(&(*n)->right, val);
//     else
//         return tree_insert(&(*n)->left, val);
// }
//
// int tree_find(struct node*n, int *val) {
//     if ( !n )
//         return 0;
//     if ( n->val == *val)
//         return 1;
//     if ( n->val < *val)
//         return tree_find(n->right, val);
//     else
//         return tree_find(n->left, val);
// }
//
// int print_tree(struct node* n) {
//     if ( !n )
//         return 0;
//         print_tree(n->left);
//         printf("%s\n", n->val);
//         print_tree(n->right);;
//         return 0;
// }
// void read(FILE* file) {
//     char* data = NULL;
//     char c = 0;
//     int i = 0;
//     for (; c != EOF; fscanf(file, "%c", &c), i++) {
//         if (c != '(') {
//             data[i] = c;
//         } else {
//             tree.
//         }
//     }
// } strchr(const char *s, int c)

char* file_read(FILE* file, size_t* size) {
    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    printf("%lu\n", *size);
    char* string = (char*)calloc(*size, sizeof(char));
    rewind(file);
    fread(string, sizeof(char), *size, file);
    return string;
}

void read(char* string, size_t size) {
    size_t num = strcspn(string, "?");
    size_t newsize = size - num - 1;
    char* question = (char*)calloc(num + 1, sizeof(char));
    char* newstring = (char*)calloc(newsize, sizeof(char));

    strncpy(question, string, num + 1);
    char* begin = strchr(string, '?') + 1;
    strcpy(newstring, begin);

    free(string);

    // add_left(question);
    // left.read(newstring, newsize);



}
