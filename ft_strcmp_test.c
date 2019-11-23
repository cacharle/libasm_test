#include "libasm_test.h"

static void
ft_strcmp_test_segfault(void)
{
	TEST_ASM_FUNCTION(ft_strcmp("", ""));
	TEST_ASM_FUNCTION(ft_strcmp("bon", "bon"));
	TEST_ASM_FUNCTION(ft_strcmp("bonjour", "bonjour"));
	TEST_ASM_FUNCTION(ft_strcmp("%c%s%p%x%X%e%f%g", "%c%s%p%x%X%e%f%g"));
	TEST_ASM_FUNCTION(ft_strcmp("the\0hidden", "the\0hidden"));
	TEST_ASM_FUNCTION(ft_strcmp("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.",
"Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet."));
}

#define FT_STRCMP_EXPECT(s1, s2) expect_int(strcmp(s1, s2), ft_strcmp(s1, s2))

static void
ft_strcmp_test_compare(void)
{
	FT_STRCMP_EXPECT("", "");
	FT_STRCMP_EXPECT("bon", "");
	FT_STRCMP_EXPECT("bonjour", "");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "");
	FT_STRCMP_EXPECT("the\0hidden", "");
	FT_STRCMP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.", "");
	FT_STRCMP_EXPECT("", "");
	FT_STRCMP_EXPECT("bon", "bon");
	FT_STRCMP_EXPECT("bonjour", "bonjour");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "%c%s%p%x%X%e%f%g");
	FT_STRCMP_EXPECT("the\0hidden", "the\0hidden");
	FT_STRCMP_EXPECT("Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.",
"Lorem ipsum dolor sit amet, consectetur adipiscing\
elit. Sed in malesuada purus. Etiam a scelerisque massa. Ut non euismod elit. Aliquam\
bibendum dolor mi, id fringilla tellus pulvinar eu. Fusce vel fermentum sem. Cras\
volutpat, eros eget rhoncus rhoncus, diam augue egestas dolor, vitae rutrum nisi\
felis sed purus. Mauris magna ex, mollis non suscipit eu, lacinia ac turpis. Phasellus\
ac tortor et lectus fermentum lobortis eu at mauris. Vestibulum sit amet posuere\
tortor, sit amet consequat amet.");

	FT_STRCMP_EXPECT("", "asdf");
	FT_STRCMP_EXPECT("bon", "bo");
	FT_STRCMP_EXPECT("bonjour", "onjour");
	FT_STRCMP_EXPECT("%c%s%p%x%X%e%f%g", "%s%p%x%X%e%f%g");
	FT_STRCMP_EXPECT("the\0hidden", "thehidden");
	FT_STRCMP_EXPECT("Lorem ipsum dolor st amet, consectetur adipiscing", "Lodsfsdfasdf");
}

void
ft_strcmp_test(void)
{
	test_name = "ft_strcmp.s";

	ft_strcmp_test_segfault();
	if (!signaled)
		ft_strcmp_test_compare();
}
