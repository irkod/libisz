#ifndef ISZ_PAGE_FIELD_I_H
#define ISZ_PAGE_FIELD_I_H

#include "isz/common/common.h"
#include "isz/it/node.h"
#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_grid_field);

typedef struct isz_grid_field_i_t_
{
	void (*set_line)(void *vobj, struct isz_it *line,
		       	 enum isz_orientation orientation, enum isz_direction direction, ISZ_FAIL_PARAM);
	struct isz_it *(*get_line)(void *vobj, enum isz_orientation orientation, enum isz_direction direction, ISZ_FAIL_PARAM);
	struct isz_node *(*get_siblings_node)(void *vobj,
		       		 	 enum isz_orientation orientation, enum isz_direction direction, ISZ_FAIL_PARAM);
	void (*set_it)(void *vobj, struct isz_it *it, ISZ_FAIL_PARAM);
	struct isz_it *(*get_it)(void *vobj, ISZ_FAIL_PARAM);
} isz_grid_field_i_t;

#endif /* !ISZ_PAGE_FIELD_I_H */
