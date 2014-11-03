#include <stdio.h>
#include <string.h>
#include "signal.h"

int login(char *user, char *pass) {
    printf("%s:%s\n", user, pass);
    return LOGIN_FAILURE;
}
