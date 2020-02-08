/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_sort_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:15 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 20:39:51 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static int
compar_int(void *a, void *b)
{
	return *(int*)a - *(int*)b;
}

static t_list *tmp;
static t_list *expected;
static t_list *actual;

#define FT_LIST_SORT_EXPECT(fmt) do {                       \
	expected = list_from_format(fmt);                       \
	actual = list_from_format(fmt);                         \
	ref_ft_list_sort(&expected, compar_int);                \
	ft_list_sort(&actual, compar_int);                      \
	if (list_cmp(expected, actual) != 0) {                  \
		printf("KO: [COMPARE]: %s: expected: ", test_name); \
		list_print(expected);                               \
		printf(" got: ");                                   \
		list_print(actual);                                 \
		putchar('\n');                                      \
	} else                                                  \
		print_ok();                                         \
	list_destroy(expected);                                 \
	list_destroy(actual);                                   \
} while (0);

/* t_list* */
/* st_merge_sorted_list(t_list* l1, t_list* l2, int (*cmp)(void *, void*)); */

static void
ft_list_sort_segfault(void)
{
	TEST_ASM_FUNCTION(tmp = list_from_format(""); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("-1 0 1 2 3 4 5 6"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("98 12 12 45 1 -1 232 34 23"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("12 45 1 -1 232 34 23 87879"); ft_list_sort(&tmp, compar_int); list_destroy(tmp));
}

static void
ft_list_sort_compare(void)
{
	FT_LIST_SORT_EXPECT("");
	FT_LIST_SORT_EXPECT("1");
	FT_LIST_SORT_EXPECT("1 2");
	FT_LIST_SORT_EXPECT("1 2 3");
	FT_LIST_SORT_EXPECT("-1 0 1 2 3 4 5 6");
	FT_LIST_SORT_EXPECT("98 12 12 45 1 -1 232 34 23");
	FT_LIST_SORT_EXPECT("12 45 1 -1 232 34 23 87879");
}

void
ft_list_sort_test(void)
{
	test_name = "ft_list_sort.s";
	ft_list_sort_segfault();
	if (!signaled)
		ft_list_sort_compare();
}
