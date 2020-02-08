/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:48 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:49 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

#define FT_WRITE_BUF_SIZE (1 << 12)

static int ft_write_pipe[2];
static char buf[FT_WRITE_BUF_SIZE];
static unsigned long write_ret;
static int ret;

#define FT_WRITE_EXPECT(str) do {                                           \
	if (pipe(ft_write_pipe) < 0)                                            \
		exit(EXIT_FAILURE);                                                 \
	fcntl(ft_write_pipe[0], F_SETFL, O_NONBLOCK);                           \
	write_ret = ft_write(ft_write_pipe[1], str, strlen(str));               \
	ret = read(ft_write_pipe[0], buf, FT_WRITE_BUF_SIZE);                   \
	buf[ret] = '\0';                                                        \
	if (strcmp(buf, str) != 0 || write_ret != strlen(str))                  \
		printf("KO: [COMPARE]: %s: expected: %lu \"%s\" got: %lu \"%s\"\n", \
				test_name, strlen(str), str, write_ret, buf);               \
	else                                                                    \
		print_ok();                                                         \
	close(ft_write_pipe[1]);                                                \
	close(ft_write_pipe[0]);                                                \
} while (0);

void
ft_write_test_segfault(void)
{
	int tmp[2];
	if (pipe(tmp) < 0)
		exit(EXIT_FAILURE);
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

void
ft_write_test_compare(void)
{
	FT_WRITE_EXPECT("");
	FT_WRITE_EXPECT("bon");
	FT_WRITE_EXPECT("bonjour");
	FT_WRITE_EXPECT("%c%s%p%x%X%e%f%g");
	FT_WRITE_EXPECT("the\0hidden");
	FT_WRITE_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");
}

void
ft_write_test(void)
{
	test_name = "ft_write.s";

	ft_write_test_segfault();
	if (!signaled)
		ft_write_test_compare();
}
