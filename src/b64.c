#include "b64.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int base64_char_value(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c >= 'a' && c <= 'z') return c - 'a' + 26;
    if (c >= '0' && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1; // Retorna -1 para padding ou caracteres inválidos
}


char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length) {
    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char *)malloc(*output_length + 1);  // Corrigido: Conversão explícita de void* para char*
    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded_data[j++] = base64_table[(triple >> 18) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 12) & 0x3F];
        encoded_data[j++] = base64_table[(triple >> 6) & 0x3F];
        encoded_data[j++] = base64_table[triple & 0x3F];
    }

    // Ajustando padding manualmente
    size_t mod = input_length % 3;
    if (mod > 0) {
        for (size_t i = 0; i < 3 - mod; i++) {
            encoded_data[*output_length - 1 - i] = '=';
        }
    }

    encoded_data[*output_length] = '\0';
    return encoded_data;
}


unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length) {
    if (input_length % 4 != 0) return NULL; // Base64 deve ter comprimento múltiplo de 4

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = (unsigned char *)malloc(*output_length);  // Corrigido: Conversão explícita de void* para unsigned char*
    if (decoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {

        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : base64_char_value(data[i++]);
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : base64_char_value(data[i++]);
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : base64_char_value(data[i++]);
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : base64_char_value(data[i++]);

        uint32_t triple = (sextet_a << 18)
                        + (sextet_b << 12)
                        + (sextet_c << 6)
                        + sextet_d;

        if (j < *output_length) decoded_data[j++] = (triple >> 16) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = triple & 0xFF;
    }

    return decoded_data;
}