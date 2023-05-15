#include "../inc/minishell.h"

void	sub_dup2(int zero, int one)
{
	printf("Empiezo sub_Dup!\n");
	dup2(zero, 0);
	dup2(one, 1);
	printf("termino\n");
}

void	check_awk(t_command *cmd)
{
	if (ft_strncmp(cmd->opt[0], "awk", 3) == 0)
	{	
		if (cmd->opt[1][0] == '\'')
			cmd->opt[1] = ft_strtrim(cmd->opt[1], "'");
		else if (cmd->opt[1][0] == '"')
			cmd->opt[1] = ft_strtrim(cmd->opt[1], "\"");
	}
}
