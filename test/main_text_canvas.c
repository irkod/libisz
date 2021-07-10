#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include "isz/isz.h"

const char *main_text_program_id = "main_text";
ISZ_FAIL_FILE(main_text_program_id);

int main()
{
	ISZ_FAIL_ROOT;
	ISZ_FAIL_NEXT_VAL(0);

	setlocale(LC_ALL, "");
	struct isz_text_canvas *tc = isz_text_canvas_new(ISZ_FAIL);
	isz_text_canvas_init(tc);
	isz_text_canvas_i_t *tc_canvas_i = ISZ_OBJECT_GET_INTERFACE(tc, isz_text_canvas);
	isz_row_cursor_i_t *tc_cursor_i = ISZ_OBJECT_GET_INTERFACE(tc, isz_row_cursor);


	tc_canvas_i->resize(tc, 20, 20, ISZ_FAIL);

	int k = 0;
	int i = 0;

	for(;;)
	{
		int size = tc_canvas_i->put(tc, 0, k++, "zażółć gęślą jaźń!" + i, ISZ_FAIL);
		i += size;

		if(!size)
			break;

		ISZ_FAIL_PRINT(stdout);
	}

	tc_cursor_i->set(tc, 3);
	tc_canvas_i->print(tc, stdout, ISZ_FAIL);
	tc_canvas_i->resize(tc, 10, 30, ISZ_FAIL);
	
	ISZ_OBJECT_DETACH(tc);

	ISZ_FAIL_PRINT(stdout);
	
	ISZ_FAIL_ROOT_FREE;
	return 0;
}
