#include "hash.h"

int main() {
    FILE* phones = fopen("phones.txt", "a+");

    FILE* hash_mod_file = fopen("HASH_MOD.csv", "w");
    // FILE* hash_xor_file = fopen("HASH_XOR.csv", "w");
    // FILE* hash_sum_file = fopen("HASH_SUM.csv", "w");
    // FILE* hash_bit_file = fopen("HASH_BIT.csv", "w");
    // FILE* hash_add_file = fopen("HASH_ADD.csv", "w");

    HashTable* htable_mod = hash_create();
    // HashTable* htable_xor = hash_create();
    // HashTable* htable_sum = hash_create();
    // HashTable* htable_bit = hash_create();
    // HashTable* htable_add = hash_create();

    file_read (phones, htable_mod, hash_mod);
    rewind(phones);
    // file_read (phones, htable_xor, hash_xor);
    // rewind(phones);
    // file_read (phones, htable_sum, hash_sum);
    // rewind(phones);
    // file_read (phones, htable_bit, hash_bit);
    // rewind(phones);
    // file_read (phones, htable_add, hash_add);

    // hash_plot (htable_mod, hash_mod_file);
    // hash_plot (htable_xor, hash_xor_file);
    // hash_plot (htable_sum, hash_sum_file);
    // hash_plot (htable_bit, hash_bit_file);
    // hash_plot (htable_add, hash_add_file);

    fclose(phones);
    fclose(hash_mod_file);
    // fclose(hash_xor_file);
    // fclose(hash_sum_file);
    // fclose(hash_bit_file);
    // fclose(hash_add_file);


    interface(htable_mod, hash_mod, phones);
    FILE*


    return 0;
}
