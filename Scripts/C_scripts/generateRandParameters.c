#include <string.h>
#include <stdlib.h>

int i;

void generate_alpha_string(char* output, int length) {
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int alpha_len = strlen(alphabet);

    for (i = 0; i < length; i++) {
        output[i] = alphabet[rand() % alpha_len];
    }
    output[length] = '\0';
}