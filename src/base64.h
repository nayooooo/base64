/*
 * Copyright (c) 2026, nayooooo
 *
 * SPDX-License-Identifier: MIT
 *
 * @brief base64
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-01-01     nayooooo     the first version
 */

#ifndef __BASE64_H__
#define __BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef NULL
#define NULL ((void *)0)
#endif

#define BASE64_PAD                '='
#define BASE64_GROUP_SIZE         (4)

int base64(uint8_t *data, uint32_t len, uint8_t *result, uint32_t size);
int base64_decode(uint8_t *data, uint32_t len, uint8_t *result, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* __BASE64_H__ */
