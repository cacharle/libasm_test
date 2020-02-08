/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_ft_list_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:20:11 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:20:12 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

int
ref_ft_list_size(t_list *begin_list)
{
	int counter;

	counter = 0;
	while (begin_list != NULL)
	{
		counter++;
		begin_list = begin_list->next;
	}
	return counter;
}
