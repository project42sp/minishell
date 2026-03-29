NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3 -I includes

SRCS	= \
		src/token/token_cmd_create.c	\
		src/tree/tree_build.c		\
		src/tree/tree_utils.c		\
		src/free/tree_free.c		\
		src/free/token_list_free.c	\
		src/main.c

OBJS_DIR	= obj
OBJS		= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

DIR_LIBFT	= libft
LIBFT		= $(DIR_LIBFT)/libft.a

#-----	Recipes	-----

all: $(NAME)

val:
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		--suppressions=readline.supp \
		./$(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(DIR_LIBFT) -lft -lreadline -o $@

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/token/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/tree/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/free/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(LIBFT):
	$(MAKE) -sC $(DIR_LIBFT) all --no-print-directory

#-----	Clean	-----
clean:
	$(MAKE) -sC $(DIR_LIBFT) $@
	rm -fr $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) -sC $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re val