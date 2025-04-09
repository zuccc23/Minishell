#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;  // Exemple : "PATH"
	char			*value;// Exemple : "usr/bin:/bin:..."
	struct s_env	*next; // Pointeur vers la prochaine variable
}	t_env;

#endif