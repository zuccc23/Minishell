#include "../../include/minishell.h"

// Initialise les variables nécessaires
void	init_cmd_var(int *pid, char **path, int *wstatus, int *exit_status)
{
	*pid = 0;
	*path = NULL;
	*wstatus = 0;
	*exit_status = 0;
}

// Valide la commande et gère les cas spéciaux
// Retourne 0 si ok, 127 si commande vide, 1 si erreur redirection
int	validate_command(t_command *cmd, t_exec *exec)
{
	if (!cmd->args || !cmd->args[0])
	{
		if (has_valid_redirections(cmd))
		{
			if (apply_redirection(cmd, exec) == -1)
				return (1);
			return (42);
		}
		return (127);
	}
	return (0);
}

//check if you need to return, returns the right number if yes
//returns 111 if no
int	check_result(int result)
{
	if (result == 42)
		return (0);
	if (result == 127)
		return (0);
	if (result != 0)
		return (result);
	else
		return (111);
}
