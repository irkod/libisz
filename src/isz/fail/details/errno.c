#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "isz/fail/details/errno.h"
#include "isz/it/it.h"
#include "isz/it/text.h"
#include "isz/function/mprintf.h"
#include "isz/i/fail_details.h"
#include "isz/fail/fail.h"

ISZ_FAIL_FILE(isz_program_id);

static struct isz_it *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM);

static isz_fail_details_i_t isz_fail_details_interface_value =
{
	isz_fail_details_i_dump
};

ISZ_IT_INTERFACE_TABLE_BEGIN
	ISZ_IT_INTERFACE_TABLE_ENTRY(isz_fail_details)
ISZ_IT_INTERFACE_TABLE_END(isz_fail_details_errno);

ISZ_IT_NEW_DEFINE(isz_fail_details_errno);

void isz_fail_details_errno_init(struct isz_fail_details_errno *obj, int error)
{
	assert(obj);

	ISZ_IT_INIT(obj);
	obj->error = error;
}

struct isz_it *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	assert(vobj);

	struct isz_fail_details_errno *obj = vobj;

	struct isz_text *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_text_init_mprintf(text, ISZ_FAIL, "{ errno: %d, strerror: %s }", obj->error, strerror(obj->error));
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return &text->isz_it;
}
