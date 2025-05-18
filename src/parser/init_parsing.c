#include "../../include/minishell.h"

//initialise l'env, le parsing des erreurs, recup des commandes/redirs
int	init_parser(t_env **env, t_token **token, t_command **commands)
{
	int	er_code;

	er_code = 0;
	er_code = parse_tokens(*token);
	if (er_code != ER_OK) 
		return(er_code);
	er_code = expand_vars(&(*token), *env);
	if (er_code != ER_OK)
		return (er_code);
	er_code = get_commands(*token, &(*commands));
	if (er_code != ER_OK)
		return (er_code);
	return (er_code);
}
