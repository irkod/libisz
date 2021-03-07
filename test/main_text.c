#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>
#include "isz/isz.h"

const char *main_text_program_id = "main_text";
ISZ_FAIL_FILE(main_text_program_id);

int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(0);

	isz_text_t *t = isz_text_new(ISZ_FAIL);
	isz_text_init_mprintf(t, ISZ_FAIL, "Ala ma %d koty %s.\nI %d ma %s też.\n", 3, "syjamskie", 5, "koni");
	isz_str_i_t *str_i = ISZ_OBJ_GET_I(t, isz_str);

	printf(str_i->get(t));

	ISZ_OBJ_DETACH(t);

	ISZ_FAIL_PRINT(stdout);
	
	ISZ_FAIL_ROOT_FREE;
	return 0;
}
