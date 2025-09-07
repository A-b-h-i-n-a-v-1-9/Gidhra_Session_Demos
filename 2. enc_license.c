// enc_license.c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Cleartext target (not present in binary as plain text): "GHIDRA-2025"
// Encoded with XOR key 0x3A -> bytes below:
static uint8_t secret_enc[] = { 0x7d,0x72,0x73,0x7e,0x68,0x7b,0x17,0x08,0x0a,0x08,0x0f };
static const uint8_t XOR_KEY = 0x3A;

static void xor_decode(uint8_t *buf, size_t len, uint8_t k) {
    for (size_t i = 0; i < len; i++) buf[i] ^= k;
}

int main(void) {
    char input[64];
    uint8_t buf[sizeof(secret_enc)];
    memcpy(buf, secret_enc, sizeof(secret_enc));
    xor_decode(buf, sizeof(buf), XOR_KEY); // runtime decode

    printf("Enter license key: ");
    if (!fgets(input, sizeof(input), stdin)) return 1;
    input[strcspn(input, "\r\n")] = '\0';

    if (strncmp(input, (char*)buf, sizeof(buf)) == 0) {
        puts("Access Granted!");
    } else {
        puts("Access Denied.");
    }
    return 0;
}
