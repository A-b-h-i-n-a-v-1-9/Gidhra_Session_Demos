// crackme_with_unused.c
// strings → xrefs → decompiler

#include <stdio.h>
#include <string.h>

// Unused bait strings (for Ghidra Strings window)
static const char *UNUSED_1 = "SuperSecretBackdoor123!";
static const char *UNUSED_2 = "root:toor";
static const char *UNUSED_3 = "flag{definitely_not_used}";

int main(void) {
    char input[64];

    puts("=== Hello Crackme ===");
    printf("Enter license key: ");
    if (!fgets(input, sizeof(input), stdin)) return 1;

    // strip newline if present
    input[strcspn(input, "\r\n")] = '\0';

    if (strcmp(input, "ABCD1234") == 0) {
        puts("Access Granted!");
    } else {
        puts("Access Denied.");
    }

    puts("Notice: not all strings in a binary are used!");
    return 0;
}
