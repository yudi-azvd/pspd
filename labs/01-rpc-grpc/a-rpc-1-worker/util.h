#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "../lib/darray.h"
#include "dwc.h"
#include <stdlib.h>

DwcRequest* DwcRequest_create_from_darray(Darray* darr) {
    DwcRequest* req = (DwcRequest*)calloc(1, sizeof(DwcRequest));
    req->strings.strings_len = darr->size;
    req->strings.strings_val = (String*)calloc(darr->size, sizeof(String));
    for (int i = 0; i < darr->size; i++) {
        req->strings.strings_val[i] = darr->arr[i];
    }

    return req;
}

void DwcResponse_destroy(DwcResponse* res) {
    // FIXME: o ideial seria liberar a memória com algo assim:
    // xdr_free((xdrproc_t) xdr_DwcRequest, (char*) res);
    
    for (int i = 0; i < res->words_count.words_count_len; i++)
        free(res->words_count.words_count_val[i].key);
    free(res->words_count.words_count_val);
}

void DwcRequest_destroy(DwcRequest* req) {
    // FIXME: o ideial seria liberar a memória com algo assim:
    // xdr_free((xdrproc_t) xdr_DwcResponse, (char*) req);
    free(req->strings.strings_val);
    free(req);
}

Darray* read_from_file(char* file_path) {
    // FILE* fp = fopen(file_path, "r");
    Darray* darr = Darray_create();
    char* strings[] = {
        "lorem",
        "epsum",
        "coisa",
        "alem",
    };
    for (int i = 0; i < 4; i++)
        Darray_append(darr, strings[i]);

    // fclose(fp);
    return darr;
}

#endif // UTIL_H_INCLUDED