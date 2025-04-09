/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdodevsk <mdodevsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:06:00 by mdodevsk          #+#    #+#             */
/*   Updated: 2025/04/09 18:06:25 by mdodevsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av, char **envp)
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