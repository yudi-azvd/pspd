#include "./hashtable.h"
#include <stdio.h>

int main() {

    HT* ht = HT_create();
    const int len = 4;
    char* strings[] = {
        "lorem",
        "epsum",
        "coisa",
        "alem",
    };

    for (int i = 0; i < len; i++) {
        printf("Hash of %s: %d\n", strings[i], HT_put(ht, strings[i], i));
    }

    HT_destroy(ht);
    return 0;
}