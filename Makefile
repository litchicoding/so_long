##### Executable program's name ###############################################
NAME = so_long

##### Define path and variables ###############################################
###############################################################################
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INCLUDE = ./include/

GET_NEXT_LINE_DIR = ./get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/get_next_line.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11

HEADER = -I$(INCLUDE) -I$(GET_NEXT_LINE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) 
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
FLAGS = $(CFLAGS) $(MLX_FLAGS)
# MAKE = make
GREEN = \033[0;32m
RESET = \033[0;m

##### Define source files and objects #########################################
###############################################################################
SRC_FILES = main.c ft_free_game.c ft_map_parsing.c ft_path_finding.c \
	ft_utils.c handle_input.c so_long.c
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

##### Rule by default #########################################################
###############################################################################
all: $(NAME)

##### Create objectc (.o) from source fils (.c )###############################
###############################################################################
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

##### Linking objects in executable ###########################################
###############################################################################
$(NAME): $(GET_NEXT_LINE) $(MLX) $(LIBFT) $(OBJ)
	@$(CC) $(HEADER) $(OBJ) $(GET_NEXT_LINE) $(LIBFT) $(FLAGS) -o $(NAME)
	@echo "$(GREEN)Compilation reussie [SO_LONG]$(RESET)"

##### Compile external libraries ##############################################
###############################################################################
$(GET_NEXT_LINE):
	@make -C $(GET_NEXT_LINE_DIR)
	@echo "$(GREEN)Compilation reussie [GET_NEXT_LINE]$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compilation reussie [LIBFT]"

$(MLX):
	@make -C $(MLX_DIR)
	@echo "$(GREEN)Compilation reussie [MLX]"
	
##### Clean objects + external lib ############################################
###############################################################################
clean:
	@$(RM) -fr $(OBJ_DIR)/
	@make -C $(GET_NEXT_LINE_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

##### Clean the executable + same for external lib ############################
###############################################################################
fclean: clean
	@$(RM) $(NAME)
	@make -C $(GET_NEXT_LINE_DIR) fclean
	@make -C $(LIBFT_DIR) fclean

ARG = map/map_valid.ber

exec: all
	./$(NAME) $(ARG)

valgrind: all
	valgrind --track-origins=yes --leak-check=full \
	./$(NAME) $(ARG)

norminette:
	@norminette src/*.c libft/*.c get_next_line/*.c include/*.h

###############################################################################
re: fclean all

.PHONY: all clean fclean re

###############################################################################
