#ifndef MINISHELL_H
# define MINISHELL_H

/*----------------------------HEADER----------------------------*/

# define HEADER \
("\n\033[34;1m\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
\n\
                A simple shell implemented in C                    \n\
                             By                                    \n\
                --- javiersa && antdelga ---                       \n\
\n\033[0m")

/*----------------------------LIBRARIES----------------------------*/

# include "../libftplus/libftplus.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/*----------------------------STRUCTS----------------------------*/

typedef struct s_cdm
{
	char	**opt;
	char	*cmd;
	char	*input;
	char	*output;
}				t_command;

typedef struct s_env
{
	char	*variable;
	char	*value;
}				t_env;

typedef struct s_data
{
	t_env		*env;
	t_command	*cmd;
	pid_t		*pid;
}				t_data;

/*----------------------------PARSE UTILS----------------------------*/

void	forward_quotes(char *input, int *i);
void	forward_operators(char *input, int *i);
int		is_separator_char(char c);

/*----------------------------OTHERS----------------------------*/

void	ft_getline(void);
void	parse(char *input, int n_commands);
char	**ft_split_mod(char *input, int i, int j, int size_split);

#endif