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

# include "../libftplus/libftplus.h"
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libgen.h>
# include <signal.h>
# include <fcntl.h>

# define CMD_ERROR "Command not found\n"
# define PIPE_ERROR "Pipe error\n"

typedef struct s_command
{
	char	*cmd;
	char	**opt;
	char	**envp;

}	t_command;

typedef struct s_pipe
{
	int		cmd_count;
	int		piping[2];
	int		fd_in;
	int		fd_t_in;
	int		fd_out;
	int		fd_t_out;
}	t_pipe;


/* Utils (cuidado con no sobreescribirse) */
char	*find_path(char **envp);
void	leaks(void);

/* Functions for minishell.c */
void	ft_prompt(t_pipe *link, t_command *cmd);
char	*ft_header(void);

/* Functions for pipe_utils.c */
void	sub_dup2(int zero, int one);
void	check_awk(t_command *cmd);

/* Functions for pipes.c */
void	child_generator(t_pipe *link, t_command *cmd);
void	create_tube(t_pipe *link, int cont);
void	child(t_command *cmd);

/*Functions for error.c*/
void	argc_error(void);
void	err_msg(char *str);
void	err_msg_exit(char *str);

/*Functions for fere.c*/
void	free_matrix(char **str);
void	close_pipes(int *tube);

#endif
