Roadmap Très Détaillée pour Minishell
Phase 1 : Analyse du Sujet et Planification
Relire attentivement le sujet (subject.md) pour identifier toutes les exigences :
Affichage du prompt et historique.
Recherche d'exécutables (via PATH ou chemin absolu/relatif).
Gestion des redirections (<, >, <<, >>).
Gestion des pipes afin de chaîner les commandes.
Expansion des variables ($VAR, $?).
Implémentation des builtins (echo -n, cd, pwd, export, unset, env, exit).
Gestion des signaux (ctrl-C, ctrl-D, ctrl-\).
Définir les contraintes de développement (respect de la Norme 42, Makefile avec -Wall -Wextra -Werror, etc.).
Répartition initiale :
Travail en duo sur le parsing.
Collaboration sur le module d'exécution après validation du parsing.
Phase 2 : Conception de l'Architecture Globale et Modulaire
Décomposer le projet en modules :
Module Lexer (analyse lexicale)
Module Parser (analyse syntaxique et construction de la structure de commande)
Module Exécution (gestion des forks, exec, redirections, pipes)
Module Builtins (implémentation des commandes internes)
Module Signaux (gestion des interruptions et comportements interactifs)
Concevoir les structures de données essentielles :
Structure Token : { type (commande, argument, redirection, pipe), valeur }
Structure Commande : { nom de la commande, liste d’arguments, redirections associées, lien avec d’éventuels pipes }
Créer un diagramme ou des schémas simples pour visualiser l'interaction entre ces modules.
Phase 3 : Développement du Lexer (Partie Parsing – Cas Actuel)
Objectif : Décomposer la ligne de commande en une suite de tokens utilisables par le parser.
Étapes détaillées du Lexer :
Lecture de la chaîne d'entrée :
Parcourir la ligne reçue et gérer la séparation par espaces (tout en ignorant les espaces à l'intérieur des quotes).
Extraction des tokens de base :
Identifier les commandes et arguments simples.
Gestion des quotes :
Traitement des quotes simples (désactiver toute interprétation).
Traitement des quotes doubles (permettre l'expansion des variables).
Identification des opérateurs spéciaux :
Identifier et isoler les redirections (<, >, <<, >>) et le pipe (|).
Détection et report d'erreurs :
S’assurer de la fermeture correcte des quotes.
Gérer les cas d’entrée invalide (exemple : des opérateurs successifs ou mal placés).
Rédaction et exécution de tests unitaires :
Écrire des scénarios tests pour vérifier que le lexer fonctionne sur des commandes simples (ex : ls -l), complexes (ex : echo "coucou" | grep cou) et les cas d’erreurs.
--
Phase 4 : Développement du Parser (Partie Parsing – Suite à la Collaboration)
Objectif : Transformer la liste de tokens en une structure de commande exploitable par le module d’exécution.
Sous-étapes du Parser :
Conception de la structure de commande :
Définir précisément la structure (commande, arguments, redirections, et pipes).
Regroupement des tokens :
Convertir la liste de tokens en commandes distinctes. Par exemple, un token « | » marque la fin d’une commande et le début de la suivante.
Association des redirections à leur commande :
Lier chaque redirection (ex : > output.txt) à la commande concernée.
Gestion de l’expansion des variables dans le contexte des quotes doubles :
Intégrer une fonction d’expansion (remplacement des variables par leur valeur).
Validation par tests unitaires :
Tester avec des commandes simples et des chaînes complexes (multi-commandes, redirections imbriquées, etc.).
Réunion de synchronisation en duo :
Réviser ensemble le fonctionnement du parser pour s’assurer de sa robustesse avant de passer à l’exécution.
Phase 5 : Développement du Module d’Exécution (À réaliser ensemble après le parsing)
Objectif : Exécuter les commandes extraites et gérées par le parser via des appels système.
Sous-étapes du Module d’Exécution :
Préparation à l’exécution :
Initialiser l’environnement (copie de l’environnement, préparation des variables, etc.).
Exécution des commandes simples :
Utiliser fork et execve pour lancer des programmes.
Gérer la récupération des statuts avec wait/waitpid.
Gestion des redirections :
Implémenter l’ouverture/fermeture des fichiers et rediriger les entrées/sorties (dup2).
Implémenter le mode heredoc (<<) en lecture jusqu’au délimiteur.
Gestion des pipes :
Créer et connecter des tuyaux entre plusieurs commandes.
Gérer la fermeture correcte des file descriptors dans chaque processus.
Implémentation des builtins :
Développer en interne les fonctions de echo, cd, pwd, export, unset, env, exit.
Décider pour chaque builtin s’il faut éviter un fork (comme cd) pour modifier l’état du shell.
Intégration et tests fonctionnels :
Tester des scénarios réels : commande simple, chaînes avec pipes, redirections multiples.
S’assurer de la robustesse en cas d’erreur d’exécution.
Phase 6 : Mise en Place de la Gestion des Signaux et du Comportement Interactif
Objectif : Faire en sorte que le shell réagisse comme Bash en mode interactif.
Sous-étapes de la gestion des signaux :
Implémenter une variable globale simple pour stocker le numéro du signal reçu.
Configurer les gestionnaires de signaux via sigaction :
Ctrl-C : interrompre la commande en cours et afficher un nouveau prompt.
Ctrl-D : considérer comme une demande de sortie du shell.
Ctrl-\ : ignorer le signal (ne rien faire).
Tester l’impact des signaux sur les processus enfants et le shell lui-même.
Vérifier que la gestion des signaux ne perturbe pas la mise en place des redirections/pipes en cours d’exécution.
--
Phase 7 : Intégration Globale et Tests Combinés
Objectif : Assembler tous les modules (parsing, exécution, signaux) et tester le shell dans son ensemble.
Étapes d’intégration :
Fusionner le Lexer et le Parser pour produire la structure de commandes complète.
Associer la structure de commande à l’exécution des commandes avec leurs redirections et pipes.
Vérifier la cohérence et l'interaction entre les modules (tests unitaires et tests d’intégration).
Réaliser des tests en mode interactif avec divers scénarios :
Commandes simples, chaînées, redirigées, avec utilisation de builtins.
Tests de robustesse face aux entrées incorrectes.
--
Phase 8 : Finalisation et Soumission
Objectif : Préparer la version finale du projet et les documents nécessaires pour la livraison.
Actions finales :
Création d’un Makefile conforme aux exigences (règles : $(NAME), all, clean, fclean, re, et les flags -Wall -Wextra -Werror).
Rédaction du README.md :
Explication de l’architecture.
Instructions de compilation et d’utilisation.
Description des choix techniques et répartition en duo.
Revue de code en binôme pour s’assurer de la qualité, de la conformité à la Norme et de l’absence de fuites mémoire.
Tests finaux et dernier passage en revue.
Soumission sur le dépôt Git conformément aux règles de l’étude.
Répartition dans le Travail en Duo
Parsing (Lexer et Parser) :
→ Collaboration totale, échanges constants pour définir la structure des tokens et la création de la commande.
→ Sessions de revue de code pour valider les tests unitaires.
Exécution & Gestion des Signaux :
→ Après validation du parsing, nous travaillerons ensemble sur l’exécution des commandes, la gestion des redirections et des pipes.
→ Répartition des builtins et implémentation des gestionnaires de signaux en fonction de nos expertises.
