#MINISHELL_PROJECT_MAKEFILE
include libft/.make
NAME				:=	minishell

CC					:=	cc
FLAGS				:=	-Wall -Wextra -Werror -g

###############################
#########START_SOURCES#########
###############################

#######AST_TREE_CREATION#######
AST_TREE_NAME		:=	create_tree.c add_nodes.c constructors.c constructors_2.c create_node.c \
						free_tree.c
AST_TREE_PATH		:=	ast/ast_create_tree/
AST_TREE			:=	$(addprefix $(AST_TREE_PATH), $(AST_TREE_NAME))

######AST_STRING_SPLITTER######
AST_SPLITTER_NAME	:=	create_node_data.c string_splitter_blocks_command.c string_splitter_blocks.c \
						string_splitter_utils_2.c string_splitter_utils.c string_splitter.c \
						check_if_inside_quotes.c
AST_SPLITTER_PATH	:=	ast/ast_string_splitter/
AST_SPLITTER		:=	$(addprefix $(AST_SPLITTER_PATH), $(AST_SPLITTER_NAME))

SRCS				:=	main.c $(AST_TREE) $(AST_SPLITTER)
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
	@mkdir -p $(OBJS_PATH)$(AST_TREE_PATH)
	@mkdir -p $(OBJS_PATH)$(AST_SPLITTER_PATH)

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
