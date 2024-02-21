#PIPEX_PROJECT_MAKEFILE
include libft/.make
NAME			:=	minishell

SRCS_NAME		:=
SRCS_PATH		:=	./srcs/
SRCS			:=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH		:=	./objs/
OBJS			:= $(addprefix $(OBJS_PATH), $(SRCS_NAME:.c=.o))

LIBFT_PATH		:=	$(LIBFT_PATH)
LIBFT			:=	$(addprefix $(LIBFT_PATH), $(LIBFT))
LIBFT_SOURSES	:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))

##################################################
#################__REMOVE IT!__###################
#################__REMOVE IT!__###################
##################################################
_DS			:= dshatilo
DS_NAME		:= create_tree.c create_node.c constructors.c constructors_2.c free_node_data.c
DS_PATH		:=	./srcs/ast/
DS			:=	$(addprefix $(SRCS_PATH), $(SRCS_NAME))

ODS_PATH		:=	./objs/
ODS			:= $(addprefix $(ODS_PATH), $(DS_NAME:.c=.o))

##################################################
#################__REMOVE IT!__###################
#################__REMOVE IT!__###################
##################################################


all: $(_DS)

# $(OBJS_PATH)%.o: $(SRCS_PATH)%.c | $(OBJS_PATH)
# 	@$(CC) $(FLAGS) -c $< -o $@

# $(NAME): $(OBJS) $(LIBFT)
# 	@echo "$(GREEN)\n--------------->$(NAME) created successfully!<---------------$(EC)"
# 	@cc $(FLAGS) $(OBJS) $(LIBFT) $ -o $(NAME)

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

##################################################
#################__REMOVE IT!__###################
#################__REMOVE IT!__###################
##################################################


$(ODS_PATH)%.o: $(DS_PATH)%.c | $(ODS_PATH)
	@$(CC) $(FLAGS) -c $< -o $@
$(_DS): $(ODS) $(LIBFT)
	@echo "$(GREEN)\n--------------->$(_DS) created successfully!<---------------$(EC)"
	@cc $(FLAGS) -lreadline $(ODS) $(LIBFT) $ -o $(_DS)


r:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@rm -rf $(ODS_PATH)
	@echo "$(GREEN)*.o files removed!$(EC)"

rr: clean
	@rm -rf $(_DS)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(GREEN)All files removed!$(EC)"
	
##################################################
#################__REMOVE IT!__###################
#################__REMOVE IT!__###################
##################################################