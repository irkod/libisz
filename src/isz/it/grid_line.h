#ifndef ISZ_IT_GRID_LINE_H
#define ISZ_IT_GRID_LINE_H

#include "isz/common/common.h"
#include "isz/it/list.h"
#include "isz/it/text.h"
#include "isz/fail/fail.h"
#include "isz/it/it.h"
#include <stddef.h>

struct isz_grid_line
{
	struct isz_text id;
	enum isz_orientation orientation;
	struct isz_list fields[isz_direction_count];
	size_t traverse_in_fields_count;
	struct isz_it *traverse_in_line;
	ISZ_IT_MEMBER;
};

void isz_grid_line_init(struct isz_grid_line *obj, enum isz_orientation orientation);
void isz_grid_line_clear(void *vobj);

ISZ_IT_NEW_DECLARE(isz_grid_line);

#endif /* !ISZ_IT_GRID_LINE_H */
