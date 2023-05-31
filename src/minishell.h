#ifndef MINISHELL_H
# define MINISHELL_H

/*----------------------------HEADER----------------------------*/

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

/*----------------------------LIBRARIES----------------------------*/

# include "../libftplus/libftplus.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
/*----------------------------STRUCTS----------------------------*/

typedef struct s_command
{
	char	**opt;
	char	*path;
	char	*input;
	int		output_tipe; //-1 estandar, 0 para > y 1 para >>
	char	*output;
	int		input_tipe;  //-1 estandar, 0 para < y 1 para <<
}	t_command;

typedef struct s_link
{
	int		piping[2];
	int		fd_in;
	int		fd_t_in;
	int		fd_out;
	int		fd_t_out;
}	t_link;

typedef struct s_data
{
	char		**env;
	t_command	*cmd;
	int			n_commands;
	int			lastcmd_value;
	char		**rute;
	t_link		tube;
}				t_data;

/*----------------------------MACROS----------------------------*/
# define CMD_ERROR "Command not found"
# define PIPE_ERROR "Pipe error"

/*----------------------------PARSE GENERAL----------------------------*/

char	*readlineplus(t_data *data);
void	parse_line(char *input, t_data *data);

/*----------------------------PARSE UTILS----------------------------*/

void	forward_quotes(char *input, int *i);
char	*ft_getenv(char *env, t_data *data, int start, int size);
char	**split_by_pipes(char *input, int n_commands, int i);
char	**split_by_args(char *input, int i, int j, int size_split);

/*----------------------------CLEAN----------------------------*/

void	clean_commands(t_data *data);
void	clean_and_exit_success(t_data *data);

/*----------------------------SIGNALS----------------------------*/
void	sigint_handler(int sig);
void	ctrl_d(char *input, t_data *data);

/*----------------------------UTILS----------------------------*/
void	ft_leaks(void);
void	sub_dup2(int zero, int one);
char  	*ft_getcmd(t_data *data, char *cmd);

/*----------------------------PIPES----------------------------*/
void	child_generator(t_data *data);

/*----------------------------BUILTINS----------------------------*/
void	select_builtin(t_data *data, t_command *comando);


#endif