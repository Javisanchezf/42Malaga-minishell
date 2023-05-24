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
# include <sys/wait.h>
/*----------------------------STRUCTS----------------------------*/

typedef struct s_command
{
	char	**opt;
	char	*path;
	char	*input;
	char	*output;
	int		output_tipe; //-1 estandar, 0 para > y 1 para >>
	int		input_tipe; //-1 estandar, 0 para < y 1 para <<
}				t_command;

typedef struct s_env
{
	char	*variable;
	char	*value;
}				t_env;

typedef struct s_data
{
	t_env		*env;
	int			n_envs;
	t_command	*cmd;
	int			n_commands;
	int			lastcmd_value;
}				t_data;

/*----------------------------PARSE UTILS----------------------------*/

void	forward_quotes(char *input, int *i);
void	forward_operators(char *input, int *i);
int		is_separator_char(char c);
char	*ft_getenv(char *env, t_data *data, int start, int size);

/*----------------------------SPLITS----------------------------*/

char	**split_by_args(char *input, int i, int j, int size_split);
char	**split_by_pipes(char *input, int n_commands, int i);

/*----------------------------CLEAN----------------------------*/

void	clean_commands(t_data *data);
void	clean_and_exit_success(t_data *data);

/*----------------------------OTHERS----------------------------*/

char	*readlineplus(t_data *data);
void	parse_line(char *input, t_data *data);

/*----------------------------SIGNALS----------------------------*/
void	sigint_handler(int sig);
void	ctrl_d(char *input);

#endif