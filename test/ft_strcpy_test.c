/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:58 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:59 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

#define FT_STRCPY_BUF_SIZE (1 << 12)

static char expected_buf[FT_STRCPY_BUF_SIZE] = {0};
static char actual_buf[FT_STRCPY_BUF_SIZE] = {0};

#define FT_STRCPY_EXPECT(str) do { \
	strcpy(expected_buf, str); \
	ft_strcpy(actual_buf, str); \
	if (strcmp(expected_buf, actual_buf) != 0) \
   		printf("KO: [COMPARE]: %s: expected: \"%s\" got: \"%s\"\n", test_name, expected_buf, actual_buf); \
	else \
		print_ok(); \
} while (0);


static void
ft_strcpy_test_segfault(void)
{
	char buf[FT_STRCPY_BUF_SIZE] = {0};

	TEST_ASM_FUNCTION(ft_strcpy(buf, ""));
	TEST_ASM_FUNCTION(ft_strcpy(buf, "abc"));
	TEST_ASM_FUNCTION(ft_strcpy(buf, "asl;fjl;asdjfjkasdl;fjadjsf"));
	TEST_ASM_FUNCTION(ft_strcpy(buf, "yope\0la"));
	TEST_ASM_FUNCTION(ft_strcpy(buf, "Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet."));
}

static void
ft_strcpy_test_compare(void)
{
	FT_STRCPY_EXPECT("");
	FT_STRCPY_EXPECT("abc");
	FT_STRCPY_EXPECT("asl;fjl;asdjfjkasdl;fjadjsf");
	FT_STRCPY_EXPECT("yope\0la");
	FT_STRCPY_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");
	FT_STRCPY_EXPECT("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0b\x0c\x0d\x0e\x0f");
	FT_STRCPY_EXPECT("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0b\x0c\x0d\x0e\x0f");
}

void
ft_strcpy_test(void)
{
	test_name = "ft_strcpy.s";

	ft_strcpy_test_segfault();
	if (!signaled)
		ft_strcpy_test_compare();
}
