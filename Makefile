CC:= cc

LIBFLAGS:= -lm -lXext -lX11

CFLAGS:= -g -Wall -Wextra -Werror $(LIBFLAGS)

NAME:= miniRT

SRC:= $(addprefix src/, main.c vec3.c vec3_2.c parser.c parser2.c camera.c \
						parser3.c rt.c rt2.c utils.c argb.c matrix.c primitives.c) \
	$(addprefix gnl/, gnl.c gnl_utils.c)

OBJ:= $(SRC:.c=.o)

MLX_DIR:= minilibx-linux

MLX:= $(MLX_DIR)/libmlx.a

LFT_DIR:= libft

LFT:= $(LFT_DIR)/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MLX) $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LFT) -o $@

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LFT):
	$(MAKE) -C $(LFT_DIR) bonus

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LFT_DIR) fclean

re: fclean all
