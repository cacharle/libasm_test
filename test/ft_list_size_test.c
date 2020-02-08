/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:20 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:08:21 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static t_list *tmp;
static int expected;
static int actual;

#define FT_LIST_SIZE_EXPECT(fmt) do {              \
	tmp = list_from_format(fmt);                   \
	expected = ref_ft_list_size(tmp);              \
	actual = ft_list_size(tmp);                    \
	if (expected != actual) {                      \
		printf("KO: [COMPARE]: %s: expected: %d ", \
				test_name, expected);              \
		list_print(tmp);                           \
		printf(" got: %d\n", actual);              \
	} else                                         \
		print_ok();                                \
	list_destroy(tmp);                             \
} while (0);

static void
ft_list_size_segfault(void)
{
	TEST_ASM_FUNCTION(tmp = list_from_format(""); ft_list_size(tmp); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3"); ft_list_size(tmp); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3 4 10"); ft_list_size(tmp); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("111234 1234 1112"); ft_list_size(tmp); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2"); ft_list_size(tmp); list_destroy(tmp));
	TEST_ASM_FUNCTION(
		tmp = list_from_format("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
		ft_list_size(tmp);
		list_destroy(tmp)
	);
}

static void
ft_list_size_compare(void)
{
	FT_LIST_SIZE_EXPECT("1 2 3");
	FT_LIST_SIZE_EXPECT("");
	FT_LIST_SIZE_EXPECT("1 2 3 4 10");
	FT_LIST_SIZE_EXPECT("19879 123 12344");
	FT_LIST_SIZE_EXPECT("1");
	FT_LIST_SIZE_EXPECT("1 2");
	FT_LIST_SIZE_EXPECT("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
}

void
ft_list_size_test(void)
{
	test_name = "ft_list_size.s";
	ft_list_size_segfault();
	if (!signaled)
		ft_list_size_compare();
}
