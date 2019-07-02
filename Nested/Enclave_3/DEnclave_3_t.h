#ifndef DENCLAVE_3_T_H__
#define DENCLAVE_3_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */

#include "user_types.h"

#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void inner_3_init();


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
