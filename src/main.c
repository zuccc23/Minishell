/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/04/09 13:45:47 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/04/09 15:33:09 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
=======
/*   Created: 2025/04/09 17:58:29 by dahmane           #+#    #+#             */
/*   Updated: 2025/04/09 17:58:52 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
>>>>>>> 55873b64ec59f44c5f06e0910324a737f23da9b2
{
	char	*input;
	
	// Initialisation du shell 

	while (1)
	{
		// Affichage du prompt et recuperation de l'input
		input = readline("minishell> ");
		if (!input) // ctrl + D ou EOF
		{
			write (1, "exit\n", 5);
			break;		
		}
		// si l'input n'est pas vide on le traite
	}
	return (0);
}