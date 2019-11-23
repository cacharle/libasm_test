RM = rm -f

LIBASM_PATH = ../libasm

CC = gcc
CCFLAGS = -Wall -Wextra
LDFLAGS = -L$(LIBASM_PATH) -lasm

NAME = runtest
SRC = main.c ft_strlen_test.c ft_strcpy_test.c ft_strcmp_test.c \
	  ft_write_test.c ft_read_test.c ft_strdup_test.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

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
