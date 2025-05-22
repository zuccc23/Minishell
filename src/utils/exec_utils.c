#include "../../include/minishell.h"

//free paths variables
char	*free_paths(char ***paths, char ***j_paths, char **cmd_tmp)
{
	if (*paths)
		free_strs(*paths);
	if (*j_paths)
		free_strs(*j_paths);
	if (*cmd_tmp)
		free(*cmd_tmp);
	return (NULL);
}
