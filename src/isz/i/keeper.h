#ifndef ISZ_I_KEEPER_H
#define ISZ_I_KEEPER_H

#include "isz/it/it.h"
#include "isz/it/node.h"
#include "isz/fail/fail.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_keeper);

typedef struct isz_keeper_i_t_
{
	void (*add)(void *vobj, struct isz_node *node, ISZ_FAIL_PARAM);
	void (*clear)(void *vobj);
} isz_keeper_i_t;

#endif /* !ISZ_I_KEEPER_H */
