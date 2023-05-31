#include "minishell.h"

// int archivo = open(nombreArchivo, O_WRONLY | O_CREAT, 0644);

int	nose(t_data *data, int i, int j, char type)
{
	int	cont;

	cont = 0;
	while (data->cmd[i].opt[j][cont] == '<' || data->cmd[i].opt[j][cont] == '>')
	{
		if (data->cmd[i].opt[j][cont] != type)
			return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1); //Puede que haya que cambiar el numero de comandos a i + 1
		cont++;
	}
	if (cont > 2)
		return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1);
	return (0);
}

int	parse_redirections(t_data *data, int i)
{
	int	j;

	data->cmd[i].input = ft_strdup("");
	data->cmd[i].output = ft_strdup("");
	j = -1;
	while (data->cmd[i].opt[++j])
	{
		if (data->cmd[i].opt[j][0] == '<')
			if (nose(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
		if (data->cmd[i].opt[j][0] == '>')
			if (nose(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
	}
	return (0);
}