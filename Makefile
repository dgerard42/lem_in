# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgerard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 17:24:50 by dgerard           #+#    #+#              #
#    Updated: 2018/03/10 15:42:48 by sbalcort         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Werror -Wextra

LIBFT = libft/libft.a

PRINTF = printf/libftprintf.a

SRCS =	main.c\
		ll_fts.c\
		test_fts.c\
		bfs.c\
		bfs_cont.c\
		send_ants.c\
		learn_colony.c\

ODIR = ofiles

OFILES = $(addprefix $(ODIR)/,$(SRCS:.c=.o))

$(ODIR)/%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@
	@/bin/echo -n "❂❂❂❂"

all: $(NAME)

$(NAME): $(OFILES)
	@echo "\033[32m[$(NAME) .o files created ( ͡° ͜ʖ ͡°)]\033[0m"
	@make -C libft/
	@make -C printf/
	@gcc $(FLAGS) -o $@ $(OFILES) $(LIBFT) $(PRINTF)
	@echo "\033[32m[$(NAME) executable created ( ͡° ͜ʖ ͡°)]\033[0m"

$(OFILES): | $(ODIR)

$(ODIR):
	@mkdir $(ODIR)

clean:
	@make -C libft/ clean
	@make -C printf/ clean
	@rm -rf $(ODIR)
	@echo "\033[31m[$(NAME) .o files deleted (╯°□°）╯︵ ┻━┻ ]\033[0m"

fclean: clean
	@/bin/rm -f rm $(NAME)
	@make -C libft/ fclean
	@make -C printf/ fclean
	@echo "\033[31m[$(NAME) executable deleted ᕙ(⇀‸↼‶)ᕗ ]\033[0m"

re: fclean all
