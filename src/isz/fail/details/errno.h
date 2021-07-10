#ifndef ISZ_FAIL_DETAILS_ERRNO_H
#define ISZ_FAIL_DETAILS_ERRNO_H

#include <stddef.h>
#include "isz/it/it.h"

struct isz_fail_details_errno
{
	int error;	
	ISZ_IT_MEMBER;
};

void isz_fail_details_errno_init(struct isz_fail_details_errno *obj, int error);
ISZ_IT_NEW_DECLARE(isz_fail_details_errno);
#endif /* !ISZ_FAIL_DETAILS_ERRNO_H */
