#include "../../include/minishell.h"

//fonction pour nettoyer et recuperer l'input
// char	**clean(char *input)
// {
// 	int	i = 0; //input[i]
// 	int	j = 0; //str[a][j] <-
// 	int	a = 0;//str ->[a][j]
// 	int		expand = 0;
// 	char	**str;

// 	int taille = get_cleaned_word_length(input);
// 	printf("\nLa taille est de %d\n", taille);


// 	if (!input)
// 		return (NULL);
// 	//allocatiuons de memoire aleatoire pr tester
// 	str = malloc(sizeof(char *) *4);
// 	str[0] = malloc(sizeof(char) * 100);
// 	str[1] = malloc(sizeof(char) * 100);
// 	str[2] = malloc(sizeof(char) * 100);
// 	str[3] = NULL;

// 	while (input[i]) // tant que l'input n'a pas fini d'etre lu, continuer la boucle
// 	{
// 		j = 0; //str[a][j] <-remettre cet indice a 0 car en debut de boucle
// 		while (is_space(input[i]) == 1) //while espace, avance -> enleve les espaces inutiles
// 			i++;
// 		while (is_space(input[i]) == 0) // boucle principale : while pas d'espace, avance -> pour ne pas recuperer l'argument d'apres
// 		{
// 			if (is_double_quotes(input[i]) == 1) // si on trouve des " "
// 			{
// 				i++; //avance sur la case suivante (l'interieur des " ")
// 				while (is_double_quotes(input[i]) == 0) // on recupere jusqua la fin des " "
// 				{
// 					if (is_expandable(input[i], input[i+1]) == 1) // si on trouve un $ ds des "", alors c expandable
// 						expand = 1;
// 					str[a][j] = input[i]; //copie les caracteres a linterieur des " "
// 					i++;
// 					j++;
// 				}
// 				i++; //on est arrive sur le 2e ", alors on i++ pour etre sur le caractere suivant
// 			}
// 			if (is_single_quotes(input[i]) == 1) // si on trouve des ' '
// 			{
// 				i++;//avance sur la case suivante (l'interieur des ' ')
// 				while (is_single_quotes(input[i]) == 0) // on recupere jusqua la fin des ' '
// 				{
// 					str[a][j] = input[i]; //copie les caracteres a linterieur des ' '
// 					i++;
// 					j++;
// 				}
// 				i++;//on est arrive sur le 2e ', alors on i++ pour etre sur le caractere suivant
// 			}
// 			while (is_ok_word(input[i]) == 1) // si on trouve un mot sans rien(mot= pas des "", pas des '', pas un espace)
// 			{
// 				if (is_expandable(input[i], input[i+1]) == 1) //si on trouve un $ ds un mot sans '', alors c expandable
// 					expand = 1;
// 				str[a][j] = input[i]; //copie les caracteres
// 					i++;
// 					j++;
// 			}
// 		}
// 		str[a][j] = '\0'; //fin de la boucle, on termine la string
// 		ft_printf("expand %d: %d\n", a, expand); //pr voir l'iindice de l'expandable
// 		a++; //on va sur la string suivante
// 		expand = 0; //reinitialise l'indice de l'expand
// 		if (input[i]) //g oublie a quoi ca sert peut etre c inutile
// 			i++;
// 	}
// 	return (str);
// }

static int	is_space(char c)
{
	if (c == '\0')
		return (-1);
	if (c == ' ')
		return (1);
	else
		return (0);
}

static int	is_double_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '"')
		return (1);
	else
		return (0);
}

static int	is_expandable(char c, char next_c)
{
	if (c == '\0')
		return (-1);
	if (c == '$' && next_c != '\0')
		return (1);
	else
		return (0);
}

static int	is_single_quotes(char c)
{
	if (c == '\0')
		return (-1);
	if (c == '\'')
		return (1);
	else
		return (0);
}

static int	is_ok_word(char c)
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

static void	check_double_quotes(char *str, int *i, int *count)
{
	if (is_double_quotes(str[*i]) == 1)
	{
		(*i)++;
		while (is_double_quotes(str[*i]) == 0)
		{
			(*count)++;
			(*i)++;
		}
		(*i)++;
	}
}

static void	check_single_quotes(char *str, int *i, int *count)
{
	if (is_single_quotes(str[*i]) == 1)
	{
		(*i)++;
		while (is_single_quotes(str[*i]) == 0)
		{
			(*count)++;
			(*i)++;
		}
		(*i)++;
	}
}

int	get_cleaned_word_length(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		check_double_quotes(input, &i, &count);
		check_single_quotes(input, &i, &count);
		while (is_ok_word(input[i]) == 1)
		{
			count++;
			i++;
		}
	}
	return (count);
}
