#include "libasm_test.h"

void
ref_ft_list_push_front(t_list **begin_list, void *data)
{

	if (begin_list == NULL || data == NULL)
		return ;
	data->next = *begin_list;
	*begin_list = data;
}
