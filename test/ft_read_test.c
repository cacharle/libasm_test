/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:44 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:45 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

#define FT_READ_BUF_SIZE (1 << 12)

static int ft_read_pipe[2];
static char buf[FT_READ_BUF_SIZE];
static int ret;

#define FT_READ_EXPECT(str) do {                                           \
	if (pipe(ft_read_pipe) < 0)                                            \
		exit(EXIT_FAILURE);                                                \
	fcntl(ft_read_pipe[0], F_SETFL, O_NONBLOCK);                           \
	write(ft_read_pipe[1], str, strlen(str));                              \
	ret = ft_read(ft_read_pipe[0], buf, strlen(str));                      \
	buf[ret] = '\0';                                                       \
	if (strcmp(buf, str) != 0 || ret != strlen(str))                       \
		printf("KO: [COMPARE]: %s: expected: %lu \"%s\" got: %d \"%s\"\n", \
				test_name, strlen(str), str, ret, buf);                    \
	else                                                                   \
		print_ok();                                                        \
	close(ft_read_pipe[1]);                                                \
	close(ft_read_pipe[0]);                                                \
} while (0);

void
ft_read_test_segfault(void)
{
	int tmp[2];
	if (pipe(tmp) < 0)
		exit(EXIT_FAILURE);
	TEST_ASM_FUNCTION(ft_read(tmp[1], "test", 5));
	TEST_ASM_FUNCTION(ft_read(tmp[1], "t", 1));
	TEST_ASM_FUNCTION(ft_read(tmp[1], "", 0));
	TEST_ASM_FUNCTION(ft_read(tmp[1], "test", 4));
	TEST_ASM_FUNCTION(ft_read(tmp[1], "test", 2));
	TEST_ASM_FUNCTION(ft_read(tmp[1], NULL, 2));
	close(tmp[0]);
	close(tmp[1]);
	TEST_ASM_FUNCTION(ft_read(-1, "tt", 2));
	TEST_ASM_FUNCTION(ft_read(OPEN_MAX + 1, "tt", 2));
}

void
ft_read_test_compare(void)
{
	FT_READ_EXPECT("");
	FT_READ_EXPECT("bon");
	FT_READ_EXPECT("bonjour");
	FT_READ_EXPECT("%c%s%p%x%X%e%f%g");
	FT_READ_EXPECT("the\0hidden");
	FT_READ_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");
}

void
ft_read_test(void)
{
	test_name = "ft_read.s";

	ft_read_test_segfault();
	if (!signaled)
		ft_read_test_compare();
}
