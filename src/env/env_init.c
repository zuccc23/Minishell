#include "../../include/minishell.h"

//g refait la fonction getenv pour recupere le bon environnement
char	*ft_getenv(char *str, char **envp)
{
	int		i;
	char	*expand;

	i = 0;
	expand = NULL;
	while (envp[i])
	{
		if (ft_strncmp(str, envp[i], ft_strlen(str)) == 0)
		{
			expand = copy_path(envp[i], ft_strlen(str) + 1);
			if (!expand)
				return (NULL);
		}
		i++;
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
