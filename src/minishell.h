/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 13:48:55 by javiersa          #+#    #+#             */
/*   Updated: 2023/06/06 14:36:53 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		output_type;
	char	*output;
	int		input_type;
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

/*----------------------------COLORS----------------------------*/
# define BOLD	"\033[1m"
# define BLACK	"\033[30;1m"
# define RED	"\033[31;1m"
# define GREEN	"\033[32;1m"
# define YELLOW	"\033[33;1m"
# define BLUE	"\033[34;1m"
# define MAGENTA	"\033[35;1m"
# define CYAN	"\033[36;1m"
# define WHITE	"\033[37;1m"
# define DEFAULT	"\033[0m"

/*----------------------------MACROS----------------------------*/
# define CMD_ERROR "Command not found"
# define PIPE_ERROR "Pipe error"

/*----------------------------PARSE GENERAL----------------------------*/
char	*readlineplus(t_data *data);
void	parse_line(char *input, t_data *data);
int		parse_redirections(t_data *data, int i);

/*----------------------------PARSE UTILS----------------------------*/
char	**split_by_pipes(char *input, int n_commands, int i);
char	**split_by_args(char *input, int i, int j, int size_split);
char	**chain_delete_one(char **array, int index);
void	forward_quotes(char *input, int *i);
char	*ft_getenv(char *env, t_data *data, int start, int size);
char	*dollar_heredoc(t_data *data, char *str);

/*----------------------------CLEAN----------------------------*/
void	clean_commands(t_data *data);
void	clean_and_exit_success(t_data *data);

/*----------------------------SIGNALS----------------------------*/
void	sigint_handler(int sig);
void	ctrl_d(char *input, t_data *data);

/*----------------------------UTILS----------------------------*/
void	ft_leaks(void);
void	sub_dup2(int zero, int one);
char	*ft_getcmd(t_data *data, char *cmd);
void	reset_fd(int *fds);
void	print_fds(t_data *data, t_command *cmd);

/*----------------------------PIPES----------------------------*/
void	child_generator(t_data *data);

/*----------------------------BUILTINS----------------------------*/
int		select_builtin(t_data *data, t_command *comando);

/*----------------------------BUILTINS----------------------------*/
int		select_builtin(t_data *data, t_command *comando);
void	bt_echo_n(t_command *cmd);
void	bt_pwd(void);
void	bt_cd(t_data *data, t_command *cmd);
void	bt_env(t_data *data);
void	bt_export_aux(t_data *data, t_command *cmd);
void	bt_export(t_data *data, t_command *cmd, int loc);
void	bt_unset_aux(t_data *data, t_command *cmd, char **new_env);
void	bt_unset(t_data *data, t_command *cmd, int loc, int *cont);

/*----------------------BUILTINS UTILS----------------------*/
int		choose_largest_string(char *a, char *b);
void	modify_values(int *index, int *loc, int *offset, int *cont);
void	restart_loop(int *cont, int *loc, char **aux);
void	bt_unset_init(t_data *data, t_command *cmd);

#endif