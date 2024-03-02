NAME = 	philo
SRC  :=	$(wildcard ./mandatory/*.c)
SRC_B := $(wildcard ./bonus/*.c)

OBJS        = $(SRC:.c=.o)
OBJS_B      = $(SRC_B:.c=.o)
CC	        = gcc
CFLAGS      = -pthread -Wall -Werror -Wextra
RM	        = rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

bonus: $(OBJS_B)
	$(CC) $(OBJS_B) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_B) && printf "All objects cleaned! :)\n"

fclean:
	@$(RM) $(OBJS) $(OBJS_B) $(NAME) && printf "$(NAME) file cleaned! :)\n"

re: fclean all