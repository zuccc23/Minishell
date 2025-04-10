# 🧠 Minishell – Roadmap de Développement

## 🔁 PARSEUR

### 1. 📥 Readline & Historique
- Lire l’input de l’utilisateur via `readline()`
- Ajouter l’input à l’historique (`add_history`)
- Gérer les signaux :
  - `SIGINT` (Ctrl+C) → réafficher prompt proprement
  - `SIGQUIT` (Ctrl+\) → ignorer
  - `EOF` (Ctrl+D) → quitter proprement

### 2. 🪓 Lexer (Tokenisation)
- Découper l’input en **tokens**
- Identifier chaque token :
  - Commandes
  - Options / Arguments
  - Opérateurs : `>`, `<`, `>>`, `<<`, `|`
- Gérer les **quotes** :
  - Simples `'` → pas d’expansion
  - Doubles `"` → expansion des variables autorisée

### 3. 🧩 Parser
- Construire une **structure de commandes**
- Gérer les erreurs de syntaxe (ex: `|>`)
- Identifier les **pipelines** et structurer les nœuds de commandes

### 4. 💵 Expansion de Variables
- Remplacer les variables d’environnement : `$VAR`, `$?`
- Suivre les **règles des quotes** :
  - Pas d’expansion dans `'`
  - Expansion dans `"`

### 5. 📂 Redirections
- Identifier les redirections :
  - `>` (écraser)
  - `>>` (append)
  - `<` (lecture)
  - `<<` (heredoc)
- Vérifier les fichiers
- Créer une structure par redirection pour l’exécution

---

## ⚙️ EXÉCUTION

### 1. 🔍 Analyse de la Commande
- Déterminer si la commande est :
  - Un **builtin**
  - Une commande **externe**
- Résoudre la commande avec `PATH`
- Vérifier les **permissions**

### 2. 🔧 Gestion des Builtins
- Implémenter :
  - `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Accès direct aux variables d’environnement

### 3. 🛡️ Gestion des Signaux
- Mettre en place des `signal handlers` :
  - Avant/dans/après `fork`
- Différencier :
  - Mode interactif
  - Mode exécution (processus enfants)

### 4. 🚀 Exécution des Commandes Externes
- `fork()` pour créer un processus enfant
- `execve()` avec les bons paramètres
- Passage de l’environnement (`envp`)
- Propagation des signaux

### 5. 🔗 Gestion des Pipes
- Création de pipes `pipe()`
- Connexion entre les commandes via `dup2()`
- Fermeture des descripteurs inutilisés

### 6. 🔄 Application des Redirections
- Ouverture des fichiers
- Redirection avec `dup2()` :
  - `stdin`, `stdout`, `stderr`
- Heredoc :
  - Lire depuis `stdin` jusqu’au délimiteur
