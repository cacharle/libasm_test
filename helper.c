/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:07 by cacharle          #+#    #+#             */
/*   Updated: 2020/04/13 15:01:20 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

void print_ok(void)
{
	printf("OK: %s\n", test_name);
	fflush(stdout);
}

void print_signaled_ko(void)
{
	printf("KO: [SEGFAULT]: %s\n", test_name);
	fflush(stdout);
}
