#ifndef ISZ_I_DUMP_H
#define ISZ_I_DUMP_H

#include "isz/it/it.h"
#include "isz/fail/fail.h"

ISZ_I_ID_DECL(isz_dump);

typedef struct isz_dump_i_t_
{
	isz_it_t *(*get)(void *vobj, ISZ_FAIL_PARAM);
} isz_dump_i_t;

#endif /* !ISZ_I_DUMP_H */
