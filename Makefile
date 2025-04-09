<<<<<<< HEAD

                          
                          
                          
                          
                          
                          
                          
                          
                          

=======
#SILENCE THE ENTERING/LEAVING DIRECTORY MESSAGE
MAKEFLAGS += --no-print-directory

#DEFINE COLOR AND STYLE CODES
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

#COMPILER AND FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror
R_FLAG = -lreadline

#SOURCE FILES
SRC =	./src/main.c 

#DIRECTORIES
OBJ_DIR = obj
LIBFT_DIR = libft

#DEFINE OBJECTS
OBJ = $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))
#OBJ += $(patsubst src/parser/%.c, $(OBJ_DIR)/%.o, $(SRC))

LIBFT_OBJ = $(LIBFT_DIR)/libft.a

#PROGRAM NAME
NAME = minishell

#DEFAULT TARGET
all: $(NAME)
	@echo "${BOLD}${GREEN}Minishell built ✅${RESET}"
	

#LINKING EXECUTABLE !!!FLAGS
$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT_OBJ)
	@${CC} ${CFLAGS} $(OBJ) $(GNL_OBJ) $(LIBFT_OBJ) $(PRINTF_OBJ) $(MINILIBIX_OBJ) $(MLX_FLAGS) -o $(NAME)
	@echo "${ITALIC}Building Minishell...🔨${RESET}"

#BUILD LIBRARIES
$(LIBFT_OBJ):
	@echo "\n███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗    "
	@echo "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║    "
	@echo "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     "
	@echo "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     "
	@echo "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@echo "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@echo "${ITALIC}Building Libft...🔨${RESET}"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "${BOLD}${GREEN}Libft built ✅${RESET}"

#CREATING OBJECT DIRECTORIES
$(OBJ_DIR):
	@mkdir -p $@

#COMPILING .c FILES INTO .o FILES (INSIDE OBJ DIR) !!!FLAGS
$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@${CC} ${CFLAGS} -c $< -o $@

#BASIC RULES
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
>>>>>>> 55873b64ec59f44c5f06e0910324a737f23da9b2
