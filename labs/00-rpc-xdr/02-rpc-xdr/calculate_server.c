/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculate.h"

int *add_100_svc(operands *argp, struct svc_req *rqstp) {
    static int result;

    printf("Request add(%d, %d)\n", argp->x, argp->y);
    result = argp->x + argp->y;

    return &result;
}

int *sub_100_svc(operands *argp, struct svc_req *rqstp) {
    static int result;

    printf("Request sub(%d, %d)\n", argp->x, argp->y);
    result = argp->x - argp->y;

    return &result;
}
