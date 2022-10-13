# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/18 11:10:47 by elehtora          #+#    #+#              #
#    Updated: 2022/10/14 02:50:06 by elehtora         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### VARIABLES ###

# Target build executable
NAME		:= libftprintf.a

# Name to feed as library path for user (ftprintf)
BIN_LIB		:= $(subst lib,,$(basename $(NAME)))

SRCS		:= ft_printf.c \
			   integer.c \
			   chars.c \
			   float.c \
			   hex.c \
			   modifiers.c \
			   field_manipulation.c \
			   error.c \
			   numerical_utils.c \
			   oct.c

SRCDIR		:= sources

LIBFT_DIR	:= libft
LIBFT		:= $(addprefix $(LIBFT_DIR), libft.a)
LIBFT_OBJS	= $(shell find $(LIBFT_DIR) -type f -regex '.*/*.o')
OBJDIR		:= objects
OBJS		:= $(SRCS:.c=.o)
OBJS		:= $(addprefix $(OBJDIR)/,$(OBJS))

INCL		:= -Iincludes -I$(LIBFT_DIR)

# The libft library is included from ./lib (see header)

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra -O3
RM			:= /bin/rm -rf


### RULES ###
.PHONY : build libft test clean fclean re debug flags

all : build

$(NAME) : $(OBJS)
	@echo "Linking as library \033[1;32m$(NAME)...\033[0m"
	@ar -rcs $@ $(OBJS) $(LIBFT_OBJS)

build : $(OBJDIR)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) $(NAME)

$(OBJDIR) :
	@mkdir -p $(@)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "Creating object file:\t\033[1;32m$(notdir $(<:.c=.o))\033[0m"
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@

clean :
	@$(RM) $(OBJDIR) *.dSYM
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaned object files of \033[1;32m$(NAME)\033[0m"

fclean : clean
	@$(RM) $(NAME) $(TEST_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Cleaned build executable of \033[1;32m$(NAME)\033[0m"

re : fclean all
