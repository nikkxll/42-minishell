# MINISHELL_PROJECT_MAKEFILE
include libft/.make

NAME				:=	minishell

CC					:=	cc
FLAGS				:=	-g -Wall -Wextra -Werror

# MINISHELL
MINISHELL_NAME		:=	main.c ft_free_minishell.c initialize_minishell.c \
						run_minishell.c 
MINISHELL_PATH		:=	minishell/
MINISHELL			:=	$(addprefix $(MINISHELL_PATH), $(MINISHELL_NAME))

# UTILS
UTILS_NAME			:=	remove_quotes.c errors_print.c split_before_wildcards.c \
						prompt_update.c pwd_init.c shlvl_init.c sort_string_array.c \
						realloc_env.c ft_split_with_quotes.c init_history.c add_e_bash_history.c \
						save_history_to_file.c handle_ctrl_d.c
UTILS_PATH			:=	utils/
UTILS				:=	$(addprefix $(UTILS_PATH), $(UTILS_NAME))

# AST_PARSER
AST_PARSER_NAME		:=	create_tree.c add_nodes.c constructors.c constructors_2.c \
						create_node.c free_tree.c
AST_PARSER_PATH		:=	ast_parser/
AST_PARSER			:=	$(addprefix $(AST_PARSER_PATH), $(AST_PARSER_NAME))

# LEXER
LEXER_NAME			:=	lexer_cmd_blocks.c lexer_common_utils.c lexer_quotes_check.c \
						lexer_searchers.c lexer_tokenization_utils.c lexer_tokenization.c \
						lexer_tokens_blocks.c lexer.c
LEXER_PATH			:=	lexer/
LEXER				:=	$(addprefix $(LEXER_PATH), $(LEXER_NAME))

# VALIDATE_STRING
VALIDATOR_NAME		:=	validate_input.c validate_word.c validate_redirect.c \
						validate_simple_command.c validate_command.c validate_pipeline.c \
						is_blank_string.c validate_and_or.c 
VALIDATOR_PATH		:=	bnf_syntax_validator/
VALIDATOR			:=	$(addprefix $(VALIDATOR_PATH), $(VALIDATOR_NAME))

# WILDCARDS
WILDCARDS_NAME		:=	wildcards.c wildcards_core.c wildcards_core_utils.c \
						wildcards_entities_expand.c wildcards_utils.c wildcards_sort.c \
						wildcards_fill_array_with_entities.c wildcards_asterisk_check.c
WILDCARDS_PATH		:=	wildcards/
WILDCARDS			:=	$(addprefix $(WILDCARDS_PATH), $(WILDCARDS_NAME))

# D_SIGN
D_SIGN_NAME			:=	dollar_sign_expansion_utils.c dollar_sign_expansion.c \
						dollar_sign_expansion_q_mark.c dollar_sign_expansion_generic.c 
D_SIGN_PATH			:=	dollar_sign_expansion/
D_SIGN				:=	$(addprefix $(D_SIGN_PATH), $(D_SIGN_NAME))

# BUILTINS
BUILTINS_NAME		:=	builtins.c echo.c env.c pwd.c unset.c exit.c utils.c
BUILTINS_EXPORT_NAME:=	export_add.c export_edit.c export_utils.c export.c export_other.c
BUILTINS_CD_NAME	:=	cd_core.c cd_auxiliary.c
BUILTINS_PATH		:=	builtins/
BUILTINS_EXPORT_PATH:=	builtins/export/
BUILTINS_CD_PATH	:=	builtins/cd/
BUILTINS			:=	$(addprefix $(BUILTINS_PATH), $(BUILTINS_NAME)) \
						$(addprefix $(BUILTINS_EXPORT_PATH), $(BUILTINS_EXPORT_NAME)) \
						$(addprefix $(BUILTINS_CD_PATH), $(BUILTINS_CD_NAME))

# REDIRECTS
REDIR_NAME			:=	apply_redirects.c check_redir.c apply_heredoc.c apply_redir_in.c \
						apply_redir_out.c apply_append.c prepare_redirects.c prepare_heredocs.c 
REDIR_PATH			:=	redirects/
REDIR				:=	$(addprefix $(REDIR_PATH), $(REDIR_NAME))

