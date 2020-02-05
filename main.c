#include "libasm_test.h"

int
main(void)
{
	ft_strlen_test();
	ft_strcpy_test();
	ft_strcmp_test();
#ifndef __linux__
	ft_write_test();
	ft_read_test();
#endif
	ft_strdup_test();

	ft_atoi_base_test();
	ft_list_push_front_test();
	ft_list_size_test();
	/* ft_list_sort_test(); */
	/* ft_list_remove_if_test(); */
	return 0;
}
