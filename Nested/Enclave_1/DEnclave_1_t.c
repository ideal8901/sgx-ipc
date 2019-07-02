#include "DEnclave_1_t.h"

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



typedef struct ms_ecall_test_producer_t {
	void* ms_buf;
} ms_ecall_test_producer_t;

typedef struct ms_docall_print_string_t {
	char* ms_str;
} ms_docall_print_string_t;

static sgx_status_t SGX_CDECL sgx_inner_1_init(void* pms)
{
	sgx_status_t status = SGX_SUCCESS;
	if (pms != NULL) return SGX_ERROR_INVALID_PARAMETER;
	inner_1_init();
	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_test_producer(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_test_producer_t));
	ms_ecall_test_producer_t* ms = SGX_CAST(ms_ecall_test_producer_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	void* _tmp_buf = ms->ms_buf;


	ecall_test_producer(_tmp_buf);


	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[2];
} g_ecall_table_demi = {
	2,
	{
		{(void*)(uintptr_t)sgx_inner_1_init, 0},
		{(void*)(uintptr_t)sgx_ecall_test_producer, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[1][2];
} g_dyn_entry_table_demi = {
	1,
	{
		{0, 0, },
	}
};


sgx_status_t SGX_CDECL docall_print_string(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_docall_print_string_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_docall_print_string_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc_outer(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree_outer();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_docall_print_string_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_docall_print_string_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_str);
		memcpy((void*)ms->ms_str, str, _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree_outer();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0+10000, ms);


	sgx_ocfree_outer();	return status;
}

