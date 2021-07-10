#include <malloc.h>
#include "isz/isz.h"

const char *program_id = "main_fail";
ISZ_FAIL_FILE(program_id);

void fun_a(ISZ_FAIL_PARAM)
{
	ISZ_FAIL_SET(isz_fail_errno_failure(2));
	return;
}


void fun_b(ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	fun_a(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;

	return;
}

void fun_c(ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT;

	fun_b(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF;

	return;
}

int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(1);

	fun_c(ISZ_FAIL);
	ISZ_FAIL_SET_CALL_IF;	
	ISZ_FAIL_PRINT(stdout);

	ISZ_FAIL_CLEAR;;

	fun_a(ISZ_FAIL);
	ISZ_FAIL_SET_CALL_IF;	
	ISZ_FAIL_PRINT(stdout);
	
	ISZ_FAIL_ROOT_FREE;
	return 0;
}
