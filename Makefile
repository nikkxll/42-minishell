#PIPEX_PROJECT_MAKEFILE
include libft/.make
NAME			:=	minishell

SRCS_NAME		:=	main.c constructors.c
SRCS_PATH		:=	./srcs/
SRCS			:=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH		:=	./objs/
OBJS			:= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

LIBFT_PATH		:=	$(LIBFT_PATH)
LIBFT			:=	$(addprefix $(LIBFT_PATH), $(LIBFT))
LIBFT_SOURSES	:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))

all: $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(OBJS_PATH)
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)\n--------------->$(NAME) created successfully!<---------------$(EC)"
	@cc $(FLAGS) $(OBJS) $(LIBFT) $ -o $(NAME)

# $(NAME): .mandatory
# 	@echo "$(GREEN)\n--------------->$(NAME) created successfully!<---------------$(EC)"

# .mandatory: $(OBJS) $(LIBFT)
# 	@cc $(FLAGS) $(OBJS) $(LIBFT) $ -o $(NAME)
# 	@touch .mandatory
# 	@rm -rf .bonus

$(LIBFT): $(LIBFT_SOURSES)
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo "$(GREEN)*.o files removed!$(EC)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(GREEN)All files removed!$(EC)"

re: fclean all