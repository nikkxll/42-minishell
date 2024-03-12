#LIBFT_PRJ
LFT_PATH		:=	libft/
LFT_SRCS		:=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
					ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memcpy.c ft_memmove.c \
					ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
					ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
					ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c  ft_putendl_fd.c \
					ft_putnbr_fd.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c 

#PRINTF_PRJ
PRINTF_PATH		:=	printf/
PRINTF_SRCS		:=	ft_printf.c ft_switch.c ft_print_char.c ft_putchar.c ft_print_str.c ft_putstr.c \
					ft_print_hex.c ft_numlenbase.c ft_dec_tobase.c ft_print_dec.c 

#GET_NEXT_LINE_PRJ
GNL_PATH		:=	get_next_line/
GNL_SRCS		:=	get_next_line.c get_next_line_utils.c
GNL_HEADERS		:=	get_next_line.h

#AUXILIARY_FUNCTIONS
AUX_PATH		:=	auxiliary/

AUX_SRCS		:=	ft_abs.c ft_do_nothing.c ft_free_2d_array.c ft_max.c ft_min.c ft_arrlen.c

#MAIN_LIBFT
LIBFT			:=	libft.a
LIBFT_PATH		:=	libft/
LIBFT_SOURSES	:=	$(addprefix $(LFT_PATH), $(LFT_SRCS)) $(addprefix $(PRINTF_PATH), $(PRINTF_SRCS)) \
					$(addprefix $(GNL_PATH), $(GNL_SRCS)) $(addprefix $(GNL_PATH), $(GNL_HEADERS)) \
					$(addprefix $(AUX_PATH), $(AUX_SRCS)) 

#######COLORS_FOR_MESSAGES
RED				:=	\033[0;31m
GREEN			:=	\033[0;32m
BLUE			:=	\033[0;34m
CYAN			:=	\033[0;36m
GREY			:=	\033[90m
EC				:=	\033[0m

#######COMPILER_SETTINGS
CC_LFT			:= cc
FLAGS_LFT		:= -Wall -Wextra -Werror -g

define progress
    @$(eval COMPILED_OBJS=$(shell echo "$$(($(COMPILED_OBJS) + 1))"))
    @if [ "$(MSG_PRINTED)" = false ]; then \
        printf "$(GREY)\nCompiling $(EC)$(CYAN)$(1)$(EC)$(GREY), please wait$(EC)"; \
        printf "$(GREY)\n$(EC)"; \
        $(eval MSG_PRINTED=true) \
    fi
    @printf "\r$(GREY)"
    @perl -e 'printf "%-50s", "#" x int(($(COMPILED_OBJS) * 50 / $(TOTAL_OBJS)));'
    @printf "$(EC)$(CURSOR_SAVE)"
    @printf "\033[3C"
    @printf "$(GREY)%.2f%%$(EC)" "$(shell echo "$(COMPILED_OBJS) / $(TOTAL_OBJS) * 100" | bc -l)"
    @printf "$(CURSOR_RESTORE)"
endef
