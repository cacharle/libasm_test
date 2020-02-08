/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:14 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:15 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

int*
create_data_elem(int data)
{
	int *data_ptr = malloc(sizeof(int));
	if (data_ptr == NULL)
		return (NULL);
	*data_ptr = data;
	return data_ptr;
}

t_list*
create_elem(int data)
{
	t_list *new = malloc(sizeof(t_list));
	if (new == NULL)
		return NULL;
	if ((new->data = create_data_elem(data)) == NULL)
		return (NULL);
	new->next = NULL;
	return new;
}

static void
push_front(t_list **lst_ptr, t_list *new_front)
{
	if (lst_ptr == NULL || new_front == NULL)
		return ;
	new_front->next = *lst_ptr;
	*lst_ptr = new_front;
}

static t_list*
reverse(t_list *list)
{
	if (list == NULL || list->next == NULL)
		return list;
	t_list *tmp = reverse(list->next);
	list->next->next = list;
	list->next = NULL;
	return tmp;
}

t_list*
list_from_format(char *fmt)
{
	t_list *head = NULL;

	while (fmt != NULL && *fmt)
	{
		int n = (int)strtol(fmt, &fmt, 10);
		t_list *elem = create_elem(n);
		push_front(&head, elem);
	}
	return reverse(head);
}

t_list*
list_dup(t_list *list)
{
	t_list *dup_head = NULL;

	while (list != NULL)
	{
		t_list *tmp = create_elem(*(int*)list->data);
		push_front(&dup_head, tmp);
	}
	return reverse(dup_head);
}

int
list_cmp(t_list *l1, t_list *l2)
{
	if (l1 == NULL && l2 == NULL)
		return 0;
	if (l1 == NULL)
		return -1;
	if (l2 == NULL)
		return 1;
	if (l1->data == NULL)
		return -1;
	if (l2->data == NULL)
		return 1;
	if (*(int*)l1->data != *(int*)l2->data)
		return *(int*)l1->data - *(int*)l2->data;
	return list_cmp(l1->next, l2->next);
}

void
list_print(t_list *list)
{
	while (list != NULL)
	{
		printf("[%d] -> ", *(int*)list->data);
		list = list->next;
	}
	printf("(null)");
}

void
list_destroy(t_list *list)
{
	if (list == NULL)
		return ;
	list_destroy(list->next);
	if (list->data != NULL)
		free(list->data);
	free(list);
}
