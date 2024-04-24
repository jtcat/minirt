CC:= cc

INCDIRS:= -Ilibft -Iminilibx-linux

LIBFLAGS:= -lXext -lX11 -lm

MFLAGS:= -O4 -fopt-info-optall-optimized -ftree-vectorize -mavx

CFLAGS:= -O3 -Wall -Wextra -Werror
#CFLAGS:= -g -Wall -Wextra -Werror

NAME:= miniRT

SRC_DIR:= src/

SRC:= $(addprefix $(SRC_DIR), \
			main.c utils.c utils2.c\
		$(addprefix datatypes/, \
			camera.c light.c vec3.c vec3_2.c matrix.c matrix2.c argb.c argb2.c utils.c) \
		$(addprefix gnl/, \
				gnl.c gnl_utils.c) \
		$(addprefix parser/, \
				parser.c parser2.c parser3.c parser4.c) \
		$(addprefix intersect/, \
				prim_cylinder.c prim_sphere.c prim_plane.c prim_construct.c) \
		$(addprefix render/, \
				render.c rt.c rt_utils.c) \
		$(addprefix interface/, \
				if.c))

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
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

$(NAME): $(MLX) $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJ) $(MLX) $(LFT) $(INCDIRS) -o $@ 

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

minilibx:
	git clone git@github.com:42Paris/minilibx-linux.git
	make -C minilibx-linux
	
