/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_ft_list_remove_if.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:20:03 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 20:02:25 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

void
ref_ft_list_remove_if(t_list **begin_list, void *data_ref,
						int (*cmp)(), void (*free_fct)(void *))
{
	t_list *saved_next;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	if (cmp((*begin_list)->data, data_ref) != 0)
	{
		ref_ft_list_remove_if(&(*begin_list)->next, data_ref, cmp, free_fct);
		return ;
	}
	saved_next = (*begin_list)->next;
	free_fct((*begin_list)->data);
	free(*begin_list);
	*begin_list = saved_next;
	ref_ft_list_remove_if(begin_list, data_ref, cmp, free_fct);
}
