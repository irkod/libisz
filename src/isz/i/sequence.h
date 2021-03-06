#ifndef ISZ_I_SEQUENCE_H
#define ISZ_I_SEQUENCE_H

#include "isz/it/it.h"

ISZ_IT_INTERFACE_ID_DECLARE(isz_sequence);

typedef struct isz_sequence_i_t_
{
	void (*reset)(void *vobj);
	int (*peek)(void *vobj, struct isz_it **it);
	void (*next)(void *vobj);
} isz_sequence_i_t;


#endif /* !ISZ_I_SEQUENCE_H */
