/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/12/09 12:52:33 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

void print_ok(void)
{
	printf("OK: %s\n", test_name);
	fflush(stdout);
}

void print_signaled_ko(const char *code)
{
	printf("KO: [SEGFAULT]: %s: with: %s\n", test_name, code);
	fflush(stdout);
}
