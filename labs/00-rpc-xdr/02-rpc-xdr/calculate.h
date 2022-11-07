/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CALCULATE_H_RPCGEN
#define _CALCULATE_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct operands {
	int x;
	int y;
};
typedef struct operands operands;

#define calculate 55555555
#define VER 100

#if defined(__STDC__) || defined(__cplusplus)
#define add 1
extern  int * add_100(operands *, CLIENT *);
extern  int * add_100_svc(operands *, struct svc_req *);
#define sub 2
extern  int * sub_100(operands *, CLIENT *);
extern  int * sub_100_svc(operands *, struct svc_req *);
extern int calculate_100_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define add 1
extern  int * add_100();
extern  int * add_100_svc();
#define sub 2
extern  int * sub_100();
extern  int * sub_100_svc();
extern int calculate_100_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_operands (XDR *, operands*);

#else /* K&R C */
extern bool_t xdr_operands ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CALCULATE_H_RPCGEN */
