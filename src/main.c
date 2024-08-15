#include "b64.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>

int main() {
    const char *input = "hello world";
    size_t encoded_length, decoded_length;

    // Codificação
    char *encoded = base64_encode((const unsigned char *)input, strlen(input), &encoded_length);
    if (encoded) {
        printf("Encoded: %s\n", encoded);

        // Decodificação
        unsigned char *decoded = base64_decode(encoded, encoded_length, &decoded_length);
        if (decoded) {
            printf("Decoded: %.*s\n", (int)decoded_length, decoded);
            free(decoded);
        } else {
            printf("Failed to decode.\n");
        }

        free(encoded);
    } else {
        printf("Failed to encode.\n");
    }

    return 0;
}