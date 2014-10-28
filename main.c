#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

void *module;

void cleanup(void) {
    dlclose(module);
}

int main(int argc, char **argv) {
    void (*test)();

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

    test = dlsym(module, "test");
    if (test == NULL) {
        puts("couldn't find symbol test");
        return 1;
    }

    test();
    
    return 0;
}
