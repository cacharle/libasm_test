#include "libasm_test.h"

static t_list*
merge_sorted_list(t_list* l1, t_list* l2, int (*cmp)())
{
	t_list *merged = NULL;

	if (l1 == NULL && l2 == NULL)
		return NULL;
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l1;
	merged = cmp(l1->data, l2->data) < 0 ? l1 : l2;
	if (cmp(l1->data, l2->data) < 0)
		merged->next = merge_sorted_list(l1->next, l2, cmp);
	else
		merged->next = merge_sorted_list(l1, l2->next, cmp);
	return merged;
}

void
ref_ft_list_sort(t_list **begin_list, int (*cmp)())
{
	if (begin_list == NULL || *begin_list == NULL
			|| (*begin_list)->next == NULL)
		return ;
	t_list *fast = (*begin_list)->next;
	t_list *slow = *begin_list;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	t_list *middle = slow->next;
	slow->next = NULL;

	sortList(begin_list, cmp);
	sortList(&middle, cmp);
	*begin_list = merge_sorted_list(*begin_list, middle, cmp);
}
