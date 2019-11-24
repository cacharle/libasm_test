#ifndef LIBASM_TEST_H
# define LIBASM_TEST_H

# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <limits.h>
# include <stddef.h>

/*
 * mandatory
 */
int
ft_strlen(char *str);
char 
*ft_strcpy(char *dst, const char *src);
int
ft_strcmp(const char *s1, const char *s2);
int
ft_write(int fildes, const void *buf, size_t buf_size);
int
ft_read(int fildes, void *buf, size_t buf_size);
char
*ft_strdup(const char *str);

/*
 * bonus
 */
int
ft_atoi_base(const char *str, const char *base);

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

void
ft_list_push_front(t_list **begin_list, void *data);
int
ft_list_size(t_list *begin_list);
void
ft_list_sort(t_list **begin_list, int (*cmp)());
void
ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

/*
 * test_functions
 */
void
ft_strlen_test(void);
void
ft_strcpy_test(void);
void
ft_strcmp_test(void);
void
ft_write_test(void);
void
ft_read_test(void);
void
ft_strdup_test(void);


/*
 * helpers
 */
void
print_ok(void);
void
print_signaled_ko(void);
void
expect_int(int expected, int actual);

/*
 * segfault tester
 */
int pid;
bool signaled;

# define TEST_SEGFAULT(x) do {        \
	if ((pid = fork()) < 0)           \
		exit(EXIT_FAILURE);           \
	if (pid == 0) {                   \
		do { x; } while(0);           \
		exit(EXIT_SUCCESS);           \
	} else {                          \
		wait(&pid);                   \
		signaled = !WIFEXITED(pid);  \
	}                                 \
} while(0);

char *test_name;

# define TEST_ASM_FUNCTION(x) do { \
	TEST_SEGFAULT(x);              \
	if (signaled)                  \
		print_signaled_ko();       \
	else                           \
		print_ok();                \
} while(0);

#endif /* LIBASM_TEST_H */
