#ifndef ISZ_FAIL_DETAILS_NO_I_H
#define ISZ_FAIL_DETAILS_NO_I_H

#include <stddef.h>
#include "isz/it/it.h"

typedef struct isz_fail_details_no_i_t_
{
	isz_i_id_t *id;	
	ISZ_IT_MEMBER;
} isz_fail_details_no_i_t;

void isz_fail_details_no_i_init(isz_fail_details_no_i_t *obj, isz_i_id_t *id);
ISZ_IT_NEW_DECL(isz_fail_details_no_i);
#endif /* !ISZ_FAIL_DETAILS_NO_I_H */
