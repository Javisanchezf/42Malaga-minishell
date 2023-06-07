# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 18:02:29 by javiersa          #+#    #+#              #
#    Updated: 2023/06/07 15:13:37 by antdelga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# General variables
NAME = minishell.a
PROGRAM = minishell
CFLAGS = -Wall -Werror -Wextra -I "/Users/$(USER)/.brew/opt/readline/include/"
PERSONALNAME = Minishell
LIBFTPLUS = libftplus
LIBFTPLUS_LIB = $(LIBFTPLUS)/libftplus.a
CC = gcc
CLEAN = rm -Rf
SRC = $(wildcard src/*.c)
OBJS := $(SRC:.c=.o)

# Personal use variables
PARAMS = 4 2 3 4 5
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)
USER := $(shell whoami)
GITIGNORE = .gitignore

# General rules

all: $(PROGRAM)


$(PROGRAM): $(LIBFTPLUS_LIB) $(NAME)
	@$(CC) $(CFLAGS) $(NAME) $(LIBFTPLUS_LIB) -L"/Users/$(USER)/.brew/opt/readline/lib/" -o $(PROGRAM) -lreadline
	@echo "$(MAGENTA)Program $(PERSONALNAME) created successfully.$(DEFAULT)"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}
	@echo "$(GREEN)Compiling:$(DEFAULT) $(notdir $<)"
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library $(NAME) created successfully.$(DEFAULT)"
clean: libftplusclean
	@$(CLEAN) ./$(OBJS)
	@echo "$(RED)Removing:$(DEFAULT) All objects from $(PERSONALNAME)."
fclean: libftplusfclean clean
	@$(CLEAN) ./$(NAME) ./$(PROGRAM)
	@echo "$(RED)Removing:$(DEFAULT) Library $(NAME)."
	@echo "$(RED)Removing:$(DEFAULT) Program $(PROGRAM)."
re: fclean libftplusclean all libftplusmake

# Lib rules

$(LIBFTPLUS_LIB): libftplusmake

libftplusmake:
	@make -C $(LIBFTPLUS)
libftplusclean:
	@make clean -C $(LIBFTPLUS)
libftplusfclean:
	@make fclean -C $(LIBFTPLUS)
libftplusre: libftplusclean libftplusmake

#Personal use
git: fclean $(GITIGNORE)
	@git add *
	@echo "$(BOLD)$(YELLOW)Git ($(GIT_BRANCH)):$(WHITE) Adding all archives.$(DEFAULT)"
	@git commit -m "[$(DATETIME)] - Little changes by $(USER)"
	@echo "$(BOLD)$(CYAN)Git ($(GIT_BRANCH)):$(WHITE) Commit this changes in brunch\
	 $(GIT_BRANCH) with "[$(DATETIME)] - Little changes by $(USER)".$(DEFAULT)"
	@git push --set-upstream origin $(GIT_BRANCH)
	@echo "$(BOLD)$(GREEN)Git ($(GIT_BRANCH)):$(WHITE) Pushing all changes.$(DEFAULT)"
submodules:
	@git submodule update --init --recursive
	@echo "$(GREEN)The submodules have been created and updated successfully.$(DEFAULT)"
$(GITIGNORE):
	@echo ".*\n*.out\n*.o\n*.a\n*.dSYM">.gitignore
	@echo "$(GREEN)Creating:$(DEFAULT) Gitignore."
42prepare: submodules
	@rm -rf .git*
	@echo "$(GREEN)All .git removed.$(DEFAULT)"
valgrind_datarace: $(PROGRAM)
	valgrind --tool="helgrind" ./$(PROGRAM) $(PARAMS)
valgrind_leaks: $(PROGRAM)
	valgrind --leak-check=full -s ./$(PROGRAM) $(PARAMS)

#COLORS
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
DEFAULT	:= \033[0m

.PHONY : all clean fclean re \
libftplusmake libftplusclean libftplusfclean libftplusre \
git submodules gitignore 42prepare valgrind_datarace valgrind_leaks
