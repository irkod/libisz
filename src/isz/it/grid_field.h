#ifndef ISZ_IT_GRID_FIELD_H
#define ISZ_IT_GRID_FIELD_H

#include "isz/common/common.h"
#include "isz/it/node.h"
#include "isz/it/it.h"
#include "isz/it/text.h"
#include <stddef.h>

typedef struct isz_grid_field_t_
{
	isz_text_t id;
	isz_it_t *line[isz_orientation_count][isz_direction_count];
	isz_node_t siblings_node[isz_orientation_count][isz_direction_count];
	ISZ_IT_MEMBER;
} isz_grid_field_t;

void isz_grid_field_init(isz_grid_field_t *obj);
void isz_grid_field_clear(void *vobj);

ISZ_IT_NEW_DECL(isz_grid_field);
#endif /* !ISZ_IT_GRID_FIELD_H */
