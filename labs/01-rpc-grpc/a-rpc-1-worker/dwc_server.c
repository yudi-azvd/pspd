/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "dwc.h"

DwcResponse* count_100_svc(DwcRequest* argp, struct svc_req* rqstp) {
    static DwcResponse result;
    int strings_len = argp->strings.strings_len;
    result.length = strings_len;
    result.total_words = strings_len;

    printf("DWC Req strings length %d\n", strings_len);
    for (int i = 0; i < strings_len; i++)
        printf("DWC Req strings[%d]: %s\n", i, argp->strings.strings_val[i]);

    return &result;
}
