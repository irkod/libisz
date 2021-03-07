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

static isz_it_t *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM);

static isz_fail_details_i_t isz_fail_details_i_value =
{
	isz_fail_details_i_dump
};

ISZ_I_TABLE_BEGIN
	ISZ_I_ENTRY(isz_fail_details)
ISZ_I_TABLE_END(isz_fail_details_errno)

ISZ_IT_NEW_DEF(isz_fail_details_errno);

void isz_fail_details_errno_init(isz_fail_details_errno_t *obj, int error)
{
	assert(obj);

	ISZ_IT_INIT(obj);
	obj->error = error;
}

isz_it_t *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	assert(vobj);

	isz_fail_details_errno_t *obj = vobj;

	isz_text_t *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_text_init_mprintf(text, ISZ_FAIL, "{ errno: %d, strerror: %s }", obj->error, strerror(obj->error));
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return &text->isz_it;
}
