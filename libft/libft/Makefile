#LIBFT_PROJECT_MAKEFILE
include ../.make
NAME			:=	libft.a
OBJS			:=	$(LFT_SRCS:.c=.o)

TOTAL_OBJS		:= $(words $(OBJS))
COMPILED_OBJS	:= 1
MSG_PRINTED 	:= false

all: $(NAME)

$(NAME): $(OBJS)
	@ar -crs $(NAME) $(OBJS)
	@ar -crs ../libft.a $(OBJS)
	@echo "$(GREEN)\n\nLIBFT_PRJ is ready$(NC)"
	@echo "$(GREY)PRINTF_PRJ is not ready$(NC)"
	@echo "$(GREY)GET_NEXT_LINE_PRJ is not ready$(NC)"
	@echo "$(GREY)AUXILIARY_FUNCTIONS is not ready$(NC)"

%.o: %.c
	@$(CC_LFT) $(FLAGS_LFT) -c $< -o $@
	@$(call progress,"libft")

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re