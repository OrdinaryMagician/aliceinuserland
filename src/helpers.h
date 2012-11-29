#ifndef HELPERS_H
#define HELPERS_H
bool isin( const char c, const char *set );
void nprints( const char *s, const int len );
int ctoh( const char c);
void pututf8( unsigned long int unichar );
char* toutf8( unsigned long int unichar );
int descape( const char *str );
#endif
