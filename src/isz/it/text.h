#ifndef ISZ_IT_TEXT_H
#define ISZ_IT_TEXT_H

#include <stddef.h>
#include "isz/fail/fail.h"
#include "isz/it/it.h"

typedef struct isz_text_t_
{
	char *str;
	int owns;
	ISZ_IT_MEMBER;
} isz_text_t;

void isz_text_init_look(isz_text_t *obj, char *str);
void isz_text_init_take(isz_text_t *obj, char *str);
void isz_text_init_copy(isz_text_t *obj, const char *str, ISZ_FAIL_PARAM);
void isz_text_init_mprintf(isz_text_t *obj, ISZ_FAIL_PARAM, const char *format, ...);
void isz_text_clear(void *vobj);
ISZ_IT_NEW_DECL(isz_text);
#endif /* !ISZ_IT_TEXT_H */
