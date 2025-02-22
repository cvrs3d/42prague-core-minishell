# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yustinov <yustinov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/28 16:40:04 by yustinov          #+#    #+#              #
#    Updated: 2025/02/22 17:50:52 by yustinov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -rf

SRCS_DIR	= src/
OBJS_DIR	= obj/
INCS_DIR	= includes/

SRCS		= src/main.c \
			src/builtins.c \
			src/builtins2.c \
			src/cmd_finder.c \
			src/constructors.c \
			src/constructors2.c \
			src/env_utils.c \
			src/env_utils2.c \
			src/env_utils3.c \
			src/evaluator.c \
			src/executor.c \
			src/expander.c \
			src/ft_split.c \
			src/handlers_null.c \
			src/heredoc.c \
			src/itoa.c \
			src/parser.c \
			src/parser2.c \
			src/parser_utils.c \
			src/signals.c \
			src/strings.c \
			src/strings2.c \
			src/strings3.c \
			src/utils.c \
			src/bonus.c \
			src/bonus2.c \
			src/builtins3.c \
			src/free_er.c \
			src/utils2.c \
			src/strings4.c

OBJS		= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)

READLINE	= -lreadline

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(READLINE) -o $(NAME)
	@echo "minishell compiled!"

all: $(NAME)

clean:
	@$(RM) $(OBJS_DIR)
	@echo "Objects cleaned!"

fclean: clean
	@$(RM) $(NAME)
	@echo "Everything cleaned!"

re: fclean all

.PHONY: all clean fclean re
