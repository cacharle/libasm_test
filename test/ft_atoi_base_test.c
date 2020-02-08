/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_test.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacharle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 03:07:27 by cacharle          #+#    #+#             */
/*   Updated: 2020/02/08 03:07:38 by cacharle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_test.h"

static int expected_ret;
static int actual_ret;

	/* asm("movq $0xffffffffffffffff, %rax"); \ */
#define FT_ATOI_BASE_EXPECT(str, base) do {      \
	actual_ret = ft_atoi_base(str, base);        \
	expected_ret = ref_ft_atoi_base(str, base);  \
	if (actual_ret != expected_ret)              \
		printf("KO: [COMPARE]: %s: expected: %d got: %d with: "#str", "#base"\n", \
				test_name, expected_ret, actual_ret); \
	else                                         \
		print_ok();                              \
} while (0);

static void
ft_atoi_base_segfault(void)
{
	TEST_ASM_FUNCTION(ft_atoi_base("", ""));
	TEST_ASM_FUNCTION(ft_atoi_base("10", ""));
	TEST_ASM_FUNCTION(ft_atoi_base("", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("123", "0123456789"));
	TEST_ASM_FUNCTION(ft_atoi_base("101", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("ffe0", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("\t\n\r\v\f\r 4", "01234"));
	TEST_ASM_FUNCTION(ft_atoi_base("45", ""));
	TEST_ASM_FUNCTION(ft_atoi_base("45", "0"));
	TEST_ASM_FUNCTION(ft_atoi_base("45", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("10", "011"));
	TEST_ASM_FUNCTION(ft_atoi_base("10", "0+"));
	TEST_ASM_FUNCTION(ft_atoi_base("10", "-0"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "\t541"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "98\n541"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "7\r541"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "0\v541"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "1\f541"));
	TEST_ASM_FUNCTION(ft_atoi_base("10111", "54 1"));
	TEST_ASM_FUNCTION(ft_atoi_base("111000", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("52", "01234567"));
	TEST_ASM_FUNCTION(ft_atoi_base("2a", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("7fffffff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", "0123-456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", "01\r23456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", "abcc"));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", ""));
	TEST_ASM_FUNCTION(ft_atoi_base("ff", "a"));
	TEST_ASM_FUNCTION(ft_atoi_base("-ff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("--ff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("+--ff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("-++++++-+--ff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("-++++++-+--ff\xff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("-+\r++-+--ff\xff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("-01", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("--11101", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("+-123", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("-++++01++-+--ff", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("-++10101\xff", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("-+\r++-+--01\x01", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("a\0bb", "ab"));
	TEST_ASM_FUNCTION(ft_atoi_base("-b\0bb", "ab"));
	TEST_ASM_FUNCTION(ft_atoi_base(" \t\n\r-++++++-+--ff\xff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("  -+\r++-+--ff\xff", "0123456789abcdef"));
	TEST_ASM_FUNCTION(ft_atoi_base("\n-01", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base("\x0b--11101", "01"));
	TEST_ASM_FUNCTION(ft_atoi_base(" 755x+", "01234567"));
	TEST_ASM_FUNCTION(ft_atoi_base(" 700chmod", "01234567"));
	TEST_ASM_FUNCTION(ft_atoi_base(" 644yo", "01234567"));
	TEST_ASM_FUNCTION(ft_atoi_base(TO_STRING(INT_MAX), "0123456789"));
	TEST_ASM_FUNCTION(ft_atoi_base(TO_STRING(INT_MIN), "0123456789"));
}

static void
ft_atoi_base_compare(void)
{
	FT_ATOI_BASE_EXPECT("", "");
	FT_ATOI_BASE_EXPECT("10", "");
	FT_ATOI_BASE_EXPECT("", "01");
	FT_ATOI_BASE_EXPECT("123", "0123456789");
	FT_ATOI_BASE_EXPECT("101", "01");
	FT_ATOI_BASE_EXPECT("ffe0", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("\t\n\r\v\f\r 4", "01234");
	FT_ATOI_BASE_EXPECT("45", "");
	FT_ATOI_BASE_EXPECT("45", "0");
	FT_ATOI_BASE_EXPECT("45", "01");
	FT_ATOI_BASE_EXPECT("10", "011");
	FT_ATOI_BASE_EXPECT("10", "0+");
	FT_ATOI_BASE_EXPECT("10", "-0");
	FT_ATOI_BASE_EXPECT("10111", "\t541");
	FT_ATOI_BASE_EXPECT("10111", "98\n541");
	FT_ATOI_BASE_EXPECT("10111", "7\r541");
	FT_ATOI_BASE_EXPECT("10111", "0\v541");
	FT_ATOI_BASE_EXPECT("10111", "1\f541");
	FT_ATOI_BASE_EXPECT("10111", "54 1");
	FT_ATOI_BASE_EXPECT("111000", "01");
	FT_ATOI_BASE_EXPECT("ff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("52", "01234567");
	FT_ATOI_BASE_EXPECT("2a", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("7fffffff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("ff", "0123-456789abcdef");
	FT_ATOI_BASE_EXPECT("ff", "01\r23456789abcdef");
	FT_ATOI_BASE_EXPECT("ff", "abcc");
	FT_ATOI_BASE_EXPECT("ff", "");
	FT_ATOI_BASE_EXPECT("ff", "a");
	FT_ATOI_BASE_EXPECT("-ff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("--ff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("+--ff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("-++++++-+--ff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("-++++++-+--ff\xff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("-+\r++-+--ff\xff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("-01", "01");
	FT_ATOI_BASE_EXPECT("--11101", "01");
	FT_ATOI_BASE_EXPECT("+-123", "01");
	FT_ATOI_BASE_EXPECT("-++++01++-+--ff", "01");
	FT_ATOI_BASE_EXPECT("-++10101\xff", "01");
	FT_ATOI_BASE_EXPECT("-+\r++-+--01\x01", "01");
	FT_ATOI_BASE_EXPECT("a\0bb", "ab");
	FT_ATOI_BASE_EXPECT("-b\0bb", "ab");
	FT_ATOI_BASE_EXPECT(" \t\n\r-++++++-+--ff\xff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("  -+\r++-+--ff\xff", "0123456789abcdef");
	FT_ATOI_BASE_EXPECT("\n-01", "01");
	FT_ATOI_BASE_EXPECT("\x0b--11101", "01");
	FT_ATOI_BASE_EXPECT(" 755x+", "01234567");
	FT_ATOI_BASE_EXPECT(" 700chmod", "01234567");
	FT_ATOI_BASE_EXPECT(" 644yo", "01234567");
	FT_ATOI_BASE_EXPECT(TO_STRING(INT_MAX), "0123456789");
	FT_ATOI_BASE_EXPECT(TO_STRING(INT_MIN), "0123456789");
}

void
ft_atoi_base_test(void)
{
	test_name = "ft_atoi_base.s";

	ft_atoi_base_segfault();
	if (!signaled)
		ft_atoi_base_compare();
}
