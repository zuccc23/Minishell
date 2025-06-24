# DEFINE COLOR AND STYLE CODES
RESET = \033[0m
BOLD = \033[1m
ITALIC = \033[3m
UNDERLINE = \033[4m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

# SILENCE THE ENTERING/LEAVING DIRECTORY MESSAGE
MAKEFLAGS += --no-print-directory

# COMPILER AND FLAGS
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
R_FLAG = -lreadline

# SOURCE
SRC = ./src/main.c ./src/signals/signals.c \
	./src/lexer/lexer.c ./src/lexer/token.c ./src/lexer/token_utils.c \
	./src/lexer/preprocess.c ./src/utils/lexer_utils.c \
	./src/lexer/preprocess_utils.c ./src/utils/list_utils.c \
	./src/lexer/syntax_checks.c ./src/lexer/clean_input_utils.c ./src/lexer/clean_input.c\
	./src/lexer/clean_input_v2.c ./src/lexer/clean_input_utils_v2.c \
	./src/parser/parser.c ./src/parser/command.c \
	./src/parser/parser_utils.c \
	./src/parser/analyse_token.c \
	./src/parser/redirections.c ./src/utils/clean.c \
	./src/parser/expand.c ./src/parser/command_utils.c \
	./src/parser/init_parsing.c ./src/executor/executor.c \
	./src/executor/executor_utils.c \
	./src/utils/exec_utils.c ./src/executor/redirections.c \
	./src/executor/heredoc.c ./src/executor/heredoc_utils.c \
	./src/env/env_init.c ./src/parser/expand_utils.c ./src/parser/expand_utils2.c \
	./src/executor/path.c ./src/executor/path_utils.c ./src/executor/valid_redir.c \
	./src/builtins/builtins_utils.c \
	./src/builtins/cd.c ./src/builtins/pwd.c ./src/builtins/echo.c ./src/builtins/exit.c \
	./src/builtins/env.c ./src/builtins/unset.c ./src/builtins/export.c ./src/builtins/export_utils.c \
	./src/builtins/builtins.c ./src/utils/errors.c

# DIRECTORIES
OBJ_DIR = obj
LIBFT_DIR = libft

# DEFINE OBJECTS
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))
LIBFT_OBJ = $(LIBFT_DIR)/libft.a

# PROGRAM NAME
NAME = minishell

# DEFAULT TARGET
all: $(NAME)
	@echo "${BOLD}${GREEN}Minishell built ✅${RESET}"

# LINKING EXECUTABLE !!!FLAGS
$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT_OBJ)
	@echo "${ITALIC}Building Minishell...🔨${RESET}"
	@${CC} ${CFLAGS} $(OBJ) $(LIBFT_OBJ) ${R_FLAG} -o $(NAME)

# BUILD LIBRARIES
$(LIBFT_OBJ):
	@echo "\n███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "${ITALIC}Building Libft...🔨${RESET}"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "${BOLD}${GREEN}Libft built ✅${RESET}"

# CREATING OBJECT DIRECTORIES
$(OBJ_DIR):
	@mkdir -p $@

# COMPILING .c FILES INTO .o FILES (INSIDE OBJ DIR) !!!FLAGS
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@${CC} ${CFLAGS} ${R_FLAG} -c $< -o $@

# BASIC RULES
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "${ITALIC}Cleaning object files...🍃${RESET}"
	@echo "${GREEN}${BOLD}Done !${RESET}"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "${ITALIC}Cleaning everything...🍃${RESET}"
	@echo "${GREEN}${BOLD}Done !${RESET}"

re: fclean all

.PHONY: all clean fclean re
