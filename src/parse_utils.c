#include "minishell.h"

int	is_separator_char(char c)
{
	return (c == '<' || c == '>' || ft_isspace(c) || c == 0);
}

char	*ft_getenv(char *env, t_data *data)
{
	int	size;
	int	i;

	i = -1;
	size = ft_strlen(env);
	while (++i < data->n_envs)
		if (ft_strlen(data->env[i].value) == size)
			if (ft_strncmp(env, data->env[i].value, size) == 0)
				break ;
	if (i < data->n_envs)
		return (ft_strdup(data->env[i].variable));
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
