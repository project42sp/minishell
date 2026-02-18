NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3

SRCS_FILES = \
			tree_print.c	\
			tree_node_create.c	\
			tree_build.c	\
			main.c

SRCS		= $(addprefix src/, $(SRCS_FILES))
OBJS_DIR	= obj
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

DIR_LIBFT	= libft
LIBFT		= $(DIR_LIBFT)/libft.a

#-----	Recipes	-----

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(DIR_LIBFT) -lft -o $@

$(OBJS_DIR)/%.o: src/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -sC $(DIR_LIBFT) all --no-print-directory


#-----	Clean	-----
clean :
	$(MAKE) -sC $(DIR_LIBFT) $@
	rm -fr $(OBJS_DIR)

fclean :
	rm -f $(NAME)
	$(MAKE) -sC $(DIR_LIBFT) $@

re : fclean all

