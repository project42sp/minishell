NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3 -I includes

SRCS	= \
		src/lexer/lexer.c			\
		src/lexer/lexer_utils.c	\
		src/token/token_cmd_create.c	\
		src/parser/parser.c			\
		src/tree/tree_print.c		\
		src/tree/tree_build.c		\
		src/tree/tree_utils.c		\
		src/executor/execution_base.c	\
		src/executor/execution_redir.c	\
		src/free/tree_free.c		\
		src/free/token_list_free.c	\
		src/free/envp_free.c	\
		src/utils/envp.c		\
		src/utils/envp_rebuilt.c	\
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
		--track-fds=yes		\
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

$(OBJS_DIR)/%.o: src/lexer/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/parser/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/utils/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR)/%.o: src/executor/%.c | $(OBJS_DIR)
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
