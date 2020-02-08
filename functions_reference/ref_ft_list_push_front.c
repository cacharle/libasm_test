/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref_ft_list_push_front.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:20:23 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:20:24 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

void
ref_ft_list_push_front(t_list **begin_list, void *data)
{
	if (begin_list == NULL)
		return ;
	t_list *new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	new->data = data;
	new->next = *begin_list;
	*begin_list = new;
}
