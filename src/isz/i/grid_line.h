#ifndef ISZ_I_GRID_LINE_H
#define ISZ_I_GRID_LINE_H

#include "isz/common/common.h"
#include "isz/it/it.h"
#include "isz/fail/fail.h"
#include <stddef.h>

ISZ_I_ID_DECL(isz_grid_line);

typedef struct isz_grid_line_i_t_
{
	isz_orientation_t (*get_orientation)(void *vobj, ISZ_FAIL_PARAM);
	void (*add_field)(void *vobj, isz_it_t *field, isz_direction_t direction, ISZ_FAIL_PARAM);
	isz_it_t *(*get_fields)(void *vobj, isz_direction_t direction, ISZ_FAIL_PARAM);
	void (*traverse_set_in_fields_count)(void *vobj, size_t count, ISZ_FAIL_PARAM);
	size_t (*traverse_get_in_fields_count)(void *vobj, ISZ_FAIL_PARAM);
	void (*traverse_set_in_line)(void *vobj, isz_it_t *line, ISZ_FAIL_PARAM);
	isz_it_t *(*traverse_get_in_line)(void *vobj, ISZ_FAIL_PARAM);
	void (*traverse_clear_in_line)(void *vobj, ISZ_FAIL_PARAM);
	void (*set_it)(void *vobj, isz_it_t *it, ISZ_FAIL_PARAM);
	isz_it_t *(*get_it)(void *vobj, ISZ_FAIL_PARAM);
} isz_grid_line_i_t;

#endif /* !ISZ_I_GRID_LINE_H */
