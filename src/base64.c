#include "base64.h"

static const uint8_t base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int _base64_character_is_valid(uint8_t c)
{
    if (c == BASE64_PAD) {
        return 1;
    }

    for (uint32_t i = 0; i < sizeof(base64_table) / sizeof(base64_table[0]) - 1; i++) {
        if (c == base64_table[i]) {
            return 2;
        }
    }

    return 0;
}

static int _base64_character_to_number(uint8_t c)
{
    for (uint32_t i = 0; i < sizeof(base64_table) / sizeof(base64_table[0]) - 1; i++) {
        if (c == base64_table[i]) {
            return (int)i;
        }
    }

    return -1;
}

int base64(uint8_t *data, uint32_t len, uint8_t *result, uint32_t size)
{
    uint32_t encode_len = 0;
    uint32_t group = 0;
    uint32_t encoding_idx = 0;
    uint8_t encoding_val = 0;
    uint32_t idx = 0;
    uint8_t mask = (1 << 6) - 1;

    if (data == NULL || result == NULL || len <= 0 || size <= 0) {
        return -1;
    }

    encode_len = 8ULL * len / 6 + ((8ULL * len % 6) ? 1 : 0);
    group = encode_len / BASE64_GROUP_SIZE + ((encode_len % BASE64_GROUP_SIZE) ? 1 : 0);
    if (encode_len <= 0 || group <= 0) {
        return -2;
    }
    if (size < group * BASE64_GROUP_SIZE) {
        return -3;
    }

    for (uint32_t i = 0; i < len; i++) {
        uint8_t byte = data[i];
        for (uint32_t j = 0; j < 8; j++) {
            encoding_val = (encoding_val << 1) & mask;
            encoding_val |= (data[i] >> (7 - j)) & 0x1;
            idx++;
            if (idx == 6) {
                result[encoding_idx++] = base64_table[encoding_val];
                encoding_val = 0;
                idx = 0;
            }
        }
    }
    if (idx > 0) {
        encoding_val = (encoding_val << (6 - idx)) & mask;
        result[encoding_idx++] = base64_table[encoding_val];
    }

    for (uint32_t i = 0; i < group * BASE64_GROUP_SIZE - encode_len; i++) {
        result[encoding_idx++] = BASE64_PAD;
    }

    return (int)encoding_idx;
}

int base64_decode(uint8_t *data, uint32_t len, uint8_t *result, uint32_t size)
{
    uint32_t decoding_idx = 0;
    uint8_t decoding_val = 0;
    uint32_t idx = 0;
    uint8_t mask = (1 << 6) - 1;
    uint8_t base64_val = 0;
    int ret;

    if (data == NULL || result == NULL || len <= 0 || size <= 0) {
        return -1;
    }

    if (len % BASE64_GROUP_SIZE) {
        return -2;
    }
    if (!_base64_character_is_valid(data[len - 1])) {
        return -3;
    }

    for (uint32_t i = 0; i < len; i++) {
        ret = _base64_character_is_valid(data[i]);
        if (ret == 0) {
            return -4;
        } else if (ret == 1) {
            break;
        } else {
            base64_val = _base64_character_to_number(data[i]) & mask;
            for (uint32_t j = 0; j < 6; j++) {
                decoding_val <<= 1;
                decoding_val |= (base64_val >> (5 - j)) & 0x1;
                idx++;
                if (idx == 8) {
                    result[decoding_idx++] = decoding_val;
                    // decoding_val = 0;
                    idx = 0;
                }
            }
        }
    }

    return (int)decoding_idx;
}
