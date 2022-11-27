#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "../lib/darray.h"
#include "dwc.h"
#include <stdlib.h>

DwcRequest *DwcRequest_create_from_darray(Darray *darr) {
  DwcRequest *req = (DwcRequest *)calloc(1, sizeof(DwcRequest));
  req->strings.strings_len = darr->size;
  req->strings.strings_val = (String *)calloc(darr->size, sizeof(String));
  for (int i = 0; i < darr->size; i++) {
    int len = strlen(darr->arr[i]);
    req->strings.strings_val[i] = (String)calloc(len + 1, sizeof(char));
    memcpy(req->strings.strings_val[i], darr->arr[i], len);
  }

  return req;
}

void DwcRequest_destroy(DwcRequest *req ) {
  for (int i = 0; i < req->strings.strings_len; i++)
    free(req->strings.strings_val[i]);
  free(req->strings.strings_val);
  free(req);
}

#endif // UTIL_H_INCLUDED