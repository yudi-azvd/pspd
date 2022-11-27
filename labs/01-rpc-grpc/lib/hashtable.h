#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define _HT_INITIAL_CAPACITY 11
#define _HT_MAX_STR_LEN 100
#define _HT_ITEM_NULL_VAL -1

int HT_hash(const char* k, int capacity) {
    int hash_result, a = 31415, b = 27183;

    for (hash_result = 0; *k != '\0'; k++) {
        a = a * b % (capacity - 1);
        hash_result = (a * hash_result + *k) % capacity;
    }

    return hash_result;
}

typedef struct HT_item {
    char* key;
    int value;
} HT_item;

HT_item HT_item_null() {
    static HT_item HT_ITEM_NULL = {NULL, 0};
    return HT_ITEM_NULL;
}

int HT_items_equal(HT_item a, HT_item b) {
    return a.value == b.value && strcmp(a.key, b.key) == 0;
}

int HT_item_equals_null(HT_item item) {
    return item.key == NULL && item.value == _HT_ITEM_NULL_VAL;
}

typedef struct HT {
    int size;
    int capacity;
    HT_item* items;
} HT;

HT* HT_create() {
    HT* ht = (HT*)calloc(1, sizeof(HT));
    ht->capacity = _HT_INITIAL_CAPACITY;
    ht->size = 0;
    ht->items = (HT_item*)calloc(_HT_INITIAL_CAPACITY, sizeof(HT_item));
    for (int i = 0; i < ht->capacity; i++)
        ht->items[i].value = _HT_ITEM_NULL_VAL;
    
    return ht;
}

#define HT_size(ht) ht->size

int HT_put(HT* ht, char* key, int value) {
    int probe, capacity = ht->capacity;
    unsigned hash = HT_hash(key, capacity);
    char k[_HT_MAX_STR_LEN];

    // for (size_t probe = 0; probe < capacity; probe++) {
    //     k[0] = '\0';
    //     strcpy(k, ht->items[hash].key);
    // }
    ht->size++;
    // strcpy(ht->items[hash].key, key);
    ht->items[hash].key = key;
    ht->items[hash].value = value;
    return hash;
}

int HT_remove(HT* ht, char* key) {
    return 0;
}

int HT_get(HT* ht, char* key) {
    return 0;
}

void HT_destroy(HT* ht) {
    free(ht->items);
    free(ht);
}

#endif // HASHTABLE_H_INCLUDED