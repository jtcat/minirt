CC:= cc

CFLAGS:= -Wall -Wextra -Werror

NAME:= miniRT

NAME_BONUS:= miniRT_bonus

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(OBJ_COMMON) -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS):
	$(CC) $(CFLAGS) $(OBJ_COMMON) $(OBJ_BONUS) -o $@
