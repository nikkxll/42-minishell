#AUXILIARY_FUNCTIONS_MAKEFILE
include ../.make
NAME	:=	auxiliary.a
OBJS	:=	$(AUX_SRCS:.c=.o)

TOTAL_OBJS		:= $(words $(OBJS))
COMPILED_OBJS	:= 0
MSG_PRINTED 	:= false

all: $(NAME)

$(NAME): $(OBJS)
	@ar -crs $(NAME) $(OBJS)
	@ar -crs ../libft.a $(OBJS)
	@echo "$(GREEN)\n\nLIBFT is ready$(NC)"
	@echo "$(GREEN)FT_PRINTF is ready$(NC)"
	@echo "$(GREEN)GET_NEXT_LINE is ready$(NC)"
	@echo "$(GREEN)AUXILIARY_FUNCTIONS_SET is ready$(NC)"

%.o: %.c
	@$(CC_LFT) $(FLAGS_LFT) -c $< -o $@
	@$(call progress,"auxiliary")

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re