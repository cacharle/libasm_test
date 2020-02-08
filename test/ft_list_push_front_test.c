/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_front_test.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:24 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:08:25 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static t_list *tmp;
static t_list *expected;
static t_list *actual;

#define FT_LIST_PUSH_FRONT_EXPECT(fmt, push) do {             \
	expected = list_from_format(fmt);                         \
	actual = list_from_format(fmt);                           \
	ref_ft_list_push_front(&expected, create_data_elem(push)); \
	ft_list_push_front(&actual, create_data_elem(push));       \
	if (list_cmp(expected, actual) != 0) {                    \
		printf("KO: [COMPARE]: %s: expected: ", test_name);   \
		list_print(expected);                                 \
		printf(" got: ");                                     \
		list_print(actual);                                   \
		putchar('\n');                                        \
	} else                                                    \
		print_ok();                                           \
	list_destroy(expected);                                   \
	list_destroy(actual);                                     \
} while (0);

static void
ft_list_push_front_segfault(void)
{
	TEST_ASM_FUNCTION(tmp = NULL; ft_list_push_front(&tmp, malloc(1));list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3"); ft_list_push_front(&tmp, create_data_elem(34)); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3 4 10"); ft_list_push_front(&tmp, create_data_elem(1)); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("111234 1234 1112"); ft_list_push_front(&tmp, create_data_elem(7)); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2"); ft_list_push_front(&tmp, create_data_elem(0)); list_destroy(tmp));
	TEST_ASM_FUNCTION(
		tmp = list_from_format("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20");
		ft_list_push_front(&tmp, create_data_elem(4));
		ft_list_push_front(&tmp, create_data_elem(4));
		ft_list_push_front(&tmp, create_data_elem(4));
		ft_list_push_front(&tmp, create_data_elem(4));
		list_destroy(tmp);
	);
}

static void
ft_list_push_front_compare(void)
{
	FT_LIST_PUSH_FRONT_EXPECT("", 0);
	FT_LIST_PUSH_FRONT_EXPECT("", 1);
	FT_LIST_PUSH_FRONT_EXPECT("0", 1);
	FT_LIST_PUSH_FRONT_EXPECT("1 2 3", 4);
	FT_LIST_PUSH_FRONT_EXPECT("1 2 3", -1);
	FT_LIST_PUSH_FRONT_EXPECT("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20", 7);
}

void
ft_list_push_front_test(void)
{
	test_name = "ft_list_push_front.s";
	ft_list_push_front_segfault();
	if (!signaled)
		ft_list_push_front_compare();
}
