#include "minishell.h"

int	is_separator_char(char c)
{
	return (c == '<' || c == '>' || c == '\'' || \
	c == '\"' || ft_isspace(c) || c == 0);
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
