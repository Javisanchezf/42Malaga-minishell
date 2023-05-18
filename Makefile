NAME = minishell.a
PROGRAM = minishell
CFLAGS = -Wall -Werror -Wextra -I "/Users/$(USER)/.brew/opt/readline/include/"
PERSONALNAME = Minishell
LIBFTPLUS = libftplus
CC = gcc
CLEAN = rm -Rf
SRC = src/main.c src/get_line.c src/parse_commands.c src/split_mod.c src/parse_utils.c
PARAMS = 4 2 3 4 5
DATETIME := $(shell date +%Y-%m-%d' '%H:%M:%S)
GIT_BRANCH := $(shell git rev-parse --abbrev-ref HEAD)

OBJS := $(SRC:.c=.o)

all: libftplusmake2 $(PROGRAM)

$(PROGRAM): $(NAME)
	@$(CC) $(CFLAGS) $(NAME) $(LIBFTPLUS)/libftplus.a -L"/Users/$(USER)/.brew/opt/readline/lib/" -o $(PROGRAM) -lreadline
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
re: fclean libftplusclean all libftplusmake2

libftplusmake:
	@make -C $(LIBFTPLUS)
libftplusmake2:
	@make nolibtool -C $(LIBFTPLUS)
libftplusclean:
	@make clean -C $(LIBFTPLUS)
libftplusfclean:
	@make fclean -C $(LIBFTPLUS)
libftplusre: libftplusclean libftplusmake

#Personal use
git: fclean gitignore
	@git add *
	@echo "$(BOLD)$(YELLOW)Git:$(WHITE) Adding all archives.$(DEFAULT)"
	@git commit -m "Little changes $(DATETIME)"
	@echo "$(BOLD)$(CYAN)Git:$(WHITE) Commit this changes with "Little changes $(DATETIME)".$(DEFAULT)"
	@git push
	@echo "$(BOLD)$(GREEN)Git:$(WHITE) Pushing all changes.$(DEFAULT)"
brunch_git: fclean gitignore
	@git add *
	@echo "$(BOLD)$(YELLOW)Git $(RED)($(GIT_BRANCH)):$(WHITE) Adding all archives.$(DEFAULT)"
	@git commit -m "Little changes $(DATETIME)"
	@echo "$(BOLD)$(CYAN)Git:$(WHITE) Commit this changes in brunch $(GIT_BRANCH) with "Little changes $(DATETIME)".$(DEFAULT)"
	@git push --set-upstream origin $(GIT_BRANCH)
	@echo "$(BOLD)$(GREEN)Git:$(WHITE) Pushing all changes.$(DEFAULT)"
submodules:
	@git submodule update --init --recursive
	@echo "$(GREEN)The submodules have been created and updated successfully.$(DEFAULT)"
gitignore:
	@echo ".*\n*.out\n*.o\n*.a">.gitignore
	@echo "$(GREEN)Creating:$(DEFAULT) Gitignore."
42prepare: submodules
	@rm -rf $(LIBFT)/.git
	@rm -rf $(NEXTILE)/.git
	@rm -rf $(PRINTF)/.git
	@rm -rf .git .gitmodules
	@echo "$(GREEN)All .git removed.$(DEFAULT)"
valgrind:
	valgrind --leak-check=full ./$(PROGRAM) $(PARAMS)

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

.PHONY : all clean fclean re bonus git gitignore submodules 42prepare .c.o
