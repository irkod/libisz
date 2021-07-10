#ifndef ISZ_I_ID_H
#define ISZ_I_ID_H

#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_id);

typedef struct isz_id_i_t_
{
	void (*set)(void *vobj, const char *id, ISZ_FAIL_PARAM);
	const char *(*get)(void *vobj);
} isz_id_i_t;

#endif /* !ISZ_I_ID_H */
