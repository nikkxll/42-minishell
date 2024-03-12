#MINISHELL_PROJECT_MAKEFILE
include libft/.make
NAME				:=	minishell

CC					:=	cc
FLAGS				:=	-Wall -Wextra -Werror -g

###############################
#########START_SOURCES#########
###############################


###########BUILTINS############
BUILTINS_NAME		:=	builtins.c cd.c echo.c env.c pwd.c unset.c
BUILTINS_UTILS_NAME	:=	errors_print.c utils.c utils_2.c
BUILTINS_EXPORT_NAME:=	export_add.c export_edit.c export_error.c export_utils.c export.c
BUILTINS_PATH		:=	builtins/
BUILTINS_UTILS_PATH	:=	builtins/utils/
BUILTINS_EXPORT_PATH:=	builtins/export/
BUILTINS			:=	$(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME)) \
	$(addprefix $(BUILTINS_UTILS_PATH), $(BUILTINS_UTILS_NAME)) \
	$(addprefix $(BUILTINS_EXPORT_PATH), $(BUILTINS_EXPORT_NAME))

########VALIDATE_STRING########
VALIDATE_INPUT_NAME	:=	validate_input.c validate_word.c validate_redirect.c validate_simple_command.c \
						validate_command.c validate_pipeline.c is_blank_string.c validate_and_or.c \
						print_syntax_error.c 
						
VALIDATE_INPUT_PATH	:=	/validate_input/
VALIDATE_INPUT		:=	$(addprefix $(VALIDATE_INPUT_PATH), $(VALIDATE_INPUT_NAME))

SRCS				:=	main.c $(VALIDATE_INPUT) $(BUILTINS) dollar_sign_expansion.c
SRCS_PATH			:=	srcs/

###############################
##########END_SOURCES##########
###############################

OBJS_PATH			:=	objs/
OBJS				:=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

LIBFT_PATH			:=	$(LIBFT_PATH)
LIBFT_SOURSES		:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))
LIBFT				:=	$(addprefix $(LIBFT_PATH), $(LIBFT))

all: $(NAME)

$(NAME): $(OBJS_PATH) $(OBJS) $(LIBFT) 
	@cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)\n--------------->$(NAME) created successfully!<---------------$(EC)"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_UTILS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_EXPORT_PATH)
	@mkdir -p $(OBJS_PATH)$(VALIDATE_INPUT_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT): $(LIBFT_SOURSES)
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo "$(GREEN)*.o files removed!$(EC)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(GREEN)All files removed!$(EC)"

re: fclean all