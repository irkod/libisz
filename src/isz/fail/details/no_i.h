#ifndef ISZ_FAIL_DETAILS_NO_I_H
#define ISZ_FAIL_DETAILS_NO_I_H

#include <stddef.h>
#include "isz/it/it.h"

struct isz_fail_details_no_i
{
	isz_it_interface_id_t *id;	
	ISZ_IT_MEMBER;
};

void isz_fail_details_no_i_init(struct isz_fail_details_no_i *obj, isz_it_interface_id_t *id);
ISZ_IT_NEW_DECLARE(isz_fail_details_no_i);
#endif /* !ISZ_FAIL_DETAILS_NO_I_H */
