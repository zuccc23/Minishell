#include "../../include/minishell.h"

//recree la fonction getenv pour recuperer le bon environnement
char	*ft_getenv(char *str, t_env *env)
{
	char	*expand;

	expand = NULL;
	while (env)
	{
		if (ft_strncmp(str, env->value, ft_strlen(str)) == 0)
		{
			expand = copy_path(env->value, ft_strlen(str) + 1);
			if (!expand)
				return (NULL);
		}
		env = env->next;
	}
	return (expand);
}

//strdup du bon chemin pour la var d'environnement
char	*copy_path(const char *s1, int start)
{
	int		i;
	int		j;
	int		size;
	char	*dest;

	i = 0;
	j = 0;
	size = ft_strlen(s1 + start);
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (i < start)
		i++;
	while (s1[i])
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

//initialise l'env a partir de l'env de base
int	init_env(t_env **env, char **envp)
{
	int		i;
	t_env	*head;

	*env = create_env_node(envp[0]);
	if (!*env)
		return (ER_MALLOC);
	head = *env;
	i = 1;
	while (envp[i])
	{
		(*env)->next = create_env_node(envp[i]);
		if (!*env)
			return (ER_MALLOC);
		*env = (*env)->next;
		i++;
	}
	*env = head;
	return (ER_OK);
}

//cree un nouveau noeud pour l'env
t_env	*create_env_node(char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->next = NULL;
	env->value = ft_strdup(value);
	if (!env->value)
	{
		free(env);
		return (NULL);
	}
	return (env);
}
