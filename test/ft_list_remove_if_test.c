/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:08:42 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 20:52:06 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static int
compar(void *a, void *ref)
{
	return *(int*)a - *(int*)ref;
}

static void
free_fct(void *data)
{
	free(data);
}

static int i0 = 0;
static int i1 = 1;
static int i2 = 2;
static int i3 = 3;
static t_list *tmp;
static t_list *expected;
static t_list *actual;

#define FT_LIST_REMOVE_IF_EXPECT(fmt, ref) do {              \
	expected = list_from_format(fmt);                        \
	actual = list_from_format(fmt);                          \
	ref_ft_list_remove_if(&expected, ref, compar, free_fct); \
	ft_list_remove_if(&actual, ref, compar, free_fct);       \
	if (list_cmp(expected, actual) != 0) {                   \
		printf("KO: [COMPARE]: %s: expected: ", test_name);  \
		list_print(expected);                                \
		printf(" got: ");                                    \
		list_print(actual);                                  \
		putchar('\n');                                       \
	} else                                                   \
		print_ok();                                          \
	list_destroy(expected);                                  \
	list_destroy(actual);                                    \
} while (0);

static void
ft_list_remove_if_segfault(void)
{
	TEST_ASM_FUNCTION(tmp = list_from_format("");
					  ft_list_remove_if(&tmp, &i0, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2");
					  ft_list_remove_if(&tmp, &i3, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3");
					  ft_list_remove_if(&tmp, &i3, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3");
					  ft_list_remove_if(&tmp, &i1, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 3");
					  ft_list_remove_if(&tmp, &i2, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("987 3 9812 3 12 312 3 12491234989 3 908 3");
					  ft_list_remove_if(&tmp, &i3, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 1 1 1 1 1 1 1");
					  ft_list_remove_if(&tmp, &i1, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 1 2 1 2 1 2");
					  ft_list_remove_if(&tmp, &i1, compar, free_fct);
					  list_destroy(tmp));
	TEST_ASM_FUNCTION(tmp = list_from_format("1 2 1 2 1 2 1 2");
					  ft_list_remove_if(&tmp, &i2, compar, free_fct);
					  list_destroy(tmp));
}

static void
ft_list_remove_if_compare(void)
{
	FT_LIST_REMOVE_IF_EXPECT("", &i0);
	FT_LIST_REMOVE_IF_EXPECT("1 2", &i3);
	FT_LIST_REMOVE_IF_EXPECT("1 2 3", &i3);
	FT_LIST_REMOVE_IF_EXPECT("1 2 3", &i1);
	FT_LIST_REMOVE_IF_EXPECT("1 2 3", &i2);
	FT_LIST_REMOVE_IF_EXPECT("987 3 9812 3 12 312 3 12491234989 3 908 3", &i3);
	FT_LIST_REMOVE_IF_EXPECT("1 1 1 1 1 1 1 1", &i1);
	FT_LIST_REMOVE_IF_EXPECT("1 2 1 2 1 2 1 2", &i1);
	FT_LIST_REMOVE_IF_EXPECT("1 2 1 2 1 2 1 2", &i2);
}

void
ft_list_remove_if_test(void)
{
	test_name = "ft_list_remove_if.s";
	ft_list_remove_if_segfault();
	if (!signaled)
		ft_list_remove_if_compare();
}
