#ifndef ENV_H
# define ENV_H

// value = Exemple : "PATH=usr/bin:/bin:..."
typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

//recupere l'env

char	*ft_getenv(char *str, char **env);
char	*copy_path(const char *s1, int start);

#endif