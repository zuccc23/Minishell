🔧 Description des Modules
2.1. Module Lexer (lexer/)

Responsabilité :
Analyser la ligne de commande brute (input utilisateur) et la transformer en une liste de tokens : commandes, arguments, redirections, pipes, etc. C’est l’analyse lexicale.

Fonctions principales :

    tokenize(char *input)
    ➤ Transforme l’entrée utilisateur en une liste chaînée de tokens (t_token). Ignore les espaces hors quotes.

    handle_quotes(char *input, int *i)
    ➤ Gère les quotes simples ' (aucune expansion/interprétation) et doubles " (autorise l’expansion de variables). Avance correctement l’index.

    handle_operators(char *input, int *i)
    ➤ Identifie les opérateurs spéciaux : <, >, <<, >>, | et les ajoute à la liste des tokens.

    add_token(char *value, t_token_type type)
    ➤ Alloue et ajoute un nouveau token à la liste.

    is_operator(char *str)
    ➤ Vérifie si une chaîne correspond à un opérateur.

2.2. Module Parser (parser/)

Responsabilité :
Transformer la liste de tokens en une structure de commandes exploitable par le shell. Gère aussi l’expansion de variables, l’organisation des pipes, et les redirections.

Fonctions principales :

    parse_tokens(t_token *tokens)
    ➤ Parcourt les tokens et crée une liste de structures t_command, chaque t_command représentant une commande séparée (gérée par |).

    expand_variables(t_command *cmd, char **envp)
    ➤ Remplace les occurrences de $VAR par leur valeur d’environnement. Gère aussi $?.

    associate_redirections(t_command *cmd, t_token *tokens)
    ➤ Associe les redirections (>, <, >>, <<) à la bonne commande.

    build_command_args(t_token *tokens)
    ➤ Construit le tableau argv[] pour chaque commande, en excluant les opérateurs.

    check_syntax(t_token *tokens)
    ➤ Détecte les erreurs de syntaxe : pipe en début ou fin, redirections sans cible, quotes non fermées…

2.3. Module Executor (executor/)

Responsabilité :
Exécuter les commandes, qu'elles soient simples, redirigées ou chaînées via pipe. Utilise fork, execve, dup2, etc. Gère les redirections, le heredoc et les builtins.

Fonctions principales :

    execute(t_command *cmd_list, char **envp)
    ➤ Lance l’exécution des commandes, gère les forks, redirections et pipelines.

    setup_redirections(t_command *cmd)
    ➤ Ouvre les fichiers et applique les redirections via dup2.

    handle_pipes(t_command *cmds)
    ➤ Connecte les stdin/stdout entre plusieurs processus via pipe.

    handle_heredoc(t_command *cmd)
    ➤ Gère le mode << : création temporaire d’un fichier contenant l’entrée jusqu’au délimiteur.

    resolve_path(char *cmd, char **envp)
    ➤ Trouve le chemin absolu de la commande via la variable PATH.

2.4. Module Builtins (builtins/)

Responsabilité :
Implémenter les commandes internes du shell, exécutables sans appel à execve.

Fonctions principales :

    ft_echo(char **args)

    ft_cd(char **args, t_env *env)

    ft_pwd(void)

    ft_export(char **args, t_env *env)

    ft_unset(char **args, t_env *env)

    ft_env(t_env *env)

    ft_exit(char **args)

    Certaines sont exécutées dans le processus parent (ex: cd, exit) car elles doivent modifier le shell lui-même.

2.5. Module Env (env/)

Responsabilité :
Gérer la copie de l’environnement (envp) et son utilisation (export, unset, etc.).

Fonctions principales :

    init_env(char **envp)
    ➤ Crée une copie propre de l’environnement sous forme de liste chaînée.

    get_env_value(t_env *env, char *key)
    ➤ Retourne la valeur d’une variable d’environnement.

    set_env(t_env **env, char *key, char *value)
    ➤ Ajoute ou modifie une variable d’environnement.

    unset_env(t_env **env, char *key)
    ➤ Supprime une variable.

    env_to_array(t_env *env)
    ➤ Convertit la liste en tableau (char **) pour execve.

2.6. Module Signals (signals/)

Responsabilité :
Gérer les interruptions clavier (CTRL-C, CTRL-) et les signaux système pour un comportement interactif naturel.

Fonctions principales :

    setup_signals_interactive()
    ➤ Signalisation dans la boucle principale du shell (parent uniquement).

    setup_signals_child()
    ➤ Réinitialise les signaux dans les processus enfants.

    sigint_handler(int sig)
    ➤ Handler pour SIGINT (CTRL-C).

    sigquit_handler(int sig)
    ➤ Handler pour SIGQUIT (CTRL-).

2.7. Module Utils (utils/)

Responsabilité :
Fournir des fonctions génériques utilisées dans plusieurs modules : chaînes, erreurs, mémoire, etc.

Fonctions principales :

    ft_split_quoted() : version améliorée de split respectant les quotes.

    free_tokens() / free_commands() : libère les structures dynamiques.

    print_error(char *msg) : affichage coloré/log en cas d’erreur.

    strjoin_free(), strdup_safe(), etc. : helpers robustes pour manipuler les chaînes.