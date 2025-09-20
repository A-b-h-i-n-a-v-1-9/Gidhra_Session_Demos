// patchme.c
// flip a branch (patching demo)
#include <stdio.h>
#include <string.h>

static int check(const char *s) {
    // Intentionally structured so a single conditional jump controls success.
    // Goal in Ghidra: flip the outcome without knowing the password.
    if (strcmp(s, "SETPASS") == 0) {
        return 1; // success
    }
    return 0;     // fail
}

int main(void) {
    char input[64];
    printf("PatchMe: enter code: ");
    if (!fgets(input, sizeof(input), stdin)) return 1;
    input[strcspn(input, "\r\n")] = '\0';

    if (check(input)) {
        puts("OK -> Access Granted");
    } else {
        puts("NO -> Access Denied");
    }
    return 0;
}
