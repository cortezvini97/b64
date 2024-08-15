# Base64 Library in C

This is a simple Base64 encoding and decoding library implemented in C. It provides functions to encode and decode data in Base64 format.

## Functions

### `char *base64_encode(const unsigned char *data, size_t input_length, size_t *output_length)`

Encodes the given data in Base64 format.

- **Parameters:**
  - `data`: Pointer to the input data.
  - `input_length`: Length of the input data.
  - `output_length`: Pointer to a size_t variable where the length of the encoded output will be stored.

- **Returns:** 
  - A pointer to the encoded Base64 string. The caller is responsible for freeing the allocated memory.

### `unsigned char *base64_decode(const char *data, size_t input_length, size_t *output_length)`

Decodes the given Base64 encoded string.

- **Parameters:**
  - `data`: Pointer to the Base64 encoded string.
  - `input_length`: Length of the Base64 encoded string.
  - `output_length`: Pointer to a size_t variable where the length of the decoded output will be stored.

- **Returns:** 
  - A pointer to the decoded data. The caller is responsible for freeing the allocated memory. Returns `NULL` if the input is not valid Base64.

## Installation

To compile and install the library, follow these steps:

1. Clone the repository:

    ```sh
    git clone https://github.com/cortezvini97/b64.git
    ```

2. Navigate to the cloned directory:

    ```sh
    cd b64
    ```

3. Compile the library:

    ```sh
    make
    ```

4. Install the library:

    ```sh
    sudo make install
    ```

## Usage

After installation, you can include the `b64.h` header file in your C programs and link against the library to use the encoding and decoding functions.

### Example

```c
#include <stdio.h>
#include "b64.h"

int main() {
    const char *text = "Hello, World!";
    size_t encoded_len;
    char *encoded = base64_encode((const unsigned char *)text, strlen(text), &encoded_len);

    if (encoded) {
        printf("Encoded: %s\n", encoded);

        size_t decoded_len;
        unsigned char *decoded = base64_decode(encoded, encoded_len, &decoded_len);

        if (decoded) {
            printf("Decoded: %.*s\n", (int)decoded_len, decoded);
            free(decoded);
        }

        free(encoded);
    }

    return 0;
}
