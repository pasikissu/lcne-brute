#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "signal.h"

void *module;

void cleanup(void) {
    dlclose(module);
}

int main(int argc, char **argv) {
    int (*login)(char *, char*);

    if (argc < 2) {
        printf("%s module\n", argv[0]);
        return 1;
    }

    module = dlopen(argv[1], RTLD_NOW);
    if (module == NULL) {
        printf("failed to load module %s\n", argv[1]);
        return 1;
    }

    atexit(cleanup);

    login = dlsym(module, "login");
    if (login == NULL) {
        puts("couldn't resolve symbols");
        return 1;
    }

    char *user[] = {"root", "toor"};
    char *pass[] = {"1234", "pass", "letmein"};
    int u, p;

    for (u = 0; u < sizeof(user)/sizeof(char*); u++) {
        for (p = 0; p < sizeof(pass)/sizeof(char*); p++) {
            if (login(user[u], pass[p]) == LOGIN_SUCCESS) {
                printf("%s:%s\n", user[u], pass[p]);
                return 0;
            }
        }
    }

    return 0;
}
