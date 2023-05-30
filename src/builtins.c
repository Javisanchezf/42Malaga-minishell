#include "minishell.h"

void bt_cd(t_data *data, t_command *cmd)
{
	// char	*aux;
	int		i;
	(void) data;
	printf("%s\n", cmd->opt[1]);
    if (chdir(cmd->opt[1]) != 0)
		perror("cd");
	i = -1;
	while(ft_strncmp(data->env[++i], "PWD=", 4) != 0)
		;
	if (data->env[i])
	{
		printf("entro\n");
		free(data->env[i]);
		data->env[i] = ft_strdup("/Users/antdelga/Desktop");
	}

	exit(0);
	
}

void	select_builtin(t_data *data, t_command *comando)
{
	if (ft_strncmp(comando->opt[0], "cd", 2) == 0)
		bt_cd(data, comando);
}
