# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/29 13:01:10 by elehtora          #+#    #+#              #
#    Updated: 2022/09/29 14:25:58 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fs_ls

SRCDIR	:= sources
SRCS	:= main.c

OBJDIR	:= objects
OBJS	:= $(SRCS:.c=.o)
OBJS	:= $(addprefix $(OBJDIR)/,$(OBJS))

LIB		:= -Llibft -lft
INCL	:= -Iincludes -Ilibft

CC		:= gcc
CFLAGS	:= -Wall -Werror -Wextra # Not specified by subject, but ?

# Rules
all : $(NAME)

$(NAME) : $(OBJDIR) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $(NAME)

$(OBJDIR) :
	-mkdir -p $(OBJDIR)

$(LIBFT) :
	$(MAKE) -C $(LIBFT)

%.o : %.c
	$(CC) $(CFLAGS) $(INCL) -c $< -o $@

