#ifndef ISZ_I_ROW_CURSOR_H
#define ISZ_I_ROW_CURSOR_H

#include <stddef.h>
#include "isz/fail/fail.h"
#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_row_cursor);

typedef struct isz_row_cursor_i_t_
{
	void (*set)(void *vobj, size_t row);
	size_t (*get)(void *vobj);
	size_t (*move_up)(void *vobj);
	size_t (*move_down)(void *vobj);
} isz_row_cursor_i_t;

#endif /* !ISZ_I_ROW_CURSOR_H */
