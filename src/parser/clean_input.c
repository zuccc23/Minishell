#include "../../include/minishell.h"

char	**clean(char *s)
{
	int	i = 0;
	int	j = 0;
	int	a = 0;
	// int	b = 1;
	// int	c = 2;
	int		expand = 0;
	char	**strs;
	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) *4);
	strs[0] = malloc(sizeof(char) * 100);
	strs[1] = malloc(sizeof(char) * 100);
	strs[2] = malloc(sizeof(char) * 100);
	strs[3] = NULL;

	while (s[i] && s[i] != ' ')
	{
		if (s[i] && s[i] == '"')
		{
			i++;
			while (s[i] && s[i] != '"')
			{
				if (s[i] == '$' && s[i+1])
				{
					expand = 1;
				}
				strs[a][j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		if (s[i] && s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
			{

				strs[a][j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		while (s[i] && s[i] != '\'' && s[i] != '"' && s[i] != ' ')
		{
			if (s[i] == '$' && s[i+1])
			{
				expand = 1;
			}
			strs[a][j] = s[i];
				i++;
				j++;
		}
	}
	strs[a][j] = '\0';
	i++;
	ft_printf("expand:%d\n", expand);
	return (strs);
}


void    strs_print(char **strs)
{
        int     i;
        int     j;

        i = 0;
        j = 0;
        while (strs[i] != NULL)
        {
                while (strs[i][j])
                {
                        write (1, &strs[i][j], 1);
                        j++;
                }
                write (1, "\n", 1);
                i++;
                j = 0;
        }
        if (strs[i] == NULL)
                write (1, "null", 4);
}