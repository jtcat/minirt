CC:= cc

LIBFLAGS:= -lm -lXext -lX11 -Ilibft

MFLAGS:= -O4 -fopt-info-optall-optimized -ftree-vectorize -mavx

#CFLAGS:= -O3 -Wall -Wextra -Werror $(LIBFLAGS)
CFLAGS:= $(MFLAGS) -Wall -Wextra -Werror $(LIBFLAGS)

NAME:= miniRT

SRC_DIR:= src/

SRC:= $(addprefix $(SRC_DIR), \
			main.c utils.c \
		$(addprefix datatypes/, \
			camera.c vec3.c vec3_2.c matrix.c argb.c) \
		$(addprefix gnl/, \
				gnl.c gnl_utils.c) \
		$(addprefix parser/, \
				parser.c parser2.c parser3.c) \
		$(addprefix intersect/, \
				primitives.c) \
		$(addprefix render/, \
				rt.c rt2.c))

OBJ_DIR:= obj/

OBJ:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC:.c=.o))

MLX_DIR:= minilibx-linux

MLX:= $(MLX_DIR)/libmlx.a

LFT_DIR:= libft

LFT:= $(LFT_DIR)/libft.a

all: $(NAME)

maps:
	cp -r ../minirt_bruno/scenes .

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)$*
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
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LFT_DIR) fclean

re: fclean all
