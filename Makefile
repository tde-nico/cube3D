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
LIBFT		= libft/libft.a
MLX			= mlx/libmlx.a
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
	LINKER = -framework OpenGL -framework AppKit
endif


all: $(NAME)

$(NAME): $(LIBS) $(OBJ_DIR) $(OBJS)
	@echo -n "$(BLUE)"
	$(CC) $(CFLAGS) $(LINKER) -I $(INCLUDE) $(OBJS) $(LIBS) -o $@
	@echo -n "$(END)"
	@echo "$(GREEN)[+] $(NAME) compiled$(END)"



$(OBJ_DIR):
	@echo -n "$(BLUE)"
	mkdir -p $@
	@echo -n "$(END)"

$(LIBFT):
	@make -s -C libft
	@echo "$(GREEN)[+] libft compiled$(END)"

$(MLX):
	@make -s -C mlx 2> /dev/null
	@echo "$(GREEN)[+] mlx compiled$(END)"

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@echo -n "$(BLUE)"
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< -o $@
	@echo -n "$(END)"



clean:
	@make -s -C libft clean
	@echo "$(YELLOW)[+] libft cleaned$(END)"
	@make -s -C mlx clean
	@echo "$(YELLOW)[+] mlx cleaned$(END)"
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)[+] $(NAME) cleaned$(END)"

fclean: clean
	@make -s -C libft fclean
	@echo "$(YELLOW)[+] libft fcleaned$(END)"
	@$(RM) $(NAME)
	@echo "$(YELLOW)[+] $(NAME) fcleaned$(END)"

re: fclean all




test: all
	@./$(NAME) maps/default.cub

run: test

var: all
	@valgrind --leak-check=full ./$(NAME) maps/default.cub
val: var

leaks: all
	@leaks --atExit -- ./$(NAME)

up:
	@$(RM) ../$(NAME)_backup
	@mkdir -p ../$(NAME)_backup
	@cp -r * ../$(NAME)_backup
	@echo "[+] Backed up"
backup: up

tar:
	@tar -cf ../$(NAME).tar .
	@echo "[+] Made tar"




.PHONY: all clean fclean re