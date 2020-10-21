# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacharle <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 03:06:59 by cacharle          #+#    #+#              #
#    Updated: 2020/10/21 15:57:34 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBASM_PATH = ../pg

RM = rm -f
PYTHON = python3

CC = gcc
CCFLAGS = -I. -Wall -Wextra -Wno-nonnull
LDFLAGS = -L$(LIBASM_PATH) -lasm

NAME = runtest
SRC = main.c \
	  helper.c \
	  test/ft_strlen_test.c \
	  test/ft_strcpy_test.c \
	  test/ft_strcmp_test.c \
	  test/ft_write_test.c \
	  test/ft_read_test.c \
	  test/ft_strdup_test.c \

SRCBONUS = helper_list.c \
		   test/ft_atoi_base_test.c \
		   test/ft_list_size_test.c \
		   test/ft_list_push_front_test.c \
		   test/ft_list_sort_test.c \
		   test/ft_list_remove_if_test.c \
		   functions_reference/ref_ft_atoi_base.c \
		   functions_reference/ref_ft_list_size.c \
		   functions_reference/ref_ft_list_push_front.c \
		   functions_reference/ref_ft_list_sort.c \
		   functions_reference/ref_ft_list_remove_if.c

ifeq ($(LIBASM_TEST_BONUS),yes)
	SRC += $(SRCBONUS)
	CCFLAGS += -D LIBASM_TEST_BONUS
endif

# CCFLAGS += -fPIE -fPIC

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)
OBJBONUS += $(OBJ)

run: pretty
# runbonus: prettybonus

# prettybonus: allbonus pretty
pretty: all
	./$(NAME) 2> /dev/null | $(PYTHON) prettier.py

# run_rawbonus: allbonus run_raw
run_raw: all
	./$(NAME) 2> /dev/null

# run_debugbonus: allbonus run_debug
run_debug: all
	./$(NAME)

all: $(NAME)
# allbonus:
# allbonus: all

$(NAME): libasm_all $(OBJ)
	$(CC) -fPIE -fPIC -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: libasm_fclean libasm_all fclean all


libasm_all:
	make -C $(LIBASM_PATH) all

libasm_fclean:
	make -C $(LIBASM_PATH) fclean

.PHONY: run pretty run_raw run_debug all clean fclean re libasm_all libasm_fclean
