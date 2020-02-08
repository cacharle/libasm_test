/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:53 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:53 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static void
ft_strlen_test_segfault(void)
{
	TEST_ASM_FUNCTION(ft_strlen(""));
	TEST_ASM_FUNCTION(ft_strlen("bon"));
	TEST_ASM_FUNCTION(ft_strlen("bonjour"));
	TEST_ASM_FUNCTION(ft_strlen("%c%s%p%x%X%e%f%g"));
	TEST_ASM_FUNCTION(ft_strlen("the\0hidden"));
	TEST_ASM_FUNCTION(ft_strlen("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet."));
}

#define FT_STRLEN_EXPECT(str) expect_int(strlen(str), ft_strlen(str))

static void
ft_strlen_test_compare(void)
{
	FT_STRLEN_EXPECT("");
	FT_STRLEN_EXPECT("bon");
	FT_STRLEN_EXPECT("bonjour");
	FT_STRLEN_EXPECT("%c%s%p%x%X%e%f%g");
	FT_STRLEN_EXPECT("the\0hidden");
	FT_STRLEN_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");
}

void
ft_strlen_test(void)
{
	test_name = "ft_strlen.s";
	ft_strlen_test_segfault();
	if (!signaled)
		ft_strlen_test_compare();
}
