/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_test.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:19 by cacharle          #+#    #+#             */
/*   Updated: 2020/12/09 12:53:01 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# ifdef __linux__
#  define OPEN_MAX FOPEN_MAX
# endif

/*
 * mandatory
 */
int   ft_strlen(char *str);
char* ft_strcpy(char *dst, const char *src);
int   ft_strcmp(const char *s1, const char *s2);
int   ft_write(int fildes, const void *buf, size_t buf_size);
int   ft_read(int fildes, void *buf, size_t buf_size);
char* ft_strdup(const char *str);

/*
 * bonus
 */
# ifdef LIBASM_TEST_BONUS
int ft_atoi_base(const char *str, const char *base);

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

void ft_list_push_front(t_list **begin_list, void *data);
int  ft_list_size(t_list *begin_list);
void ft_list_sort(t_list **begin_list, int (*cmp)());
void ft_list_remove_if(t_list **begin_list, void *data_ref,
					   int (*cmp)(), void (*free_fct)(void *));
# endif

/*
 * test_functions
 */
void ft_strlen_test(void);
void ft_strcpy_test(void);
void ft_strcmp_test(void);
void ft_write_test(void);
void ft_read_test(void);
void ft_strdup_test(void);

# ifdef LIBASM_TEST_BONUS
void ft_atoi_base_test(void);
void ft_list_push_front_test(void);
void ft_list_size_test(void);
void ft_list_sort_test(void);
void ft_list_remove_if_test(void);
# endif


/*
 * helpers
 */
void print_ok(void);
void print_signaled_ko(const char *code);

# ifdef LIBASM_TEST_BONUS
int*    create_data_elem(int data);
t_list* create_elem(int data);
t_list* list_from_format(char *fmt);
t_list* list_dup(t_list *list);
int     list_cmp(t_list *l1, t_list *l2);
void    list_print(t_list *list);
void    list_destroy(t_list *list);
# endif

/*
 * function of reference
 */
# ifdef LIBASM_TEST_BONUS
int  ref_ft_atoi_base(char *str, char *base);
void ref_ft_list_push_front(t_list **begin_list, void *data);
int  ref_ft_list_size(t_list *begin_list);
void ref_ft_list_sort(t_list **begin_list, int (*cmp)());
void ref_ft_list_remove_if(t_list **begin_list, void *data_ref,
							int (*cmp)(), void (*free_fct)(void *));
# endif

/*
 * segfault tester
 */
extern int  pid;
extern bool signaled;
extern bool signaled_suite;

# define TEST_SEGFAULT(x) do {               \
	if ((pid = fork()) < 0)                  \
		exit(EXIT_FAILURE);                  \
	if (pid == 0) {                          \
		do { x; } while(0);                  \
		exit(EXIT_SUCCESS);                  \
	} else {                                 \
		wait(&pid);                          \
		signaled = WIFSIGNALED(pid);         \
		if (signaled) signaled_suite = true; \
	}                                        \
} while(0)

extern char *test_name;

# define TEST_ASM_FUNCTION(x) do {       \
	TEST_SEGFAULT(x);                    \
	if (signaled)                        \
		print_signaled_ko(#x);           \
	else                                 \
		print_ok();                      \
} while(0)

# define ERRNO_WRAP(x, errno_save) do {  \
	errno = 0;                           \
	do { x; } while (0);                 \
	errno_save = errno;                  \
} while(0)

#endif
