#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 250

typedef struct settings settings;

settings* initSettings();
void setValues(settings*, unsigned int, const char*);
unsigned int getLineLength(settings*);
const char* getListfile(settings*);
void readSettings(settings*, FILE*);
void error(const char* const, ...);
FILE* safeopen(const char*, const char*, int);
void printSettings(settings*, FILE*);