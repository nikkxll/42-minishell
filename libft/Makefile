#LIBFT_MAKEFILE
include .make
NAME = libft.a

all: $(NAME)

$(NAME): $(LIBFT_SOURSES)
	@echo	"$(GREEN)+--------------------------------------------------------+$(EC)"
	@echo	"$(GREEN)|                     BUILDING LIBFT                     |$(EC)"
	@echo	"$(GREEN)+--------------------------------------------------------+$(EC)"
	@$(MAKE) -C $(LFT_PATH)
	@$(MAKE) -C $(PRINTF_PATH)
	@$(MAKE) -C $(GNL_PATH)
	@$(MAKE) -C $(AUX_PATH)
	@echo	"$(GREEN)+--------------------------------------------------------+$(EC)"
	@echo	"$(GREEN)|                     LIBFT IS READY!                    |$(EC)"
	@echo	"$(GREEN)+--------------------------------------------------------+$(EC)"
clean:
	@$(MAKE) clean -C $(LFT_PATH)
	@$(MAKE) clean -C $(PRINTF_PATH)
	@$(MAKE) clean -C $(GNL_PATH)
	@$(MAKE) clean -C $(AUX_PATH)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LFT_PATH)
	@$(MAKE) fclean -C $(PRINTF_PATH)
	@$(MAKE) fclean -C $(GNL_PATH)
	@$(MAKE) fclean -C $(AUX_PATH)
	@echo "$(GREEN)LIBFT REMOVED!$(EC)"

re: fclean all