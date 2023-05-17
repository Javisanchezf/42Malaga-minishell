#ifndef MINISHELL_H
# define MINISHELL_H

# define HEADER ("\n\033[34;1m\
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
# define BOLD ("\033[1m")
# define BLACK ("\033[30;1m")
# define RED ("\033[31;1m")
# define GREEN ("\033[32;1m")
# define YELLOW ("\033[33;1m")
# define BLUE ("\033[34;1m")
# define MAGENTA ("\033[35;1m")
# define CYAN ("\033[36;1m")
# define WHITE ("\033[37;1m")
# define DEFAULT ("\033[0m")

# include "../libftplus/libftplus.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libgen.h>

typedef struct s_cdm
{
	char	*cmd;  // COMANDO: LS, PWD...
	char	**opt;  // OPCIONES: -a, -ld...
	char	*path; // RUTA DEL COMANDO
	char	unif; // |, <, >, ...
}				t_cmd;

typedef struct s_env
{
	char	*variable;
	char	*value;
}				t_env;

typedef struct s_data
{
	t_env		*env;
}				t_data;

void	ft_getline(void);

#endif