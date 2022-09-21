END			= \033[0m
YELLOW		= \033[33m
RED			= \033[31m
HIGH_RED	= \033[91m
GREEN		= \033[32m
BLUE		= \033[34m

NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
LIBFT		= libs/libft/libft.a
MLX			= libs/mlx/libmlx.a
MLX_LINUX	= libs/mlx_linux/libmlx_Linux.a
LIBS		= $(LIBFT)
INCLUDE		= includes/
SRC_DIR		= srcs
OBJ_DIR		= objs
SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin)
	LIBS += $(MLX)
	LINKER_MAC = -framework OpenGL -framework AppKit
	MINILIBX = mlx
else ifeq ($(detected_OS),Linux)
	LIBS += $(MLX_LINUX)
	LINKER_LINUX += -Llibs/mlx_linux -lmlx_Linux -L/usr/lib -Ilibs/mlx_linux -lXext -lX11 -lm -lz
	LINUX_OBJ_FLAGS = -I/usr/include -Ilibs/mlx_linux
	MINILIBX = mlx_linux
endif


all: $(NAME)

$(NAME): $(LIBS) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(LINKER_MAC) -I $(INCLUDE) $(OBJS) $(LIBS) $(LINKER_LINUX) -o $@
	@echo "$(GREEN)[+] $(NAME) compiled$(END)"



$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(BLUE)[+] $@ folder created$(END)"

$(LIBFT):
	@make -s -C libs/libft
	@echo "$(GREEN)[+] libft compiled$(END)"

$(MLX_LINUX):
	@make -s -C libs/mlx_linux 2> /dev/null 1> /dev/null
	@echo "$(GREEN)[+] mlx_linux compiled$(END)"

$(MLX):
	@make -s -C libs/mlx 2> /dev/null
	@echo "$(GREEN)[+] mlx compiled$(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(LINUX_OBJ_FLAGS) -c $< -o $@
	@echo "$(BLUE)[+] $@ compiled$(END)"



clean:
	@make -s -C libs/libft clean
	@echo "$(YELLOW)[+] libft cleaned$(END)"
	@make -s -C libs/$(MINILIBX) clean 1> /dev/null
	@echo "$(YELLOW)[+] $(MINILIBX) cleaned$(END)"
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)[+] $(NAME) cleaned$(END)"

fclean: clean
	@make -s -C libs/libft fclean
	@echo "$(YELLOW)[+] libft fcleaned$(END)"
	@$(RM) $(NAME)
	@echo "$(YELLOW)[+] $(NAME) fcleaned$(END)"

re: fclean all




test_invalid: all
	./$(NAME) maps/invalid_0.cub
	./$(NAME) maps/invalid_1.cub
	./$(NAME) maps/invalid_2.cub
	./$(NAME) maps/invalid_3.cub
	./$(NAME) maps/invalid_4.cub
	./$(NAME) maps/invalid_5.cub
	./$(NAME) maps/invalid_6.cub
	./$(NAME) maps/invalid_7.cub

val_invalid: all
	valgrind --leak-check=full ./$(NAME) maps/invalid_0.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_1.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_2.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_3.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_4.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_5.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_6.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_7.cub

leaks_invalid: all
	leaks --atExit -- ./$(NAME) maps/invalid_0.cub
	leaks --atExit -- ./$(NAME) maps/invalid_1.cub
	leaks --atExit -- ./$(NAME) maps/invalid_2.cub
	leaks --atExit -- ./$(NAME) maps/invalid_3.cub
	leaks --atExit -- ./$(NAME) maps/invalid_4.cub
	leaks --atExit -- ./$(NAME) maps/invalid_5.cub
	leaks --atExit -- ./$(NAME) maps/invalid_6.cub
	leaks --atExit -- ./$(NAME) maps/invalid_7.cub

test: all
	clear
	@./$(NAME) maps/default.cub

run: test

var: all
	clear
	@valgrind --leak-check=full ./$(NAME) maps/default.cub
val: var

leaks: all
	clear
	@leaks --atExit -- ./$(NAME) maps/default.cub

copy:
	@$(RM) ../$(NAME)_backup
	@mkdir -p ../$(NAME)_backup
	@cp -r * ../$(NAME)_backup
	@echo "$(GREEN)[+] Copied project$(END)"
backup: copy
up: copy

tar: fclean
	@tar -cf ../$(NAME).tar .
	@echo "$(GREEN)[+] Made tar$(END)"




.PHONY: all clean fclean re
