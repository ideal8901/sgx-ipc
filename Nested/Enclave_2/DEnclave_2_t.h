#ifndef DENCLAVE_2_T_H__
#define DENCLAVE_2_T_H__

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


void inner_2_init();
void ecall_test_consumer(void* buf);

sgx_status_t SGX_CDECL docall_print_string(const char* str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif