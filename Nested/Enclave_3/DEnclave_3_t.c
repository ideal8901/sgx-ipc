#include "DEnclave_3_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)



static sgx_status_t SGX_CDECL sgx_inner_3_init(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;

#ifdef _MSC_VER
	/* In case enclave `DEnclave_3' doesn't call any tRTS function. */
	volatile int force_link_trts = sgx_is_within_enclave(NULL, 0);
	(void) force_link_trts; /* avoid compiler warning */
#endif

	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	inner_3_init();
	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[1];
} g_ecall_table_demi = {
	1,
	{
		{(void*)(uintptr_t)sgx_inner_3_init, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
} g_dyn_entry_table_demi = {
	0,
};


