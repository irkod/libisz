#ifndef ISZ_IT_TEXT_CANVAS_H
#define ISZ_IT_TEXT_CANVAS_H

#include <stddef.h>
#include "isz/it/it.h"

struct isz_text_canvas
{
	size_t row_count;
	size_t column_count;
	size_t cursor_row;
	int mb_cur_max;
	char *data;
	ISZ_IT_MEMBER;
};

void isz_text_canvas_init(struct isz_text_canvas *obj);
void isz_text_canvas_clear(void *vobj);
ISZ_IT_NEW_DECLARE(isz_text_canvas);
#endif /* !ISZ_IT_TEXT_CANVAS_H */
