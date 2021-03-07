#ifndef ISZ_I_FAIL_DETAILS_H
#define ISZ_I_FAIL_DETAILS_H

#include "isz/it/it.h"

struct isz_fail_node_t_;

ISZ_I_ID_DECL(isz_fail_details);

typedef struct isz_fail_details_i_t_
{
	isz_it_t *(*dump)(void *vobj, struct isz_fail_node_t_ *isz_fail_node);
} isz_fail_details_i_t;

#endif /* !ISZ_I_FAIL_DETAILS_H */
