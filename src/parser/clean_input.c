#include "../../include/minishell.h"

//fonction pour nettoyer et recuperer l'input
char	**clean(char *input)
{
	int	i = 0; //input[i]
	int	j = 0; //strs[a][j] <-
	int	a = 0;//strs ->[a][j]
	int		expand = 0;
	char	**strs;

	if (!input)
		return (NULL);
	//allocatiuons de memoire aleatoire pr tester
	strs = malloc(sizeof(char *) *4);
	strs[0] = malloc(sizeof(char) * 100);
	strs[1] = malloc(sizeof(char) * 100);
	strs[2] = malloc(sizeof(char) * 100);
	strs[3] = NULL;

	while (input[i]) // tant que l'input n'a pas fini d'etre lu, continuer la boucle
	{
		j = 0; //strs[a][j] <-remettre cet indice a 0 car en debut de boucle
		while (is_space(input[i]) == 1) //while espace, avance -> enleve les espaces inutiles
			i++;
		while (is_space(input[i]) == 0) // boucle principale : while pas d'espace, avance -> pour ne pas recuperer l'argument d'apres
		{
			if (is_double_quotes(input[i]) == 1) // si on trouve des " "
			{
				i++; //avance sur la case suivante (l'interieur des " ")
				while (is_double_quotes(input[i]) == 0) // on recupere jusqua la fin des " "
				{
					if (is_expandable(input[i], input[i+1]) == 1) // si on trouve un $ ds des "", alors c expandable
						expand = 1;
					strs[a][j] = input[i]; //copie les caracteres a linterieur des " "
					i++;
					j++;
				}
				i++; //on est arrive sur le 2e ", alors on i++ pour etre sur le caractere suivant
			}
			if (is_single_quotes(input[i]) == 1) // si on trouve des ' '
			{
				i++;//avance sur la case suivante (l'interieur des ' ')
				while (is_single_quotes(input[i]) == 0) // on recupere jusqua la fin des ' '
				{
					strs[a][j] = input[i]; //copie les caracteres a linterieur des ' '
					i++;
					j++;
				}
				i++;//on est arrive sur le 2e ', alors on i++ pour etre sur le caractere suivant
			}
			while (is_ok_word(input[i]) == 1) // si on trouve un mot sans rien(mot= pas des "", pas des '', pas un espace)
			{
				if (is_expandable(input[i], input[i+1]) == 1) //si on trouve un $ ds un mot sans '', alors c expandable
					expand = 1;
				strs[a][j] = input[i]; //copie les caracteres
					i++;
					j++;
			}
		}
		strs[a][j] = '\0'; //fin de la boucle, on termine la string
		ft_printf("expand %d: %d\n", a, expand); //pr voir l'iindice de l'expandable
		a++; //on va sur la string suivante
		expand = 0; //reinitialise l'indice de l'expand
		if (input[i]) //g oublie a quoi ca sert peut etre c inutile
			i++;
	}
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

int	is_space(char c)
{
	if (c == '\0')
		return (-1);
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	is_double_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '"')
		return (1);
	else
		return (0);
}

int	is_expandable(char c, char next_c)
{
	if (c == '\0')
		return (-1);
	if (c == '$' && next_c != '\0')
		return (1);
	else
		return (0);
}

int	is_single_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '\'')
		return (1);
	else
		return (0);
}

int	is_ok_word(char c)
{
	if (c == '\0')
		return (-1);
	if (c == ' ')
		return (0);
	if (c == '"')
		return (0);
	if (c == '\'')
		return (0);
	else
		return (1);
}
