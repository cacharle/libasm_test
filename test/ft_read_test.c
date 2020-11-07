/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:44 by cacharle          #+#    #+#             */
/*   Updated: 2020/11/07 17:15:02 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

#define FT_READ_BUF_SIZE (1 << 12)

static int ft_read_pipe[2];
static char buf[FT_READ_BUF_SIZE] = {0};
static ssize_t read_ret;
static ssize_t read_origin_ret;
static int read_errno;
static int read_origin_errno;

#define FT_READ_EXPECT(str) do {                                           \
	if (pipe(ft_read_pipe) < 0)                                            \
		exit(EXIT_FAILURE);                                                \
	fcntl(ft_read_pipe[0], F_SETFL, O_NONBLOCK);                           \
	write(ft_read_pipe[1], str, strlen(str));                              \
	ERRNO_WRAP(read_origin_ret = read(ft_read_pipe[0], buf, strlen(str)), read_origin_errno);             \
	write(ft_read_pipe[1], str, strlen(str));                              \
	ERRNO_WRAP(read_ret = ft_read(ft_read_pipe[0], buf, strlen(str)), read_errno);                 \
	buf[read_ret] = '\0';                                                  \
	if (read_errno != read_origin_errno)                                   \
		printf("KO: [COMPARE]: %s: expected: errno %d got: errno %d with: "#str"\n", \
				test_name, read_origin_errno, read_errno);                           \
	else if (strcmp(buf, str) != 0 || read_ret != read_origin_ret)                       \
		printf("KO: [COMPARE]: %s: expected: %lu \"%s\" got: %lu \"%s\" with: %d, \"%s\", %zu \n", \
				test_name, strlen(str), str, read_ret, buf, ft_read_pipe[0], buf, read_origin_ret);        \
	else                                                                   \
		print_ok();                                                        \
	close(ft_read_pipe[1]);                                                \
	close(ft_read_pipe[0]);                                                \
} while (0);

#define FT_READ_EXPECT_ERROR(fd, buf, size) do {                                 \
	ERRNO_WRAP(read_ret = ft_read(fd, buf, size), read_errno);                   \
	ERRNO_WRAP(read_origin_ret = read(fd, buf, size), read_origin_errno);        \
	if ((long)read_ret != -1)                                                    \
		printf("KO: [COMPARE]: %s: expected: %ld got: %ld with: %d "#buf" %d\n", \
				test_name, -1l, (long)read_ret, fd, size);                       \
	else if (read_errno != read_origin_errno)                                    \
		printf("KO: [COMPARE]: %s: expected: errno %d got: errno %d with: %d "#buf", %d\n", \
				test_name, read_origin_errno, read_errno, fd, size);                        \
	else                                                                         \
		print_ok();                                                              \
} while (0);

static
void ft_read_test_segfault(void)
{
	int tmp[2];
	char buf_read[2048];

	if (pipe(tmp) < 0)
		exit(EXIT_FAILURE);
	write(tmp[1], "asdfkasdfkl;jasd;ljkfa;lssdlfasdfasdfasdfasdfasdfasdfasdfasdfasdf", 40);
	TEST_ASM_FUNCTION(ft_read(-1, buf_read, 2));
	TEST_ASM_FUNCTION(ft_read(tmp[0], NULL, 2));
	TEST_ASM_FUNCTION(ft_read(tmp[0], buf_read, 0));
	TEST_ASM_FUNCTION(ft_read(tmp[0], buf_read, 5));
	TEST_ASM_FUNCTION(ft_read(tmp[0], buf_read, 32));
	close(tmp[0]);
	close(tmp[1]);
	TEST_ASM_FUNCTION(ft_read(-1, buf_read, 2));
	TEST_ASM_FUNCTION(ft_read(OPEN_MAX + 1, buf_read, 2));
}

static
void ft_read_test_compare(void)
{
	FT_READ_EXPECT("");
	FT_READ_EXPECT("bon");
	FT_READ_EXPECT("bonjour");
	FT_READ_EXPECT("#c#s#p#x#X#e#f#g");
	FT_READ_EXPECT("the\0hidden");
	FT_READ_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");

	int tmp[2];
	pipe(tmp);
	char buf[32];

	write(tmp[1], "bonjour", 7);
	FT_READ_EXPECT_ERROR(tmp[0], NULL, 3);
	FT_READ_EXPECT_ERROR(-1, buf, 7);
	FT_READ_EXPECT_ERROR(42, buf, 7);
	FT_READ_EXPECT_ERROR(9809, buf, 7);
	FT_READ_EXPECT_ERROR(98123, buf, 1);
	FT_READ_EXPECT_ERROR(42, NULL, 7);
}

void ft_read_test(void)
{
	test_name = "ft_read.s";
	signaled_suite = false;
	ft_read_test_segfault();
	if (!signaled_suite)
		ft_read_test_compare();
}
