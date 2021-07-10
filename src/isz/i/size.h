#ifndef ISZ_I_SIZE_H
#define ISZ_I_SIZE_H

#include <stddef.h>
#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_size);

typedef struct isz_size_i_t_
{
	size_t (*get)(void *vobj);
} isz_size_i_t;

#endif /* !ISZ_I_SIZE_H */
