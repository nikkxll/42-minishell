#GET_NEXT_LINE_PROJECT_MAKEFILE
include ../.make
NAME	:= get_next_line.a
OBJS	:= $(GNL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	@ar -crs $(NAME) $(OBJS)
	@ar -crs ../libft.a $(OBJS)
	@echo "$(GREY)-GET_NEXT_LINE_PRJ is ready$(NC)"

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re