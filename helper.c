/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:08 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"


void
print_ok(void)
{
	printf("OK: %s\n", test_name);
	fflush(stdout);
}

void
print_signaled_ko(void)
{
	printf("KO: [SEGFAULT]: %s\n", test_name);
	fflush(stdout);
}

void
expect_int(int expected, int actual)
{
	if (actual != expected)
		printf("KO: [COMPARE]: %s: expected: %d got: %d\n", test_name, expected, actual);
	else
		print_ok();
	fflush(stdout);
}