# TRAVERSE
TRAVERSE_NAME		:=	traverse_tree.c traverse_bracket.c traverse_pipe.c wait_children.c \
						traverse_command_br.c traverse_command.c parse_cmd.c is_builtin.c \
						locate_command.c find_executable.c run_builtin.c
TRAVERSE_PATH		:=	traverse_tree/
TRAVERSE			:=	$(addprefix $(TRAVERSE_PATH), $(TRAVERSE_NAME))

# SIGNALS
SIGNALS_NAME		:=	interceptor.c toggler.c
SIGNALS_PATH		:=	signals/
SIGNALS				:=	$(addprefix $(SIGNALS_PATH), $(SIGNALS_NAME))

# SOURCE_FILES
SRCS				:=	$(MINISHELL) $(UTILS) $(AST_PARSER) $(LEXER) $(VALIDATOR) \
						$(WILDCARDS) $(D_SIGN) $(BUILTINS) $(REDIR) $(TRAVERSE) $(SIGNALS)
SRCS_PATH			:=	srcs/

# OBJECT_FILES
OBJS_PATH			:=	objs/
OBJS				:=	$(addprefix $(OBJS_PATH), $(SRCS:.c=.o))

# LIBFT_LIBRARY
LIBFT_PATH			:=	$(LIBFT_PATH)
LIBFT_SOURSES		:=	$(addprefix $(LIBFT_PATH), $(LIBFT_SOURSES))
LIBFT				:=	$(addprefix $(LIBFT_PATH), $(LIBFT))

# READLINE
# RL					:=	/opt/homebrew/opt/readline/lib/
# RLH					:=	/opt/homebrew/opt/readline/lib/
# RL_HEADER			:=	/opt/homebrew/opt/readline/include/readline/readline.h
# RLH_HEADER			:=	/opt/homebrew/opt/readline/include/readline/history.h

RL					:=	~/.brew/Cellar/readline/8.2.7/lib
RLH					:=	~/.brew/Cellar/readline/8.2.7/lib
RL_HEADER			:=	~/.brew/Cellar/readline/8.2.7/include/readline/readline.h
RLH_HEADER			:=	~/.brew/Cellar/readline/8.2.7/include/readline/history.h

# HEADERS AND EXTERNAL LIBRARIES
HEADERS				:=	$(LIBFT_PATH)libft.h $(RL_HEADER) $(RLH_HEADER)
INCLUDES			:=	$(addprefix -I , $(HEADERS))
LIBS				:=	-lft -L $(LIBFT_PATH) -lreadline -L $(RL) -lhistory -L $(RL)

# LOADING PROGRESS BAR INIT
TOTAL_OBJS			:= $(words $(OBJS))
COMPILED_OBJS		:= 0
MSG_PRINTED 		:= false

# RULES
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS_PATH) $(OBJS) $(HEADERS)
	@cc $(FLAGS) $(INCLUDES) $(LIBS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)\n\n$(NAME) created successfully!$(EC)"

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)
	@mkdir -p $(OBJS_PATH)$(MINISHELL_PATH)
	@mkdir -p $(OBJS_PATH)$(UTILS_PATH)
	@mkdir -p $(OBJS_PATH)$(AST_PARSER_PATH)
	@mkdir -p $(OBJS_PATH)$(LEXER_PATH)
	@mkdir -p $(OBJS_PATH)$(VALIDATOR_PATH)
	@mkdir -p $(OBJS_PATH)$(WILDCARDS_PATH)
	@mkdir -p $(OBJS_PATH)$(VALIDATOR_PATH)
	@mkdir -p $(OBJS_PATH)$(D_SIGN_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_EXPORT_PATH)
	@mkdir -p $(OBJS_PATH)$(BUILTINS_CD_PATH)
	@mkdir -p $(OBJS_PATH)$(REDIR_PATH)
	@mkdir -p $(OBJS_PATH)$(TRAVERSE_PATH)
	@mkdir -p $(OBJS_PATH)$(SIGNALS_PATH)

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
	@rm -rf .e-bash_history
	@echo "$(RED)\nFull clean up completed successfully!$(EC)"

re: fclean all

.PHONY: all clean fclean re