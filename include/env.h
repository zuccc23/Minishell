#ifndef ENV_H
# define ENV_H

// value = Exemple : "PATH=usr/bin:/bin:..."
typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

//recupere l'env

int		init_env(t_env **env, char **envp);
char	*ft_getenv(char *str, t_env *env);
char	*copy_path(const char *s1, int start);
t_env	*create_env_node(char *value);

#endif