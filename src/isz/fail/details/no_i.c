#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "isz/fail/details/errno.h"
#include "isz/it/it.h"
#include "isz/it/text.h"
#include "isz/function/mprintf.h"
#include "isz/i/fail_details.h"
#include "isz/fail/fail.h"
#include "isz/fail/details/no_i.h"

ISZ_FAIL_FILE(isz_program_id);

static isz_it_t *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM);

static isz_fail_details_i_t isz_fail_details_i_value =
{
	isz_fail_details_i_dump
};

ISZ_I_TABLE_BEGIN
	ISZ_I_ENTRY(isz_fail_details)
ISZ_I_TABLE_END(isz_fail_details_no_i)

ISZ_IT_NEW_DEF(isz_fail_details_no_i);

void isz_fail_details_no_i_init(isz_fail_details_no_i_t *obj, isz_i_id_t *id)
{
	assert(obj);

	ISZ_IT_INIT(obj);
	obj->id = id;
}

isz_it_t *isz_fail_details_i_dump(void *vobj, ISZ_FAIL_PARAM)
{
	ISZ_FAIL_NEXT_VAL(NULL);

	assert(vobj);

	isz_fail_details_no_i_t *obj = vobj;

	isz_text_t *text = isz_text_new(ISZ_FAIL);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	isz_text_init_mprintf(text, ISZ_FAIL, "{ interface: %s }", *obj->id);
	ISZ_FAIL_RET_CALL_IF_VAL(NULL);

	return &text->isz_it;
}
