/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:03 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:08:03 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static void
ft_strcmp_test_segfault(void)
{
	TEST_ASM_FUNCTION(ft_strcmp("", ""));
	TEST_ASM_FUNCTION(ft_strcmp("bon", "bon"));
	TEST_ASM_FUNCTION(ft_strcmp("bonjour", "bonjour"));
	TEST_ASM_FUNCTION(ft_strcmp("%c%s%p%x%X%e%f%g", "%c%s%p%x%X%e%f%g"));
	TEST_ASM_FUNCTION(ft_strcmp("the\0hidden", "the\0hidden"));
	TEST_ASM_FUNCTION(ft_strcmp("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.",
"Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet."));
}

int strcmp_expected;
int strcmp_actual;

#ifdef __linux__
# define FT_STRCMP_EXPECT(s1, s2) do { \
	strcmp_expected = strcmp(s1, s2); \
	strcmp_actual = ft_strcmp(s1, s2); \
	if ((strcmp_expected < 0 && strcmp_actual < 0) || \
	    (strcmp_expected > 0 && strcmp_actual > 0) || \
	    (strcmp_expected == 0 && strcmp_actual == 0)) \
		print_ok(); \
	else \
		printf("KO: [COMPARE]: ft_strcmp.s: expected: %d got: %d\n", \
			   strcmp_expected, strcmp_actual); \
} while (0);
#else
# define FT_STRCMP_EXPECT(s1, s2) expect_int(strcmp(s1, s2), ft_strcmp(s1, s2))
#endif

static void
ft_strcmp_test_compare(void)
{
	FT_STRCMP_EXPECT("", "");
	FT_STRCMP_EXPECT("bon", "");
	FT_STRCMP_EXPECT("bonjour", "");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "");
	FT_STRCMP_EXPECT("the\0hidden", "");
	FT_STRCMP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.", "");
	FT_STRCMP_EXPECT("", "");
	FT_STRCMP_EXPECT("bon", "bon");
	FT_STRCMP_EXPECT("bonjour", "bonjour");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "%c%s%p%x%X%e%f%g");
	FT_STRCMP_EXPECT("the\0hidden", "the\0hidden");
	FT_STRCMP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.",
"Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");

	FT_STRCMP_EXPECT("", "asdf");
	FT_STRCMP_EXPECT("bon", "bo");
	FT_STRCMP_EXPECT("bonjour", "onjour");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "%s%p%x%X%e%f%g");
	FT_STRCMP_EXPECT("the\0hidden", "thehidden");
	FT_STRCMP_EXPECT("Lorem ipsum dolor st amet, consectetur adipiscing", "Lodsfsdfasdf");

	FT_STRCMP_EXPECT("\x01", "\x01");
	FT_STRCMP_EXPECT("\x02", "\x01");
	FT_STRCMP_EXPECT("\x01", "\x02");
	FT_STRCMP_EXPECT("\xff", "\xff");
	FT_STRCMP_EXPECT("\xfe", "\xff");
	FT_STRCMP_EXPECT("\xff", "\xfe");

	FT_STRCMP_EXPECT("\x01\x01", "\x01");
	FT_STRCMP_EXPECT("\x01\x02", "\x01");
	FT_STRCMP_EXPECT("\x02\x01", "\x02");
	FT_STRCMP_EXPECT("\xff\xff", "\xff");
	FT_STRCMP_EXPECT("\xff\xfe", "\xff");
	FT_STRCMP_EXPECT("\xfe\xff", "\xfe");

	FT_STRCMP_EXPECT("\x01", "\x01\x01");
	FT_STRCMP_EXPECT("\x01", "\x01\x02");
	FT_STRCMP_EXPECT("\x02", "\x02\x01");
	FT_STRCMP_EXPECT("\xff", "\xff\xff");
	FT_STRCMP_EXPECT("\xff", "\xff\xfe");
	FT_STRCMP_EXPECT("\xfe", "\xfe\xff");
}

void
ft_strcmp_test(void)
{
	test_name = "ft_strcmp.s";

	ft_strcmp_test_segfault();
	if (!signaled)
		ft_strcmp_test_compare();
}
