#include "./hashtable.h"
#include <stdio.h>

int main() {
    
    HT* ht = HT_create();
    char* key = "Abobora";
    HT_put(ht, key, 3);
    int key_hash = HT_hash(key, ht->capacity);
    printf("Hash of %s: %d\n", key, key_hash);

    printf("%d\n",  HT_item_equals_null(ht->items[0]));
    printf("%d\n",  HT_items_equal(ht->items[key_hash], HT_item_null()));

    HT_destroy(ht);
    return 0;
}