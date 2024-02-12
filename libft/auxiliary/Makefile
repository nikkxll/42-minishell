#AUXILIARY_FUNCTIONS_MAKEFILE
include ../.make
NAME	:=	auxiliary.a
OBJS	:=	$(AUX_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar -crs $(NAME) $(OBJS)
	@ar -crs ../libft.a $(OBJS)
	@echo "$(GREY)-AUXILIARY_FUNCTIONS are ready$(NC)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re