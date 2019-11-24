#include "libasm_test.h"

static t_list*
create_elem(int data)
{
	int *data_ptr = malloc(sizeof(int));
	if (data_ptr == NULL)
		return (NULL);
	t_list *new = malloc(sizeof(t_list));
	if (new == NULL)
		return NULL;
	new->data = data_ptr;
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

	while (*fmt)
	{
		int n = ft_atoi(*fmt);
		t_list *elem = create_elem(n);
		push_front(&head, elem);
		while (isdigit(*fmt))
			fmt++;
		if (*fmt)
			fmt++;
	}
	return head;
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
list_cmp(t_list *l1, t_list l2)
{
	if (l1 == NULL && l2 == NULL)
		return 0;
	if (l1 == NULL)
		return -1;
	if (l2 == NULL)
		return 1;
	if (*(int*)l1->data != *(int*)l2->data)
		return *(int*)l1->data - *(int*)l2->data;
	return list_cmp(l1->next, l2->next);
}

void
list_print(t_list *list)
{
	while (list != NULL)
		printf("[%d] -> ", *(int*)list->data);
	printf("(null)\n");
}
