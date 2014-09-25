/**
 * @file
 * @brief utility functions for tests
 *
 * (c) CossackLabs
 */

#include "test_utils.h"
#include <string.h>

static uint8_t parse_char(char c)
{
	if ((c >= '0') && (c <= '9'))
		return (uint8_t)(c - '0');

	if ((c >= 'A') && (c <= 'F'))
		return (uint8_t)(c - 'A' + 0xa);

	if ((c >= 'a') && (c <= 'f'))
		return (uint8_t)(c - 'a' + 0xa);

	return 0xff;
}

test_utils_status_t string_to_bytes(const char *str, uint8_t *bytes, size_t size)
{
	size_t str_size = strlen(str);
	size_t i;

	/* strings with hex data should at least be even in size */
	if (0x1 & str_size)
		return HERMES_INVALID_PARAMETER;

	/* check if we have enough memory for output */
	if (size < (str_size / 2))
		return HERMES_BUFFER_TOO_SMALL;

	for (i = 0; i < str_size; i += 2)
	{
		uint8_t upper = parse_char(str[i]);
		uint8_t lower = parse_char(str[i + 1]);

		if ((0xf0 & upper) || (0xf0 & lower))
			return HERMES_INVALID_PARAMETER;

		bytes[i / 2] = lower | (upper << 4);
	}

	return HERMES_SUCCESS;
}