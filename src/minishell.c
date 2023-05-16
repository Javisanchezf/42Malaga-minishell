#include "../inc/minishell.h"

char	*ft_header(void)
{
	char	path[1024];
	char	*tmp;

	if (getcwd(path, sizeof(path)) == NULL)
		exit(EXIT_FAILURE); // CAMBIAR
	tmp = ft_strrchr(path, '/') + 1;
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin("\033[36;1m", tmp);
	if (!tmp)
		return (NULL);
	free(tmp);
	return (ft_strjoin(tmp, " -> \033[0m"));
}

void	ft_prompt(t_pipe *link, t_command *cmd)
{
	char	*in;
	char	*prompt;

	while (1)
	{
		prompt = ft_header();
		if (!prompt)
			exit(EXIT_FAILURE); // CAMBIAR
		in = readline(prompt);
		add_history(in);
		if (ft_strncmp(in, "pitos", 5) == 0) // CTRL + D
			child_generator(link, cmd);
		else if (!ft_strncmp(in, "exit", 5) || !ft_strncmp(in, "EXIT", 5))
		{
			free(in);
			break ;
		}
		free(in);
		free(prompt);
	}
}

/* NO SIRVE, SOLO DE PRUEBA HASTA TENER EL PARSE */
int	main(int argc, char **argv, char **envp)
{
	t_pipe		link;
	t_command	*cmd;

	(void)argc;
	(void)argv;
	cmd = malloc(sizeof(t_command) * 3);
	link.fd_in = dup(0);
	link.fd_t_in = dup(0);
	link.fd_t_out = dup(1);
	link.cmd_count = 3;
	link.envp = envp;
	cmd[0].opt = ft_split("ls -l -a", ' ');
	cmd[0].cmd = "/bin/ls";
	cmd[1].opt = ft_split("wc -l", ' ');
	cmd[1].cmd = "/usr/bin/wc";
	cmd[2].opt = ft_split("cat -e", ' ');
	cmd[2].cmd = "/bin/cat";

	/* ESTO SÍ PODRÍA SERVIR */
	if (argc != 1)
		argc_error();
	printf("%s", (char *)&(HEADER));
	ft_prompt(&link, cmd);
	exit(0);
}
