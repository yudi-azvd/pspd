/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DWC_H_RPCGEN
#define _DWC_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct Words {
	char *buffer;
	int length;
};
typedef struct Words Words;

struct HashTable {
	int capacity;
	int size;
	char *strings;
};
typedef struct HashTable HashTable;

struct gnumbers {
	int g_assets;
	int g_liabilities;
};
typedef struct gnumbers gnumbers;

struct gnumbers_node {
	gnumbers gn_numbers;
	struct gnumbers_node *gn_next;
};
typedef struct gnumbers_node gnumbers_node;

#define dwc 55555555
#define VER 100

#if defined(__STDC__) || defined(__cplusplus)
#define count 1
extern  int * count_100(Words *, CLIENT *);
extern  int * count_100_svc(Words *, struct svc_req *);
extern int dwc_100_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define count 1
extern  int * count_100();
extern  int * count_100_svc();
extern int dwc_100_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_Words (XDR *, Words*);
extern  bool_t xdr_HashTable (XDR *, HashTable*);
extern  bool_t xdr_gnumbers (XDR *, gnumbers*);
extern  bool_t xdr_gnumbers_node (XDR *, gnumbers_node*);

#else /* K&R C */
extern bool_t xdr_Words ();
extern bool_t xdr_HashTable ();
extern bool_t xdr_gnumbers ();
extern bool_t xdr_gnumbers_node ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DWC_H_RPCGEN */
