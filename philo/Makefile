NAME = 	philo
SRC  :=	$(wildcard ./mandatory/*.c)
SRC_B := $(wildcard ./bonus/*.c)

OBJS        = $(SRC:.c=.o)
OBJS_B      = $(SRC_B:.c=.o)
CC	        = gcc
CFLAGS      = -pthread -Wall -Werror -Wextra
RM	        = rm -f

BOLD = "\033[1m"
RED = "\033[31;1m"
GREEN = "\033[32;1m"
YELLOW = "\033[33;1m"
CYAN = "\033[36;1m"
BLUE = "\033[34;1m"
BLACK = "\033[30;1m"
MAGENTA = "\033[35;1m"
WHITE = "\033[37;1m"
RESET = "\033[0m"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo $(GREEN)All objects created!$(RESET)

bonus: $(OBJS_B)
	@$(CC) $(OBJS_B) -o $(NAME)
	@echo $(GREEN)All $(YELLOW)bonus$(RESET)$(GREEN) objects created!$(RESET)

clean:
	@$(RM) $(OBJS) $(OBJS_B)
	@echo $(RED)All objects cleaned!$(RESET)

fclean:
	@$(RM) $(OBJS) $(OBJS_B) $(NAME)
	@echo $(RED)All objects cleaned!$(RESET)
	@echo $(MAGENTA)$(NAME)$(RESET) $(RED)file cleaned!$(RESET)

re: fclean all