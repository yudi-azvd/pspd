/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "../lib/darray.h"
#include "dwc.h"

void dwc_100(char *host, DwcRequest * dwc_req) {
  CLIENT *clnt;
  DwcResponse *result_1;

#ifndef DEBUG
  clnt = clnt_create(host, dwc, VER, "tcp");
  if (clnt == NULL) {
    clnt_pcreateerror(host);
    exit(1);
  }
#endif /* DEBUG */

  result_1 = count_100(dwc_req, clnt);
  if (result_1 == (DwcResponse *)NULL) {
    clnt_perror(clnt, "call failed");
  }

  printf("Total words: %d\n", result_1->total_words);
#ifndef DEBUG
  clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[]) {
  char *host;

  if (argc < 2) {
    printf("usage: %s server_host\n", argv[0]);
    exit(1);
  }

  Darray *darr = Darray_create();
  char *strings[] = {
      "lorem",
      "ipsum",
      "coisa",
      "alem",
  };

  for (int i = 0; i < 4; i++) {
    Darray_append(darr, strings[i]);
  }

  DwcRequest *req = calloc(1, sizeof(DwcRequest));
  req->strings.strings_len = darr->size;
  req->strings.strings_val = calloc(darr->size, sizeof(String));
  for (int i = 0; i < darr->size; i++) {
    int len = strlen(darr->arr[i]);
    req->strings.strings_val[i] = calloc(len+1, sizeof(char));
    memcpy(req->strings.strings_val[i], darr->arr[i], len);
  }

  host = argv[1];
  dwc_100(host, req);

  for (int i = 0; i < darr->size; i++)
    free(req->strings.strings_val[i]);
  free(req->strings.strings_val);
  free(req);

  Darray_destroy(darr);
  exit(0);
}
