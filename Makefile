END				= \033[0m
YELLOW			= \033[33m
RED				= \033[31m
HIGH_RED		= \033[91m
GREEN			= \033[32m
BLUE			= \033[34m

NAME			= cub3D
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf
LIBFT_DIR		= libs/libft
MLX_LINUX_DIR	= libs/mlx_linux
MLX_DIR			= libs/mlx
INCLUDE			= includes/
SRC_DIR			= srcs
OBJ_DIR			= objs
LIBFT			= $(LIBFT_DIR)/libft.a
MLX				= $(MLX_DIR)/libmlx.a
MLX_LINUX		= $(MLX_LINUX_DIR)/libmlx_Linux.a
LIBS			= $(LIBFT)
SRCS			= $(wildcard $(SRC_DIR)/*.c)
OBJS			= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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
	LINKER_LINUX += -L$(MLX_LINUX_DIR) -lmlx_Linux -L/usr/lib -I$(MLX_LINUX_DIR) -lXext -lX11 -lm -lz
	LINUX_OBJ_FLAGS = -I/usr/include -I$(MLX_LINUX_DIR)
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
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN)[+] libft compiled$(END)"

$(MLX_LINUX):
	@chmod +x $(MLX_LINUX_DIR)/configure
	@make -s -C $(MLX_LINUX_DIR) 2> /dev/null 1> /dev/null
	@echo "$(GREEN)[+] mlx_linux compiled$(END)"

$(MLX):
	@make -s -C $(MLX_DIR) 2> /dev/null
	@echo "$(GREEN)[+] mlx compiled$(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INCLUDE) $(LINUX_OBJ_FLAGS) -c $< -o $@
	@echo "$(BLUE)[+] $@ compiled$(END)"



clean:
	@make -s -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)[+] libft cleaned$(END)"
	@make -s -C libs/$(MINILIBX) clean 1> /dev/null
	@echo "$(YELLOW)[+] $(MINILIBX) cleaned$(END)"
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)[+] $(NAME) cleaned$(END)"

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@echo "$(YELLOW)[+] libft fcleaned$(END)"
	@$(RM) $(NAME)
	@echo "$(YELLOW)[+] $(NAME) fcleaned$(END)"

re: fclean all



bonus: all

norm:
	clear
	@norminette $(LIBFT_DIR) $(INCLUDE) $(SRC_DIR)

test_invalid: all
	./$(NAME) maps/invalid_0.cub
	./$(NAME) maps/invalid_1.cub
	./$(NAME) maps/invalid_2.cub
	./$(NAME) maps/invalid_3.cub
	./$(NAME) maps/invalid_4.cub
	./$(NAME) maps/invalid_5.cub
	./$(NAME) maps/invalid_6.cub
	./$(NAME) maps/invalid_7.cub
	./$(NAME) maps/invalid_8.cub
	./$(NAME) maps/invalid_9.cub
	./$(NAME) maps/invalid_10.cub
	./$(NAME) maps/invalid_11.cub
	./$(NAME) maps/invalid_12.cub
	./$(NAME) maps/invalid_13.cub
	./$(NAME) maps/invalid_color_0.cub
	./$(NAME) maps/invalid_color_1.cub
	./$(NAME) maps/invalid_no_colors.cub
	./$(NAME) maps/invalid_no_map.cub
	./$(NAME) maps/invalid_no_texture.cub
	./$(NAME) maps/invalid_texture.cub

val_invalid: all
	valgrind --leak-check=full ./$(NAME) maps/invalid_0.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_1.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_2.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_3.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_4.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_5.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_6.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_7.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_8.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_9.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_10.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_11.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_12.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_13.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_color_0.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_color_1.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_no_colors.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_no_map.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_no_texture.cub
	valgrind --leak-check=full ./$(NAME) maps/invalid_texture.cub

leaks_invalid: all
	leaks --atExit -- ./$(NAME) maps/invalid_0.cub
	leaks --atExit -- ./$(NAME) maps/invalid_1.cub
	leaks --atExit -- ./$(NAME) maps/invalid_2.cub
	leaks --atExit -- ./$(NAME) maps/invalid_3.cub
	leaks --atExit -- ./$(NAME) maps/invalid_4.cub
	leaks --atExit -- ./$(NAME) maps/invalid_5.cub
	leaks --atExit -- ./$(NAME) maps/invalid_6.cub
	leaks --atExit -- ./$(NAME) maps/invalid_7.cub
	leaks --atExit -- ./$(NAME) maps/invalid_8.cub
	leaks --atExit -- ./$(NAME) maps/invalid_9.cub
	leaks --atExit -- ./$(NAME) maps/invalid_10.cub
	leaks --atExit -- ./$(NAME) maps/invalid_11.cub
	leaks --atExit -- ./$(NAME) maps/invalid_12.cub
	leaks --atExit -- ./$(NAME) maps/invalid_13.cub
	leaks --atExit -- ./$(NAME) maps/invalid_color_0.cub
	leaks --atExit -- ./$(NAME) maps/invalid_color_1.cub
	leaks --atExit -- ./$(NAME) maps/invalid_no_colors.cub
	leaks --atExit -- ./$(NAME) maps/invalid_no_map.cub
	leaks --atExit -- ./$(NAME) maps/invalid_no_texture.cub
	leaks --atExit -- ./$(NAME) maps/invalid_texture.cub

grep_leaks:
	make leaks_invalid | grep "total leaked bytes"


test: all
	clear
	@./$(NAME) maps/default.cub

run: test
rrun: fclean test

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

tar: clean_mac fclean
	@tar -cf ../$(NAME).tar .
	@echo "$(GREEN)[+] Made tar$(END)"

clean_mac:
	@find . -name "._*" -delete
	@find . -name ".DS_Store" -delete
	@echo "$(YELLOW)[+] Nasty MAC files cleaned$(END)"

clean_cache:
	@rm -rf ~/Library/Caches && rm -rf ~/Library/Application\ Support/Code/Cache && rm -rf ~/Library/Application\ Support/Code/User/workspaceStorage



.PHONY: all clean fclean re
