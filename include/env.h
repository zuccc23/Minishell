#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*key;  // Exemple : "PATH"
	char			*value;// Exemple : "usr/bin:/bin:..."
	struct s_env	*next; // Pointeur vers la prochaine variable
}	t_env;

//recupere l'env
char	*ft_getenv(char *str, char **envp);
char	*copy_path(const char *s1, int start);

#endif