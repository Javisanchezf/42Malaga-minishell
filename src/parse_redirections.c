#include "minishell.h"

char	**chain_delete_one(char **array, int index)
{
	int		size;
	char	**new_array;
	int		i;
	int		j;

	size = 0;
	size = ft_split_size(array);
	if (index < 0 || index >= size)
		return (array);
	new_array = (char **)ft_calloc((size), sizeof(char *));
	if (!new_array)
		return (array);
	i = -1;
	j = 0;
	while (++i < size)
	{
		if (i != index)
		{
			new_array[j] = array[i];
			j++;
		}
	}
	ft_free_and_null((void **)&array[index]);
	ft_free_and_null((void **)&array);
	return (new_array);
}

void	input_parse(t_data *data, int i, int j, int cont)
{
	int		k;
	int		file;

	k = 0;
	while (data->cmd[i].opt[j][k] && (data->cmd[i].opt[j][k] == '<' || ft_isspace(data->cmd[i].opt[j][k])))
		k++;
	data->cmd[i].input_type = cont;
	ft_free_and_null((void **)&data->cmd[i].output);
	data->cmd[i].output = ft_substr(data->cmd[i].opt[j], k, ft_strlen(data->cmd[i].opt[j]) - k);
	if (cont == 1)
	{
		file = open(data->cmd[i].output, O_RDONLY, 0644);
		close(file);
		//if (file == -1 && errno == EACCES) sustituir todo por: minishell: a.txt: Permission denied
	}
	//el << rarito
	data->cmd[i].opt = chain_delete_one(data->cmd[i].opt, j);
}

void	output_parse(t_data *data, int i, int j, int cont)
{
	int		k;
	int		file;

	k = 0;
	while (data->cmd[i].opt[j][k] && (data->cmd[i].opt[j][k] == '>' || ft_isspace(data->cmd[i].opt[j][k])))
		k++;
	data->cmd[i].output_type = cont;
	ft_free_and_null((void **)&data->cmd[i].output);
	data->cmd[i].output = ft_substr(data->cmd[i].opt[j], k, ft_strlen(data->cmd[i].opt[j]) - k);
	if (cont == 1)
		file = open(data->cmd[i].output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		file = open(data->cmd[i].output, O_WRONLY | O_APPEND | O_CREAT, 0644);
	//if (file == -1 && errno == EACCES) sustituir todo por: minishell: a.txt: Permission denied
	close(file);
	data->cmd[i].opt = chain_delete_one(data->cmd[i].opt, j);
}

int	nose(t_data *data, int i, int j, char type)
{
	int	cont;

	cont = 0;
	while (data->cmd[i].opt[j][cont] && (data->cmd[i].opt[j][cont] == '<' || data->cmd[i].opt[j][cont] == '>' || ft_isspace(data->cmd[i].opt[j][cont])))
		cont++;
	if (!data->cmd[i].opt[j][cont])
		return (ft_putstr_fd("\033[31;1mminishell: syntax error near\
 unexpected token\n\033[0m", 2), clean_commands(data), 1);
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
	if (type == '>')
		output_parse(data, i, j, cont);
	else if (type == '<')
		input_parse(data, i, j, cont);
	return (0);
}

int	parse_redirections(t_data *data, int i)
{
	int	j;

	data->cmd[i].input = ft_strdup("");
	data->cmd[i].output = ft_strdup("");
	data->cmd[i].input_type = 0;
	data->cmd[i].output_type = 0;
	j = 0;
	while (data->cmd[i].opt[j])
	{
		if (data->cmd[i].opt[j][0] == '<')
		{
			if (nose(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
		}
		else if (data->cmd[i].opt[j][0] == '>')
		{
			if (nose(data, i, j, data->cmd[i].opt[j][0]) == 1)
				return (1);
		}
		else
			j++;
	}
	return (0);
}
