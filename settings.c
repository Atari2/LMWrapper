#include "settings.h"
struct settings {
    unsigned int max_line_length;
    char* listfile;
};

// general functions
void error(const char* const format, ...) {
    va_list va;
    va_start(va, format);
    vprintf(format, va);
    va_end(va);
    printf("\nPress any key to exit\n");
    fflush(stdin);
    getc(stdin);
    exit(1);
}

FILE* safeopen(const char* filename, const char* mode, int fatal) {
    FILE* fp = fopen(filename, mode);
    if (fp == NULL && fatal)
        error("Couldn't open file %s in mode %s", filename, mode);
    return fp;
}

// settings functions
settings* initSettings() {
    settings* s = malloc(sizeof(settings));
    s->listfile = calloc(MAX_LINE_LENGTH, sizeof(char));
    setValues(s, 4095u, "programList.txt");
    return s;
}

void setValues(settings* s, unsigned int llength, const char* listfile) {
    s->max_line_length = llength;
    strcpy(s->listfile, listfile);
}
unsigned int getLineLength(settings* s) {
    return s->max_line_length;
}

const char* getListfile(settings* s) {
    return s->listfile;
}

void readSettings(settings* s, FILE* ini) {
    if (ini == NULL)
        return;
    char line[MAX_LINE_LENGTH];
    char listfile[MAX_LINE_LENGTH];
    char setting[MAX_LINE_LENGTH];
    int llength, nprogs, temp = 0;
    int n = 0;
    while (fgets(line, MAX_LINE_LENGTH, ini) != NULL) {
        printf("%s", line);
        n = sscanf(line, "%[^:]: %u", setting, &temp);
        if (n != 2) {
            sscanf(line, "%[^:]: %s", setting, listfile);
        }
        while (isspace(setting[strlen(setting) - 1]) || setting[strlen(setting) - 1] == ':') {
            setting[strlen(setting) - 1] = '\0';
        }
        if (strcmp(setting, "max_line_length") == 0) {
            llength = temp;
        } else if (strcmp(setting, "list_filename") == 0) {
            while(isspace(listfile[strlen(listfile) - 1]))
                listfile[strlen(listfile) - 1] = '\0';
        } else {
            error("Unrecognized settings option %s", setting);
        }
    }
    setValues(s, llength, listfile);
}

void printSettings(settings* s, FILE* fp) {
    fprintf(fp, "%s %d\n", s->listfile, s->max_line_length);
}