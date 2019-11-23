#include "libasm_test.h"


void
print_ok(void)
{
	printf("OK: %s\n", test_name);
}

void
print_stack_alignment_error(void)
{
	printf("KO: [STACK ALIGNMENT]: %s\n", test_name);
}

void
print_signaled_ko(void)
{
	printf("KO: [SEGFAULT]: %s\n", test_name);
}

void
expect_int(int expected, int actual)
{
	if (actual != expected)
   		printf("KO:	[COMPARE]: %s: expected: %d got: %d\n", test_name, expected, actual);
	else
		print_ok();
}
