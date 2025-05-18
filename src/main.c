#include "../include/minishell.h"

//creating a node with proper values
t_token	*new_token(char *value1, char *value2, t_token_type type, int expandable, int expandable2) // fonction temporaire 
{
	t_token *new = NULL;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->word = NULL;
	new->next = NULL;

	new->type = type;

	if (value1 && value2)
	{
		new->word = malloc(sizeof(t_word));
		if (!new->word)
			return (NULL);
		new->word->value = ft_strdup(value1);
		if (!new->word->value)
			return (NULL);

		new->word->next = malloc(sizeof(t_word));
		if (!new->word->next)
			return (NULL);
		new->word->next->value = ft_strdup(value2);
		if (!new->word->next->value)
			return (NULL);

		new->word->expandable = expandable;
		new->word->next->expandable = expandable2;

		new->word->next->next = NULL;
	}

	return (new);
}

//creating a temporary linked list of tokens
t_token	*temp_tokens(void) // fonction temporaire 
{
	t_token *head = NULL;
	t_token *token = NULL;

	token = new_token("l", "s", TOKEN_WORD, 0, 0);
	if (!token)
		return (NULL);
	head = token;

	token->next = new_token("$USER", "$PATHf", TOKEN_WORD, 1, 1);
	if (!token->next)
		return (NULL);
	token = token->next;

	token->next = new_token(NULL, NULL, TOKEN_REDIRECT_OUT, 0, 0);
	if (!token->next)
		return (NULL);
	token = token->next;

	token->next = new_token("$USER", "$_", TOKEN_WORD, 1, 1);
	if (!token->next)
		return (NULL);
	token = token->next;

	token = head;
	return (token);
}

//print the token list in a single line
void	print_line_tokens(t_token *token) // fonction temporaire 
{
	ft_printf("----------------------------\n");
	while (token)
	{
		if (token->word)
		{
			ft_printf("%s", token->word->value);
			if (token->word->next)
				ft_printf("%s", token->word->next->value);
			ft_printf(" ");
		}
		if (token->type == TOKEN_HEREDOC)
			ft_printf("<< ");
		if (token->type == TOKEN_REDIRECT_OUT)
			ft_printf("> ");
		if (token->type == TOKEN_REDIRECT_IN)
			ft_printf("< ");
		if (token->type == TOKEN_REDIRECT_APPEND)
			ft_printf(">> ");
		token = token->next;
	}
	ft_printf("\n");
	ft_printf("----------------------------\n");
}

//print the token list
void	print_tokens(t_token *token) // fonction temporaire 
{
	while (token)
	{
		ft_printf("%s ", token->word->value);
		if (token->type == 0)
			ft_printf("        =word ");
		else 
			ft_printf("       =operator ");
		ft_printf("=expandable:%d\n", token->expandable);
		token = token->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	// char	*input;
	(void)ac;
	(void)av;
	(void)envp;
	
	// Signaux 
	// handle_signal();

	// Initialisation du shell

	// while (1)
	// {
	// 	// Affichage du prompt et recuperation de l'input
	// 	input = readline("minishell> ");
	// 	if (!input) // ctrl + D ou EOF
	// 	{
	// 		write (1, "exit\n", 5);
	// 		break;
	// 	}
	// 	// si l'input n'est pas vide on le traite
	// 	if (*input)
	// 	{
	// 		add_history(input);
	// 	}
	// }

	// INIT ENV
	int			er_code = 0;
	t_env		*env = NULL;

	er_code = init_env(&env, envp);
	if (er_code != ER_OK)
		return (er_code);

	//CREER DES TOKENS TEMPORAIRES POUR LES TESTS
	t_token		*token = NULL;
	token = temp_tokens();
	if (!token)
		return (1);
	print_line_tokens(token);

	// INIT PARSING
	t_command	*command = NULL;

	er_code = init_parser(&env, &token, &command);
	if (er_code != ER_OK)
		return (er_code);

	ft_printf("command: %s\n", command->args[0]);
	ft_printf("command: %s\n", command->args[1]);
	ft_printf("redirect type: %d\n", command->redirections->type);
	ft_printf("redirect file: %s\n", command->redirections->file);

	// CLEANING AND FREEING
	free_commands(command);
	free_tokens(token);
	free_env(env);
	return (0);
}
