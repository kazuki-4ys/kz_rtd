#include "ctgp_som_replica.h"

void *get_ctgp_som_replica_patch1(void);
void *get_ctgp_som_replica_patch1_end(void);
void *get_ctgp_som_replica_patch2(void);
void *get_ctgp_som_replica_patch2_end(void);
void *get_ctgp_som_replica_patch3(void);
void *get_ctgp_som_replica_patch3_end(void);
void *get_ctgp_som_replica_patch4(void);
void *get_ctgp_som_replica_patch4_end(void);

#ifdef RMCP

#define PATCH1_ADDR 0x8060245c
#define PATCH2_ADDR 0x808584d8
#define PATCH3_ADDR 0x8085853c
#define PATCH4_ADDR 0x8057c3a8

#endif

#ifdef RMCE

#define PATCH1_ADDR 0x805ddb7c
#define PATCH2_ADDR 0x80836a48
#define PATCH3_ADDR 0x80836aac
#define PATCH4_ADDR 0x80575b44

#endif

#ifdef RMCJ

#define PATCH1_ADDR 0x80601bd0
#define PATCH2_ADDR 0x80857b44
#define PATCH3_ADDR 0x80857BA8
#define PATCH4_ADDR 0x8057bd28

#endif

void installCtgpSomReplica(void){
    injectC2Patch((void*)PATCH1_ADDR, get_ctgp_som_replica_patch1(), get_ctgp_som_replica_patch1_end());
    injectC2Patch((void*)PATCH2_ADDR, get_ctgp_som_replica_patch2(), get_ctgp_som_replica_patch2_end());
    injectC2Patch((void*)PATCH3_ADDR, get_ctgp_som_replica_patch3(), get_ctgp_som_replica_patch3_end());
    injectC2Patch((void*)PATCH4_ADDR, get_ctgp_som_replica_patch4(), get_ctgp_som_replica_patch4_end());
}