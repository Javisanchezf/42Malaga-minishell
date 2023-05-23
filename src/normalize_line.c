#include "minishell.h"

char	*normalize_line(char *input, t_data data)
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
		while (input[i] != '\'' && input[i] != '\"' && input[i] != '$' && input[i])
			i++;
		aux = ft_substr(input, j, i - j + 1);
		line = ft_freeandjoin(line, aux);
	}
	return (line);
}