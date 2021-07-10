#ifndef ISZ_FUNCTION_GRID_TRAVERSE_H
#define ISZ_FUNCTION_GRID_TRAVERSE_H

#include "isz/common/common.h"
#include "isz/it/it.h"
#include "isz/fail/fail.h"

typedef struct isz_grid_traverse_functors_t_
{
	isz_it_functor_t field_functor;
	void *field_data;
	isz_it_functor_t line_functor;
	void *line_data;
	isz_it_functor_t back_line_functor;
	void *back_line_data;
} isz_grid_traverse_functors_t;

void isz_grid_insert(struct isz_it *field, struct isz_it *left, struct isz_it *up, struct isz_it *down, struct isz_it *right, ISZ_FAIL_PARAM);
void isz_grid_traverse(struct isz_it *first_line, struct isz_it *last_line, enum isz_direction direction, isz_grid_traverse_functors_t *functors, ISZ_FAIL_PARAM);

#endif /* !ISZ_FUNCTION_GRID_TRAVERSE_H */
