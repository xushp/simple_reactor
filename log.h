#include <stdarg.h>
#include <stdio.h>
#include <string.h>
namespace log {
//#define LOG fprintf(stdout, "Error:[%s,%s](%s/%s:Line %d)\n",       \
    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__)
#define COLOR_RED   "\033[0;32;31m"
#define COLOR_NON   "\033[0;m"
#define LOG_HEAD "\033[0;32;31m[%s] [%s] [%s/%s:%d]"
inline
void log(const char *_format, ...) {
  va_list list;
  int len_log_head = strlen(LOG_HEAD);
  int len_format = strlen(_format);
  char * str_temp = new char[len_log_head + len_format + strlen(COLOR_NON) + 1];
  sprintf(str_temp, "%s%s"COLOR_NON, LOG_HEAD, _format);
  va_start(list, str_temp);
  vfprintf(stdout, str_temp, list);
  va_end(list);
  delete []str_temp;
  putchar('\n');
}

#define LOG(_format, ...) log::log(_format,       \
                                   __DATE__,      \
                                   __TIME__,      \
                                   __FILE__,      \
                                   __FUNCTION__,  \
                                   __LINE__,      \
                                   ## __VA_ARGS__)

}
