#include "libasm_test.h"

int
ref_ft_list_size(t_list *begin_list)
{
	int counter;

	counter = 0;
	while (begin_list)
	{
		counter++
		begin_list = begin_list->next;
	}
	return counter;
}


