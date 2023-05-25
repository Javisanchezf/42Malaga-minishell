#include "minishell.h"

// int archivo = open(nombreArchivo, O_WRONLY | O_CREAT, 0644);

char	*dollar_excepctions(char *input, char *line, int *i, t_data *data)
{
	char	*aux;
	int		j;

	(*i)++;
	if(ft_isspace(input[*i]) || !input[*i] || input[*i] == '\'' || input[*i] == '\"')
	{
		aux = ft_strjoin(line, "$");
		free(line);
		return (aux);
	}
	else if (input[*i] == '?')
	{
		(*i)++;
		aux = ft_itoa(data->lastcmd_value);
		return (ft_freeandjoin(line, aux));
	}
	else
	{
		j = *i;
		while (input[*i] && input[*i] != '$' && !ft_isspace(input[*i])  && input[*i] != '\'' && input[*i] != '\"')
			(*i)++;
		aux = ft_getenv(input, data, j, *i - j);
		return(ft_freeandjoin(line, aux));
	}
	return (line);
}

char	*normalize_line(char *input, t_data *data)
{
	int		i;
	int		j;
	char	*line;
	char	*aux;

	i = 0;
	line = ft_calloc(1, sizeof(char));
	while (input[i])
	{
		j = i;
		while (input[i] && input[i] != '$' && input[i] != '\'' && input[i] != '\"')
			i++;
		aux = ft_substr(input, j, i - j);
		line = ft_freeandjoin(line, aux);
		j = i;
		if (input[i] == '$')
			line = dollar_excepctions(input, line, &i, data);
		else if (input[i] == '\'')
		{
			forward_quotes(input, &i);
			aux = ft_substr(input, j + 1, i - j - 2);
			line = ft_freeandjoin(line, aux);
		}
		else if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
			{
				while (input[i] == '$')
					line = dollar_excepctions(input, line, &i, data);
				if (input[i] && input[i] != '\"')
				{
					i++;
					aux = ft_substr(input, i - 1, 1);
					line = ft_freeandjoin(line, aux);
				}
			}
			i++;
		}
	}
	return (line);
}

void	parse_line(char *input, t_data *data)
{
	char	**commands;
	int		i;

	commands = split_by_pipes(input, 0, 0);
	i = 0;
	data->n_commands = ft_split_size(commands);
	data->cmd = ft_calloc(data->n_commands + 1 ,sizeof(t_command)); //Proteger
	while (commands[i])
	{
		char *borrar = normalize_line(commands[i], data);
		data->cmd[i].opt = split_by_args(borrar, 0, 0, 0);
		free(borrar);
		data->cmd[i].path = ft_strdup("");
		data->cmd[i].input = ft_strdup("");
		data->cmd[i].output = ft_strdup("");
		printf("\n\tCommand Nº%d:\n---------------------------\n", i);
		ft_printf_split(data->cmd[i].opt);
		i++;
	}
	ft_free_and_null((void **)&commands);
	if (ft_strncmp(input, "exit", 5) == 0)
	{
		ft_free_and_null((void **)&input);
		clean_and_exit_success(data);
	}
	ft_free_and_null((void **)&input);
}
