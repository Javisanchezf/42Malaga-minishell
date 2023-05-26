#include "minishell.h"

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
