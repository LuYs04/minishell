# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/23 14:33:23 by luatshem          #+#    #+#              #
#    Updated: 2024/02/06 18:05:41 by luatshem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME     = minishell
GCC      = gcc
CFLAGS   = -Wall -Wextra -Werror #-g -fsanitize=address
RM       = rm -rf
OUTPUT   = ./$(NAME)
LIBS     = -I./hf/ -I./readline/include
LIBS_DIR = hf

SRC = src
OBJ = obj
SUBDIRS = main utils builtins pipe parser redirection

SRC_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(SRC)/, $(dir)))
OBJ_DIR = $(foreach dir, $(SUBDIRS), $(addprefix $(OBJ)/, $(dir)))

SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c))
OBJS = $(subst $(SRC), $(OBJ), $(SRCS:.c=.o))
LIB_DIR = $(foreach dir, $(LIBS_DIR), $(wildcard $(dir)/*.h))

LIBFT     = ft
LIBFT_DIR = ./lib$(LIBFT)/

RDLINE        := readline
RDLINE_PATH   = $(addprefix $(shell pwd)/, $(RDLINE))
RDLINE_MAIN   = $(addprefix $(RDLINE), -main)
RDLINE_RESERV = $(addprefix $(RDLINE), -lib)
RDLINE_DIR    = ./$(RDLINE)/lib

all: readline $(NAME)
	@echo > /dev/null

bonus: all

readline: Makefile
	@if [ -d $(RDLINE) ]; then \
		make READLINE_READY; \
	else \
		make readline-util; \
	fi

READLINE_READY:
	@echo "all is done in readline" 

readline-util:
	@$(RM) $(RDLINE_RESERV)
	@cp -R $(RDLINE_MAIN) $(RDLINE_RESERV)
	@cd $(RDLINE_RESERV) && exec ./configure --prefix=${RDLINE_PATH}
	@make -C ./$(RDLINE_RESERV)
	@make -C ./$(RDLINE_RESERV) install
	@$(RM) $(RDLINE_RESERV)

$(NAME): $(LIB_DIR) Makefile $(OBJS)
	@make -C $(LIBFT_DIR) all
	@$(GCC) -o $(NAME) $(OBJS) -g $(CFLAGS) $(LIBS) -L$(LIBFT_DIR) -l$(LIBFT) -L$(RDLINE_DIR) -l$(RDLINE) -lncurses

$(OBJ)/%.o: $(SRC)/%.c $(LIB_DIR) Makefile
	@mkdir -p $(OBJ) $(OBJ_DIR)
	@$(GCC) $(CFLAGS) $(LIBS) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@$(RM) $(RDLINE)

re: fclean all

.PHONY: all clean fclean re
