#include <stdio.h>
#include <string.h>

#include "../src/base64.h"

#define ENCODE_TIMES            (5)
#define DECODE_TIMES            ENCODE_TIMES

#define BUFF_SIZE               (1024)

int main(void)
{
    uint8_t data[BUFF_SIZE] = "hello base64!";
    uint8_t base[BUFF_SIZE] = { 0 };
    int len;

    printf("\n==================================================\n");
    len = strlen(data);
    printf("data(%d):\n", len);
    printf("%s\n", data);
    // encode
    for (uint32_t i = 0; i < ENCODE_TIMES; i++) {
        memset(base, 0, BUFF_SIZE);
        len = strlen(data);
        len = base64(data, len, base, BUFF_SIZE);
        for (uint32_t j = 0; j < i + 1; j++) {
            printf("  ");
        }
        printf("base64(%d):\n", len);
        for (uint32_t j = 0; j < i + 1; j++) {
            printf("  ");
        }
        printf("%s\n", base);
        memcpy(data, base, BUFF_SIZE);
    }
    // decode
    for (uint32_t i = 0; i < DECODE_TIMES; i++) {
        memset(base, 0, BUFF_SIZE);
        len = strlen(data);
        len = base64_decode(data, len, base, BUFF_SIZE);
        for (uint32_t j = 0; j < DECODE_TIMES - 1 - i; j++) {
            printf("  ");
        }
        printf("decode base64(%d):\n", len);
        for (uint32_t j = 0; j < DECODE_TIMES - 1 - i; j++) {
            printf("  ");
        }
        printf("%s\n", base);
        memcpy(data, base, BUFF_SIZE);
    }
    printf("\n==================================================\n");

    return 0;
}
