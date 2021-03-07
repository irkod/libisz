#ifndef ISZ_I_SEQUENCE_H
#define ISZ_I_SEQUENCE_H

#include "isz/it/it.h"

ISZ_I_ID_DECL(isz_sequence);

typedef struct isz_sequence_i_t_
{
	void (*reset)(void *vobj);
	int (*get)(void *vobj, isz_it_t **it);
	void (*next)(void *vobj);
} isz_sequence_i_t;


#endif /* !ISZ_I_SEQUENCE_H */
