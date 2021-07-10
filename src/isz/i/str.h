#ifndef ISZ_I_STR_H
#define ISZ_I_STR_H

#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_str);

typedef struct isz_str_i_t_
{
	char *(*get)(void *vobj);
} isz_str_i_t;

#endif /* !ISZ_STR_I_H */
