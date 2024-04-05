#MINISHELL_PROJECT_MAKEFILE
include libft/.make

NAME				:=	minishell

CC					:=	cc
FLAGS				:=	-Wall -Wextra -Werror -g

###############################
#########START_SOURCES#########
###############################

#########COMMON_UTILS##########
COMMON_UTILS_NAME	:=	remove_quotes.c errors_print.c split_before_wildcards.c prompt_update.c \
						pwd_init.c shlvl_init.c sort_string_array.c realloc_env.c ft_split_with_quotes.c
COMMON_UTILS_PATH	:=	common_utils/
COMMON_UTILS		:=	$(addprefix $(COMMON_UTILS_PATH), $(COMMON_UTILS_NAME))

#######AST_TREE_CREATION#######
AST_TREE_NAME		:=	create_tree.c add_nodes.c constructors.c constructors_2.c create_node.c \
						free_tree.c
AST_TREE_PATH		:=	ast/ast_create_tree/
AST_TREE			:=	$(addprefix $(AST_TREE_PATH), $(AST_TREE_NAME))

######AST_STRING_SPLITTER######
AST_SPLITTER_NAME	:=	create_node_info.c string_splitter_blocks_command.c string_splitter_blocks.c \
						string_splitter_utils_2.c string_splitter_utils.c string_splitter.c \
						check_if_inside_quotes.c
AST_SPLITTER_PATH	:=	ast/ast_string_splitter/
AST_SPLITTER		:=	$(addprefix $(AST_SPLITTER_PATH), $(AST_SPLITTER_NAME))

########VALIDATE_STRING########
VALIDATE_INPUT_NAME	:=	validate_input.c validate_word.c validate_redirect.c validate_simple_command.c \
						validate_command.c validate_pipeline.c is_blank_string.c validate_and_or.c 
VALIDATE_INPUT_PATH	:=	validate_input/
VALIDATE_INPUT		:=	$(addprefix $(VALIDATE_INPUT_PATH), $(VALIDATE_INPUT_NAME))

###########WILDCARDS###########
WILDCARDS_NAME		:=	wildcards.c wildcards_core.c wildcards_core_utils.c wildcards_entities_expand.c \
						wildcards_utils.c wildcards_sort.c wildcards_fill_array_with_entities.c \
						wildcards_asterisk_check.c
WILDCARDS_PATH		:=	wildcards/
WILDCARDS			:=	$(addprefix $(WILDCARDS_PATH), $(WILDCARDS_NAME))

#############D_SIGN############
D_SIGN_NAME			:=	dollar_sign_expansion_utils.c dollar_sign_expansion.c dollar_sign_expansion_q_mark.c \
						dollar_sign_expansion_generic.c 
D_SIGN_PATH			:=	dollar_sign_expansion/
D_SIGN				:=	$(addprefix $(D_SIGN_PATH), $(D_SIGN_NAME))

########EXECUTION########
TRAVERSE_NAME		:=	traverse_tree.c traverse_bracket.c traverse_pipe.c wait_children.c \
						traverse_command_br.c traverse_command.c parse_cmd.c is_builtin.c \
						locate_command.c find_executable.c run_builtin.c
REDIR_NAME			:=	apply_redirects.c check_redir.c apply_heredoc.c apply_redir_in.c apply_redir_out.c \
						apply_append.c
BUILTINS_NAME		:=	builtins.c cd_core.c cd_auxiliary.c echo.c env.c pwd.c unset.c exit.c utils.c
BUILTINS_EXPORT_NAME:=	export_add.c export_edit.c export_utils.c export.c export_other.c
BUILTINS_PATH		:=	execution/builtins/
BUILTINS_EXPORT_PATH:=	execution/builtins/export/
TRAVERSE_PATH		:=	execution/traverse_tree/
REDIR_PATH			:=	execution/redirects/
EXECUTION_PATH		:=	execution/
BUILTINS			:=	$(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME)) \
						$(addprefix $(BUILTINS_EXPORT_PATH), $(BUILTINS_EXPORT_NAME)) \
						$(addprefix $(TRAVERSE_PATH), $(TRAVERSE_NAME)) \
						$(addprefix $(REDIR_PATH), $(REDIR_NAME))
EXECUTION			:=	$(addprefix $(EXECUTION_PATH), $(EXECUTION_NAME))

SRCS				:=	main.c minishell.c $(VALIDATE_INPUT) $(AST_TREE) $(AST_TRAVERSE) $(AST_SPLITTER) \
						$(BUILTINS) $(EXECUTION) $(D_SIGN) $(WILDCARDS) $(COMMON_UTILS) $(REDIR)
SRCS_PATH			:=	srcs/

###############################
##########END_SOURCES##########
###############################

OBJS_PATH			:=	objs/
OBJS				:=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

LIBFT_PATH			:=	$(LIBFT_PATH)
LIBFT_SOURSES		:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))
LIBFT				:=	$(addprefix $(LIBFT_PATH), $(LIBFT))

# RL					:=	/opt/homebrew/opt/readline/lib/
# RLH					:=	/opt/homebrew/opt/readline/lib/
# RL_HEADER				:=	/opt/homebrew/opt/readline/include/readline/readline.h
# RLH_HEADER			:=	/opt/homebrew/opt/readline/include/readline/history.h

RL					:=	~/.brew/Cellar/readline/8.2.7/lib
RLH					:=	~/.brew/Cellar/readline/8.2.7/lib
RL_HEADER			:=	~/.brew/Cellar/readline/8.2.7/include/readline/readline.h
RLH_HEADER			:=	~/.brew/Cellar/readline/8.2.7/include/readline/history.h

HEADERS				:=	$(LIBFT_PATH)libft.h $(RL_HEADER) $(RLH_HEADER)
INCLUDES			:=	$(addprefix -I , $(HEADERS))
LIBS				:=	-lft -L $(LIBFT_PATH) -lreadline -L $(RL) -lhistory -L $(RL)

TOTAL_OBJS			:= $(words $(OBJS))
COMPILED_OBJS		:= 0
MSG_PRINTED 		:= false

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS) $(HEADERS)
	@cc $(FLAGS) $(INCLUDES) $(LIBS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)\n\n$(NAME) created successfully!$(EC)"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)$(AST_TREE_PATH)
	@mkdir -p $(OBJS_PATH)$(AST_SPLITTER_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_UTILS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_EXPORT_PATH)
	@mkdir -p $(OBJS_PATH)$(VALIDATE_INPUT_PATH)
	@mkdir -p $(OBJS_PATH)$(EXECUTION_PATH)
	@mkdir -p $(OBJS_PATH)$(D_SIGN_PATH)
	@mkdir -p $(OBJS_PATH)$(WILDCARDS_PATH)
	@mkdir -p $(OBJS_PATH)$(EXECUTION_UTILS_PATH)
	@mkdir -p $(OBJS_PATH)$(COMMON_UTILS_PATH)
	@mkdir -p $(OBJS_PATH)$(TRAVERSE_PATH)
	@mkdir -p $(OBJS_PATH)$(REDIR_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@
	@$(call progress,"minishell")

$(LIBFT): $(LIBFT_SOURSES)
	@$(MAKE) -C $(LIBFT_PATH)

clean:
	@$(MAKE) clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)*.o files removed!$(EC)"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(RED)\nFull clean up completed successfully!$(EC)"

re: fclean all

.PHONY: all clean fclean re