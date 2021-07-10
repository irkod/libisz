#ifndef ISZ_I_TEXT_CANVAS_H
#define ISZ_I_TEXT_CANVAS_H

#include <stddef.h>
#include "isz/fail/fail.h"
#include "isz/it/it.h"

ISZ_I_ID_DECL(isz_text_canvas);

typedef struct isz_text_canvas_i_t_
{
	void (*resize)(void *vobj, size_t row_count, size_t column_count,
		       ISZ_FAIL_PARAM);
	int (*put)(void *vobj, size_t row, size_t column, char *unicode_char,
		   ISZ_FAIL_PARAM);
	void (*put_rectangle)(void *vobj, size_t row, size_t column,
		             size_t row_count, size_t column_count,
			     char *unicode_char, ISZ_FAIL_PARAM);
	void (*print)(void *da, FILE *file, ISZ_FAIL_PARAM);
} isz_text_canvas_i_t;

#endif /* !ISZ_I_TEXT_CANVAS_H */
