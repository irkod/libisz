#ifndef ISZ_IT_GRID_LINE_H
#define ISZ_IT_GRID_LINE_H

#include "isz/common/common.h"
#include "isz/it/list.h"
#include "isz/it/text.h"
#include "isz/fail/fail.h"
#include "isz/it/it.h"
#include <stddef.h>

typedef struct isz_grid_line_t_ isz_grid_line_t;

struct isz_grid_line_t_
{
	isz_text_t id;
	isz_orientation_t orientation;
	isz_list_t fields[isz_direction_count];
	size_t traverse_in_fields_count;
	isz_it_t *traverse_in_line;
	ISZ_IT_MEMBER;
} ;

void isz_grid_line_init(isz_grid_line_t *obj, isz_orientation_t orientation);
void isz_grid_line_clear(void *vobj);

ISZ_IT_NEW_DECL(isz_grid_line);

#endif /* !ISZ_IT_GRID_LINE_H */
