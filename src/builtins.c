#include "minishell.h"

//Te he quitado el leak que habia reasignando envs (pero yo haria la reasignacion d los envs (OLDPWD y PWD) cuando este la funcion export llamando a esa)
void	bt_cd(t_data *data, t_command *cmd)
{
	int		i;
	char	*aux;
	char	aux2[2048];

	if (!cmd->opt[1])
	{
		aux = ft_getenv("ZDOTDIR", data, 0, 7);
		if (chdir(aux) != 0)
			return (free(aux), perror("cdsd"));
		free(aux);
	}
	else
		if (chdir(cmd->opt[1]) != 0)
			return (perror("cd"));
	i = 0;
	while (ft_strncmp(data->env[i], "PWD=", 4) != 0)
		i++;
	if (data->env[i])
	{
		ft_free_and_null((void **)&data->env[i]);
		if (getcwd(aux2, 2048) == NULL)
			return (perror("pwd"));
		data->env[i] = ft_strjoin("PWD=", aux2);
	}
}

int	select_builtin(t_data *data, t_command *comando)
{
	if (ft_strncmp(comando->opt[0], "cd", 2) == 0)
		return (bt_cd(data, comando), 1);
	return (0);
}
