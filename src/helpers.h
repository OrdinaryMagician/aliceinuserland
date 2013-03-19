#ifndef HELPERS_H
#define HELPERS_H
#include <stdbool.h>
int bail( const char *fmt, ... );
bool isin( const char c, const char *set );
void nprints( const char *s, const int len );
int ctoh( const char c);
void pututf8( unsigned long unichar );
char* toutf8( unsigned long unichar );
int descape( const char *str );
#endif
