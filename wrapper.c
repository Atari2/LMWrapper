#include <windows.h>
#include "settings.h"

int main(int argc, char* argv[]) {
    if (strcmp(argv[argc - 1], "-h") == 0 || strcmp(argv[argc - 1], "--help") == 0 || argc == 1) {
        printf("Usage:\n");
        printf("Place this executable in your LM folder and create a text file called \"programList.txt\" always in your LM folder\n");
        printf("Each line needs to be a command to you want to be executed (e.g. \"pixi.exe rom.smc\")\n");
        printf("Then create a file called \"usertoolbar.txt\" in your LM folder and write the following into it (or use the provided one):\n");
        printf("***START***\n\"lmwrapper.exe\" \"%%9\"\n***END***\n");
        printf("The next time you'll open LM, you'll have a new icon in the toolbar, pressing on that icon will run all the commands in \"programList.txt\" and reload the rom.\n");
        printf("For additional information, such as creating your own settings file, check out the readme\n");
        printf("Press any key to exit");
        fflush(stdin);
        getc(stdin);
        return 0;
    }
    if (argc != 2)
        error("Wrong number of command line parameters, expected 2 got %d", argc);
    const char* lm_handle = argv[argc-1];
    unsigned short int verification_code = 0;
    HWND window_handle = 0;
    const char* config = "lmwrapper.ini";
    FILE* conf = safeopen(config, "r", 0);
    settings* setts = initSettings();
    int success;
    readSettings(setts, conf);
    fclose(conf);
    char* buffer = malloc(getLineLength(setts));
    FILE* list = safeopen(getListfile(setts), "r", 1);
    while (fgets(buffer, getLineLength(setts), list) != NULL) {
        success = system(buffer);
        if (success == -1) {
            error("Call to %s failed", buffer);
        }
    }
    fclose(list);
    window_handle = (HWND)(LONG_PTR)strtoull(lm_handle, NULL, 16);
    char* pos_of = strchr(lm_handle, ':') + 1;
    verification_code = (strtoul(pos_of, NULL, 16) & 0xFFFFu);
    unsigned int IParam = (verification_code << 16) + 2;
    int retval = PostMessage(window_handle, 0xBECB, 0, IParam);
    free(setts);
    free(buffer);
    return retval;
}