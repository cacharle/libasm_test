RM = rm -f
UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
	PYTHON = python3.7
else
	PYTHON = python3
endif

LIBASM_PATH = ../libasm

CC = gcc -fPIC -no-pie
CCFLAGS = -I. -Wall -Wextra
LDFLAGS = -L$(LIBASM_PATH) -lasm

NAME = runtest
SRC = main.c \
	  helper.c \
	  ft_strlen_test.c \
	  ft_strcpy_test.c \
	  ft_strcmp_test.c \
	  ft_write_test.c \
	  ft_read_test.c \
	  ft_strdup_test.c \
	  ft_atoi_base_test.c \
	  functions_reference/ref_ft_atoi_base.c
	  #ft_list_push_front_test.c ft_list_size_test.c \
	  # ft_list_sort_test.c ft_list_remove_if_test.c \

OBJ = $(SRC:.c=.o)

run: pretty

pretty: all
	./$(NAME) | $(PYTHON) prettier.py

run_raw: all
	./$(NAME)

all: $(NAME)

$(NAME): libasm_all $(OBJ)
	$(CC)  -o $@ $(OBJ) $(LDFLAGS)

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
