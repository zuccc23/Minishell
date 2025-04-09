Minishell
Description
Minishell est un projet en C qui consiste à créer un shell simplifié, inspiré de Bash. Ce projet te permettra de maîtriser la gestion des processus, des descripteurs de fichiers et la manipulation des signaux.
Fonctionnalités Attenues
Affichage et Historique
Afficher un prompt pour chaque nouvelle commande.
Gérer un historique des commandes.
Exécution des Commandes
Rechercher et lancer des exécutables en utilisant la variable d'environnement PATH ou via des chemins relatifs/absolus.
Redirections
< pour rediriger l'entrée.
> pour rediriger la sortie.
<< pour le mode heredoc (lecture jusqu'à un délimiteur).
>> pour la sortie en mode append.
Pipes
Permettre la connexion de la sortie d'une commande à l'entrée d'une autre.
Expansion des Variables
Gérer l'expansion des variables d'environnement via le symbole $.
Gérer spécifiquement $? pour afficher l'état de sortie de la dernière commande.
Gestion des Signaux
Implémenter une gestion similaire à Bash pour les signaux, notamment :
Ctrl-C : affiche un nouveau prompt sur une nouvelle ligne.
Ctrl-D : quitte le shell.
Ctrl-\ : ne fait rien.
Builtins
Implémenter les commandes internes suivantes :
echo (avec option -n)
cd
pwd
export
unset
env
exit
Contraintes Techniques
Le projet doit être écrit en C et conforme aux normes de 42.
Le Makefile doit respecter les règles : $(NAME), all, clean, fclean, re et compiler avec les flags -Wall -Wextra -Werror.
La gestion de la mémoire doit être rigoureuse (pas de fuites).
Seule une variable globale est autorisée pour indiquer les signaux reçus (stockant uniquement le numéro du signal).
Ce résumé couvre les points clés à implémenter et pourra servir de référence rapide pour ton projet Minishell.