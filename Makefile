#MINISHELL_PROJECT_MAKEFILE
include libft/.make
NAME				:=	minishell

CC					:=	cc
FLAGS				:=	-Wall -Wextra -Werror -g

###############################
#########START_SOURCES#########
###############################

#####BUILTINS#####
BUILTINS_NAME		:=	builtins.c cd.c echo.c env.c pwd.c unset.c
BUILTINS_UTILS_NAME	:=	errors_print.c utils.c utils_2.c
BUILTINS_EXPORT_NAME:=	export_add.c export_edit.c export_error.c export_utils.c export.c
BUILTINS_PATH		:=	builtins/
BUILTINS_UTILS_PATH	:=	builtins/utils/
BUILTINS_EXPORT_PATH:=	builtins/export/
BUILTINS			:=	$(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME)) \
	$(addprefix $(BUILTINS_UTILS_PATH), $(BUILTINS_UTILS_NAME)) \
	$(addprefix $(BUILTINS_EXPORT_PATH), $(BUILTINS_EXPORT_NAME))
SRCS				:=	main.c dollar_sign_expansion.c $(BUILTINS)
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
