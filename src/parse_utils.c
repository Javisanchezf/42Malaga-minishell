#include "minishell.h"

int	is_separator_char(char c)
{
	return (c == '<' || c == '>' || ft_isspace(c) || c == 0);
}

char	*ft_getenv(char *env, t_data *data, int start, int size)
{
	int		i;
	char	*aux;

	i = 0;
	while (data->env[i])
	{
		aux = ft_strchr(data->env[i], '=') + 1;
		if (size == aux - data->env[i] - 1)
			if (ft_strncmp(&env[start], data->env[i], size - 2) == 0)
				return (ft_strdup(aux));
		i++;
	}
	return (ft_strdup(""));
}

void	forward_quotes(char *input, int *i)
{
	char	aux;

	aux = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != aux)
		(*i)++;
	(*i)++;
}

void	forward_operators(char *input, int *i)
{
	while (input[*i] && (input[*i] == '<' || input[*i] == '>'))
		(*i)++;
	while (ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '\"')
		forward_quotes(input, i);
	else
		while (!is_separator_char(input[*i]))
			(*i)++;
}
