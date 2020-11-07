/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:48 by cacharle          #+#    #+#             */
/*   Updated: 2020/11/07 17:15:12 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

#define FT_WRITE_BUF_SIZE (1 << 12)

static int ft_write_pipe[2];
static char buf[FT_WRITE_BUF_SIZE] = {0};
static ssize_t write_ret;
static ssize_t write_origin_ret;
static int write_errno;
static int write_origin_errno;
static ssize_t ret;

#define FT_WRITE_EXPECT(str) do {                                                                  \
	if (pipe(ft_write_pipe) < 0)                                                                   \
		exit(EXIT_FAILURE);                                                                        \
	fcntl(ft_write_pipe[0], F_SETFL, O_NONBLOCK);                                                  \
	ERRNO_WRAP(write_origin_ret = write(ft_write_pipe[1], str, strlen(str)), write_origin_errno);  \
	read(ft_write_pipe[0], buf, FT_WRITE_BUF_SIZE);                                                \
	ERRNO_WRAP(write_ret = ft_write(ft_write_pipe[1], str, strlen(str)), write_errno);             \
	ret = read(ft_write_pipe[0], buf, FT_WRITE_BUF_SIZE);                                          \
	buf[ret] = '\0';                                                                               \
	if (write_errno != write_origin_errno)                                                         \
		printf("KO: [COMPARE]: %s: expected: errno %d got: errno %d with: "#str"\n",               \
				test_name, write_origin_errno, write_errno);                                       \
	else if (strcmp(buf, str) != 0 || write_ret != write_origin_ret)                               \
		printf("KO: [COMPARE]: %s: expected: %lu \"%s\" got: %lu \"%s\" with: %d, \"%s\", %zu \n", \
				test_name, strlen(str), str, write_ret, buf, ft_write_pipe[0], buf, strlen(str));  \
	else                                                                                           \
		print_ok();                                                                                \
	close(ft_write_pipe[1]);                                                                       \
	close(ft_write_pipe[0]);                                                                       \
} while (0);

#define FT_WRITE_EXPECT_ERROR(fd, str, size) do {                                           \
	ERRNO_WRAP(write_ret = ft_write(fd, str, size), write_errno);                           \
	ERRNO_WRAP(write_origin_ret = write(fd, str, size), write_origin_errno);                \
	if ((long)write_ret != -1)                                                              \
		printf("KO: [COMPARE]: %s: expected: %ld got: %ld with: %d "#str", %d\n",           \
				test_name, -1l, (long)write_ret, fd, size);                                 \
	else if (write_errno != write_origin_errno)                                             \
		printf("KO: [COMPARE]: %s: expected: errno %d got: errno %d with: %d "#str", %d\n", \
				test_name, write_origin_errno, write_errno, fd, size);                      \
	else                                                                                    \
		print_ok();                                                                         \
} while (0);

static
void ft_write_test_segfault(void)
{
	int tmp[2];
	if (pipe(tmp) < 0)
		exit(EXIT_FAILURE);
	TEST_ASM_FUNCTION(ft_write(-1, "test", 5));
	TEST_ASM_FUNCTION(ft_write(tmp[1], NULL, 5));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "test", 0));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "test", 5));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "t", 1));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "", 0));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "test", 4));
	TEST_ASM_FUNCTION(ft_write(tmp[1], "test", 2));
	TEST_ASM_FUNCTION(ft_write(tmp[1], NULL, 2));
	close(tmp[0]);
	close(tmp[1]);
	TEST_ASM_FUNCTION(ft_write(-1, "tt", 2));
	TEST_ASM_FUNCTION(ft_write(OPEN_MAX + 1, "tt", 2));
}

static
void ft_write_test_compare(void)
{
	FT_WRITE_EXPECT("");
	FT_WRITE_EXPECT("bon");
	FT_WRITE_EXPECT("bonjour");
	FT_WRITE_EXPECT("#c#s#p#x#X#e#f#g");
	FT_WRITE_EXPECT("the\0hidden");
	FT_WRITE_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");

	FT_WRITE_EXPECT_ERROR(STDOUT_FILENO, NULL, 3);
	FT_WRITE_EXPECT_ERROR(-1, "bonjour", 7);
	FT_WRITE_EXPECT_ERROR(42, "bonjour", 7);
	FT_WRITE_EXPECT_ERROR(9809, "bonjour", 7);
	FT_WRITE_EXPECT_ERROR(98123, "", 1);
	FT_WRITE_EXPECT_ERROR(42, NULL, 7);
}

void ft_write_test(void)
{
	test_name = "ft_write.s";
	signaled_suite = false;
	ft_write_test_segfault();
	if (!signaled_suite)
		ft_write_test_compare();
}
