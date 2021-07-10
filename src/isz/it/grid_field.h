#ifndef ISZ_IT_GRID_FIELD_H
#define ISZ_IT_GRID_FIELD_H

#include "isz/common/common.h"
#include "isz/it/node.h"
#include "isz/it/it.h"
#include "isz/it/text.h"
#include <stddef.h>

struct isz_grid_field
{
	struct isz_text id;
	struct isz_it *line[isz_orientation_count][isz_direction_count];
	struct isz_node siblings_node[isz_orientation_count][isz_direction_count];
	ISZ_IT_MEMBER;
};

void isz_grid_field_init(struct isz_grid_field *obj);
void isz_grid_field_clear(void *vobj);

ISZ_IT_NEW_DECLARE(isz_grid_field);
#endif /* !ISZ_IT_GRID_FIELD_H */
