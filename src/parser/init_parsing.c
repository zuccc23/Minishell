#include "../../include/minishell.h"

//initialise l'env, le parsing des erreurs, recup des commandes/redirs
int	init_parser(t_data *shell)
{
	int	er_code;

	er_code = 0;
	er_code = expand_vars(&(*shell).token, (*shell).exec->envp, \
	(*shell).exit_status);
	if (er_code != ER_OK)
		return (er_code);
	er_code = parse_tokens((*shell).token);
	if (er_code != ER_OK)
		return (er_code);
	er_code = get_commands((*shell).token, &(*shell).command);
	if (er_code != ER_OK)
		return (er_code);
	return (er_code);
}
