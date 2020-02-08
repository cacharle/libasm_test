/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_ft_list_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 02:49:28 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 02:49:29 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static t_list*
merge_sorted_list(t_list* l1, t_list* l2, int (*cmp)(void *, void*))
{
	t_list *merged = 0x0;

	if (l1 == 0x0)
		return l2;
	if (l2 == 0x0)
		return l1;
	if (cmp(l1->data, l2->data) < 0)
	{
		merged = l1;
		merged->next = merge_sorted_list(l1->next, l2, cmp);
	}
	else
	{
		merged = l2;
		merged->next = merge_sorted_list(l1, l2->next, cmp);
	}
	return merged;
}

void
ref_ft_list_sort(t_list **begin_list, int (*cmp)(void *, void*))
{
	if (begin_list == 0x0 || *begin_list == 0x0
			|| (*begin_list)->next == 0x0)
		return ;
	t_list *fast = (*begin_list)->next;
	t_list *slow = *begin_list;
	while (fast != 0x0)
	{
		fast = fast->next;
		if (fast != 0x0)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	t_list *middle = slow->next;
	slow->next = 0x0;

	ref_ft_list_sort(begin_list, cmp);
	ref_ft_list_sort(&middle, cmp);
	*begin_list = merge_sorted_list(*begin_list, middle, cmp);
}
