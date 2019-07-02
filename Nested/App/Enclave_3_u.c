#include "Enclave_3_u.h"
#include <errno.h>


typedef struct ms_ocall_print_string_t {
	char* ms_str;
} ms_ocall_print_string_t;

typedef struct ms_ocall_sleep_t {
	int ms_time;
} ms_ocall_sleep_t;

static sgx_status_t SGX_CDECL Enclave_3_ocall_print_string(void* pms)
{
	ms_ocall_print_string_t* ms = SGX_CAST(ms_ocall_print_string_t*, pms);
	ocall_print_string((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_3_ocall_sleep(void* pms)
{
	ms_ocall_sleep_t* ms = SGX_CAST(ms_ocall_sleep_t*, pms);
	ocall_sleep(ms->ms_time);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[2];
} ocall_table_Enclave_3 = {
	2,
	{
		(void*)Enclave_3_ocall_print_string,
		(void*)Enclave_3_ocall_sleep,
	}
};
sgx_status_t inner_3_init(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave_3, NULL);
	return status;
}
