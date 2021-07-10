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

void isz_grid_insert(isz_it_t *field, isz_it_t *left, isz_it_t *up, isz_it_t *down, isz_it_t *right, ISZ_FAIL_PARAM);
void isz_grid_traverse(isz_it_t *first_line, isz_it_t *last_line, isz_direction_t direction, isz_grid_traverse_functors_t *functors, ISZ_FAIL_PARAM);

#endif /* !ISZ_FUNCTION_GRID_TRAVERSE_H */
