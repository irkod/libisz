#ifndef ISZ_FAIL_DETAILS_ERRNO_H
#define ISZ_FAIL_DETAILS_ERRNO_H

#include <stddef.h>
#include "isz/it/it.h"

typedef struct isz_fail_details_errno_t_
{
	int error;	
	ISZ_IT_MEMBER;
} isz_fail_details_errno_t;

void isz_fail_details_errno_init(isz_fail_details_errno_t *obj, int error);
ISZ_IT_NEW_DECL(isz_fail_details_errno);
#endif /* !ISZ_FAIL_DETAILS_ERRNO_H */
