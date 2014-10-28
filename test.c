#include <stdio.h>
#include <string.h>
#include "signal.h"

char test_user[32];

void switch_user(char *user) {
    strncpy(test_user, user, 31);
}

int login(char *test_pass) {
    printf("%s:%s\n", test_user, test_pass);
    return LOGIN_FAILURE;
}
