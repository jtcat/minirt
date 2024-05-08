CC:= cc

INCDIRS:= -Ilibft -Iminilibx-linux

LIBFLAGS:= -lXext -lX11 -lm

MFLAGS:= -O4 -fopt-info-optall-optimized -ftree-vectorize -mavx

CFLAGS:= -O3 -Wall -Wextra -Werror
#CFLAGS:= -g -Wall -Wextra -Werror

NAME:= miniRT

NAME_BONUS:= miniRT_bonus

SRC_DIR:= src/

SRC_DIR_BONUS:= src_bonus/

SRC:= $(addprefix $(SRC_DIR), \
			main.c utils.c utils2.c\
		$(addprefix datatypes/, \
			camera.c light.c vec3.c vec3_2.c matrix.c matrix2.c matrix3.c argb.c argb2.c utils.c) \
		$(addprefix gnl/, \
				gnl.c gnl_utils.c) \
		$(addprefix parser/, \
				parser.c parser2.c parser3.c parser4.c) \
		$(addprefix intersect/, \
				prim_cylinder.c prim_sphere.c prim_plane.c prim_construct.c) \
		$(addprefix render/, \
				render.c rt.c rt_utils.c) \
		$(addprefix interface/, \
				if.c if2.c if3.c))

SRC_BONUS:= $(addprefix $(SRC_DIR_BONUS), \
			main_bonus.c utils_bonus.c utils2_bonus.c\
		$(addprefix datatypes/, \
			camera_bonus.c light_bonus.c vec3_bonus.c vec3_2_bonus.c matrix_bonus.c matrix2_bonus.c matrix3_bonus.c argb_bonus.c argb2_bonus.c utils_bonus.c) \
		$(addprefix gnl/, \
				gnl_bonus.c gnl_utils_bonus.c) \
		$(addprefix parser/, \
				parser_bonus.c parser2_bonus.c parser3_bonus.c parser4_bonus.c) \
		$(addprefix intersect/, \
				prim_cylinder_bonus.c prim_sphere_bonus.c prim_plane_bonus.c prim_construct_bonus.c) \
		$(addprefix render/, \
				render_bonus.c rt_bonus.c rt_utils_bonus.c) \
		$(addprefix interface/, \
				if_bonus.c if2_bonus.c if3_bonus.c))

OBJ_DIR:= obj/
OBJ_DIR_BONUS:= obj_bonus/

OBJ:= $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SRC:.c=.o))
OBJ_BONUS:= $(patsubst $(SRC_DIR_BONUS)%,$(OBJ_DIR_BONUS)%,$(SRC_BONUS:.c=.o))

MLX_DIR:= minilibx-linux

MLX:= $(MLX_DIR)/libmlx.a

LFT_DIR:= libft

LFT:= $(LFT_DIR)/libft.a

all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)$*
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	mkdir -p $(OBJ_DIR_BONUS)$*
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

$(NAME): $(MLX) $(LFT) $(OBJ)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJ) $(MLX) $(LFT) $(INCDIRS) -o $@ 

$(NAME_BONUS): $(MLX) $(LFT) $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJ_BONUS) $(MLX) $(LFT) $(INCDIRS) -o $@ 

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(LFT):
	$(MAKE) -C $(LFT_DIR) bonus

clean:
	$(RM) -f $(OBJ)
	$(RM) -f $(OBJ_BONUS)
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(OBJ_DIR_BONUS)
	$(MAKE) -C $(MLX_DIR) clean || true
	$(MAKE) -C $(LFT_DIR) clean

fclean: clean
	$(RM) -f $(NAME)
	$(RM) -f $(NAME_BONUS)
	$(MAKE) -C $(LFT_DIR) fclean

re: fclean all

minilibx:
	git clone git@github.com:42Paris/minilibx-linux.git minilibx-linux
	make -C minilibx-linux

.PHONY: all bonus clean fclean
