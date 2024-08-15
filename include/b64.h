#ifndef B64_H
#define B64_H

#include <stddef.h>


char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length);
unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length);

#endif // B64_H