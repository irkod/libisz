#ifndef ISZ_I_GRID_LINE_H
#define ISZ_I_GRID_LINE_H

#include "isz/common/common.h"
#include "isz/it/it.h"
#include "isz/fail/fail.h"
#include <stddef.h>

ISZ_IT_INTERFACE_ID_DECLARE(isz_grid_line);

typedef struct isz_grid_line_i_t_
{
	enum isz_orientation (*get_orientation)(void *vobj, ISZ_FAIL_PARAM);
	void (*add_field)(void *vobj, struct isz_it *field, enum isz_direction d, ISZ_FAIL_PARAM);
	struct isz_it *(*get_fields)(void *vobj, enum isz_direction d, ISZ_FAIL_PARAM);
	void (*traverse_set_in_fields_count)(void *vobj, size_t count, ISZ_FAIL_PARAM);
	size_t (*traverse_get_in_fields_count)(void *vobj, ISZ_FAIL_PARAM);
	void (*traverse_set_in_line)(void *vobj, struct isz_it *line, ISZ_FAIL_PARAM);
	struct isz_it *(*traverse_get_in_line)(void *vobj, ISZ_FAIL_PARAM);
	void (*traverse_clear_in_line)(void *vobj, ISZ_FAIL_PARAM);
	void (*set_it)(void *vobj, struct isz_it *it, ISZ_FAIL_PARAM);
	struct isz_it *(*get_it)(void *vobj, ISZ_FAIL_PARAM);
} isz_grid_line_i_t;

#endif /* !ISZ_I_GRID_LINE_H */
