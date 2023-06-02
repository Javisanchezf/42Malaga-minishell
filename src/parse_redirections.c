#include "minishell.h"

/*Se tiene que hacer en otro momento lo del heredoc porque no sustituye $USER y mas royetes*/
void	heredoc(t_data *data, int i)
{
	char	*prompt;
	char	*aux1;
	char	*aux2;

	aux1 = ft_strjoin(CYAN"heredoc \'", data->cmd[i].input);
	prompt = ft_strjoin(aux1, "\'> "DEFAULT);
	ft_free_and_null((void **)&aux1);
	aux1 = readline(prompt);
	ctrl_d(aux1, data);
	aux2 = ft_calloc(1, 1);
	while (ft_strncmp(aux1, data->cmd[i].input, ft_strlen(data->cmd->input) + 1) != 0)
	{
		aux2 = ft_freeandjoin(aux2, aux1);
		aux1 = readline(prompt);
		ctrl_d(aux1, data);
	}
	ft_free_and_null((void **)&data->cmd[i].input);
	ft_free_and_null((void **)&prompt);
	data->cmd[i].input = aux2;
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
	data->cmd[i].input = ft_substr(data->cmd[i].opt[j], k, ft_strlen(data->cmd[i].opt[j]) - k);
	if (cont == 1 || cont == 3)
	{
		file = open(data->cmd[i].output, O_RDONLY, 0644);
		close(file);
		if (cont == 3)
			data->cmd[i].input_type = 2;
		//if (file == -1 && errno == EACCES) sustituir todo por: minishell: a.txt: Permission denied
	}
	else
		heredoc(data, i);
	printf("Heredoc: %s\n", data->cmd[i].input);
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
	if ((cont > 2 && type == '>')|| (cont > 3 && type == '<'))
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
