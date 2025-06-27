#include "../../include/minishell.h"

//initialise l'env, le parsing des erreurs, recup des commandes/redirs
int	init_parser(t_data *shell)
{
	int	er_code;

	er_code = 0;
	er_code = expand_vars(&shell->token, shell->exec->envp, \
	shell->exit_status);
	if (er_code != ER_OK)
		return (er_code);
	er_code = parse_tokens(shell->token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = get_commands(shell->token, &shell->command);
	if (er_code != ER_OK)
		return (er_code);
	er_code = is_minishell(*shell);
	return (er_code);
}

//hehe
int	is_minishell(t_data shell)
{
	t_command	*head;
	int			i;

	i = 0;
	head = shell.command;
	while (shell.command)
	{
		if (shell.command && shell.command->args && shell.command->args[0])
		{
			if (shell.command->next != NULL)
				i++;
			if (is_same_word(shell.command->args[0], "./minishell") && i != 0)
			{
				print_symbol();
				free_commands(head);
				return (1);
			}
		}
		i++;
		shell.command = shell.command->next;
	}
	shell.command = head;
	return (ER_OK);
}

// return 1 if same word, 0 if not
int	is_same_word(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 == 0 || len2 == 0)
		return (0);
	if (len1 != len2)
		return (0);
	if (ft_strncmp(str1, str2, len1) == 0)
		return (1);
	return (0);
}

void	print_symbol(void)
{
    printf("....................../´¯/) \n");
    printf("....................,/¯../  \n");
    printf(".................../..../   \n");
    printf("............./´¯/'...'/´¯¯`·¸ \n");
    printf("........../'/.../..../......./¨¯\\ \n");
    printf("........('(...´...´.... ¯~/'...') \n");
    printf(".........\\.................'...../ \n");
    printf("..........''...\\.......... _.·´  \n");
    printf("............\\..............(     \n");
    printf("..............\\.............\\... \n");
}
