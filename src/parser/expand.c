#include "../../include/minishell.h"

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

int	expand_vars(t_token **token)
{
	t_token	*head;

	head = *token;
	while (*token)
	{
		if ((*token)->type == TOKEN_HEREDOC)
			*token = (*token)->next->next;
		if (is_word(*token) == 1)
		{
			//replace and expand
			//secure
		}
		if (*token)
			*token = (*token)->next;
	}
	*token = head;
	return (ER_OK);
}

