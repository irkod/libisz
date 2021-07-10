#ifndef ISZ_IT_TEXT_H
#define ISZ_IT_TEXT_H

#include <stddef.h>
#include "isz/fail/fail.h"
#include "isz/it/it.h"

struct isz_text
{
	char *str;
	int owns;
	ISZ_IT_MEMBER;
};

void isz_text_init_look(struct isz_text *obj, char *str);
void isz_text_init_take(struct isz_text *obj, char *str);
void isz_text_init_copy(struct isz_text *obj, const char *str, ISZ_FAIL_PARAM);
void isz_text_init_mprintf(struct isz_text *obj, ISZ_FAIL_PARAM, const char *format, ...);
void isz_text_clear(void *vobj);
ISZ_IT_NEW_DECLARE(isz_text);
#endif /* !ISZ_IT_TEXT_H */
