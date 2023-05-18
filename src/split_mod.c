#include "minishell.h"

int	is_separator_char(char c)
{
	return (c == '<' || c == '>' || c == '\'' || c == '\"' || ft_isspace(c) || c == 0);
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

static int	ft_size_split_mod(char *input)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			forward_quotes(input, &i);
			n++;
		}
		if (input[i] == '<' || input[i] == '>')
		{
			forward_operators(input, &i);
			n++;
		}
		if (!is_separator_char(input[i]))
		{
			n++;
			while (!is_separator_char(input[i]))
				i++;
		}
	}
	return (n);
}

static char	**ft_splitfree(char **split, int n)
{
	while (n-- > 0)
		free(split[n]);
	free(split);
	return (0);
}

char	**ft_split_mod(char *input)
{
	char	**split;
	int		i;
	int		j;
	int		n;

	i = 0;
	n = -1;
	split = (char **)ft_calloc((ft_size_split_mod(input) + 1), sizeof(char *));
	if (!split || !input)
		return (0);
	while (input[i] && ++n < ft_size_split_mod(input))
	{
		while (ft_isspace(input[i]))
			i++;
		j = i;
		if (input[i] == '\'' || input[i] == '\"')
			forward_quotes(input, &i);
		else if (input[i] == '<' || input[i] == '>')
			forward_operators(input, &i);
		else if (!is_separator_char(input[i]))
			while (!is_separator_char(input[i]))
				i++;
		split[n] = ft_substr(input, j, i - j);
		if (!split[n])
			return (ft_splitfree(split, n));
	}
	return (split);
}
