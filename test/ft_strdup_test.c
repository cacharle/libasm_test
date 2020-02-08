/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:06 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:08:07 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static char *tmp;

#define FT_STRDUP_EXPECT(str) do {            \
	tmp = ft_strdup(str);                     \
	if (tmp == NULL || strcmp(str, tmp) != 0) \
		printf("KO: [COMPARE]: %s: expected: \"%s\" got: \"%s\"\n", test_name, str, tmp); \
	else                                      \
		print_ok();                           \
	free(tmp);                                \
} while (0);

static void
ft_strdup_test_segfault(void)
{
	char *tmp2 = NULL;
	char a;

	TEST_ASM_FUNCTION(ft_strdup(""));
	TEST_ASM_FUNCTION(ft_strdup("abc"));
	TEST_ASM_FUNCTION(ft_strdup("asl;fjl;asdjfjkasdl;fjadjsf"));
	TEST_ASM_FUNCTION(ft_strdup("yope\0la"));
	TEST_ASM_FUNCTION(ft_strdup("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet."));

	tmp2 = ft_strdup("");
	TEST_ASM_FUNCTION(a = *tmp2);
	tmp2 = ft_strdup("abc");
	TEST_ASM_FUNCTION(a = *tmp2);
	tmp2 = ft_strdup("asl;fjl;asd");
	TEST_ASM_FUNCTION(a = *tmp2);
	tmp2 = ft_strdup("yope\0la");
	TEST_ASM_FUNCTION(a = *tmp2);
}

static void
ft_strdup_test_compare(void)
{
	FT_STRDUP_EXPECT("");
	FT_STRDUP_EXPECT("abc");
	FT_STRDUP_EXPECT("asl;fjl;asdjfjkasdl;fjadjsf");
	FT_STRDUP_EXPECT("yope\0la");
	FT_STRDUP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");
	FT_STRDUP_EXPECT("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0b\x0c\x0d\x0e\x0f");
	FT_STRDUP_EXPECT("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0b\x0c\x0d\x0e\x0f");
}


void
ft_strdup_test(void)
{
	test_name = "ft_strdup.s";

	ft_strdup_test_segfault();
	if (!signaled)
		ft_strdup_test_compare();
}
