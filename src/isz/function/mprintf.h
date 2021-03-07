#ifndef ISZ_FUNCTION_MPRINTF_H
#define ISZ_FUNCTION_MPRINTF_H

#include <stddef.h>
#include <stdarg.h>

char *isz_mprintf(const char *format, ...);
size_t isz_vmprintf_size(const char *format, va_list ap);
char *isz_vmprintf_str(const char *format, size_t size, va_list ap);

#endif /* !ISZ_FUNCTION_MPRINTF_H */
