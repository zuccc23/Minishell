#!/bin/bash

# Script de test automatisé pour minishell
# Usage: ./test_minishell.sh [path_to_minishell]

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Variables globales
MINISHELL_NAME=${1:-"minishell"}
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
TEST_DIR="minishell_tests"
TIMEOUT=5

# Chemin absolu vers minishell (avant de changer de dossier)
MINISHELL_PATH="$(pwd)/$MINISHELL_NAME"

# Créer le dossier de test
mkdir -p "$TEST_DIR"
cd "$TEST_DIR"

# Fonction d'affichage
print_header() {
    echo -e "${BLUE}================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}================================${NC}"
}

print_test() {
    echo -e "${YELLOW}Testing:${NC} $1"
}

print_pass() {
    echo -e "${GREEN}✓ PASS${NC}"
    ((PASSED_TESTS++))
}

print_fail() {
    echo -e "${RED}✗ FAIL${NC}"
    echo -e "${RED}Command: $1${NC}"
    echo -e "${RED}Expected:${NC}"
    cat bash_output.tmp 2>/dev/null | head -5
    echo -e "${RED}Got:${NC}"
    cat minishell_output.tmp 2>/dev/null | head -5
    echo -e "${RED}---${NC}"
    ((FAILED_TESTS++))
}

# Fonction de test principal
run_test() {
    local cmd="$1"
    local test_name="$2"

    ((TOTAL_TESTS++))

    if [ -n "$test_name" ]; then
        print_test "$test_name"
    else
        print_test "$cmd"
    fi

    # Nettoyer les fichiers de sortie précédents
    rm -f bash_output.tmp minishell_output.tmp minishell_output_raw.tmp bash_err.tmp minishell_err.tmp

    # Exécuter avec bash
    timeout $TIMEOUT bash -c "$cmd" > bash_output.tmp 2> bash_err.tmp
    bash_exit=$?

    # Exécuter avec minishell
    timeout $TIMEOUT bash -c "echo '$cmd' | $MINISHELL_PATH" > minishell_output_raw.tmp 2> minishell_err.tmp
    minishell_exit=$?

    # Enlever le prompt "minishell> " et les lignes vides
    grep -v "^minishell>" minishell_output_raw.tmp | grep -v "^$" > minishell_output.tmp 2>/dev/null || touch minishell_output.tmp

    # Comparer les sorties (on ignore les codes de sortie pour l'instant car timeout peut les modifier)
    if diff bash_output.tmp minishell_output.tmp >/dev/null 2>&1; then
        print_pass
    else
        print_fail "$cmd"
    fi
}

# Debug: afficher le chemin et lister les fichiers
echo -e "${BLUE}Chemin du minishell: $MINISHELL_PATH${NC}"
echo -e "${BLUE}Fichiers dans le répertoire parent:${NC}"
ls -la ../ | grep -E "(minishell|\.out)"

# Test si minishell existe
if [ ! -f "$MINISHELL_PATH" ]; then
    echo -e "${RED}Erreur: $MINISHELL_PATH n'existe pas${NC}"
    echo -e "${YELLOW}Fichiers exécutables trouvés dans le répertoire parent:${NC}"
    find ../ -maxdepth 1 -type f -executable -name "*minishell*" 2>/dev/null
    find ../ -maxdepth 1 -type f -name "*.out" 2>/dev/null
    echo -e "${YELLOW}Essaye avec:${NC}"
    echo "  ./test_minishell.sh nom_exact_de_ton_executable"
    exit 1
fi

# Vérifier que le fichier est exécutable
if [ ! -x "$MINISHELL_PATH" ]; then
    echo -e "${RED}Erreur: $MINISHELL_PATH n'est pas exécutable${NC}"
    echo -e "${YELLOW}Essaye: chmod +x $MINISHELL_NAME${NC}"
    exit 1
fi

# Créer quelques fichiers de test
echo "test content" > test_file.txt
echo -e "line1\nline2\nline3" > multiline.txt
echo "secret" > readonly.txt
chmod 444 readonly.txt

print_header "TESTS AUTOMATISÉS MINISHELL"

# 1. Tests de base
print_header "1. TESTS DE BASE"

run_test "ls" "Liste fichiers courants"
run_test "pwd" "Répertoire courant"
run_test "echo hello" "Echo simple"
run_test "echo \"hello world\"" "Echo avec quotes"
run_test "cat test_file.txt" "Cat fichier simple"
run_test "wc test_file.txt" "Compter lignes/mots"

# 2. Tests de PATH
print_header "2. TESTS DE PATH ET EXÉCUTABLES"

run_test "/bin/ls" "Chemin absolu ls"
run_test "/bin/echo test" "Chemin absolu echo"
run_test "commandebidon" "Commande inexistante"
run_test "/bin/commandebidon" "Chemin inexistant"

# 3. Tests de pipes simples
print_header "3. TESTS DE PIPES"

run_test "ls | cat" "Pipe simple ls cat"
run_test "echo test | cat" "Pipe echo cat"
run_test "cat test_file.txt | cat" "Pipe cat cat"
run_test "ls | wc -l" "Pipe ls wc"
run_test "echo -e \"a\nb\nc\" | wc -l" "Pipe echo wc avec newlines"

# 4. Tests de pipes multiples
print_header "4. TESTS DE PIPES MULTIPLES"

run_test "echo test | cat | cat" "Triple pipe"
run_test "ls | head | tail" "Pipe ls head tail"
run_test "echo -e \"1\n2\n3\n4\n5\" | head -3 | tail -1" "Pipe complexe avec head/tail"

# 5. Tests de redirections de sortie
print_header "5. REDIRECTIONS DE SORTIE (>)"

run_test "echo test > output1.txt" "Redirection simple"
run_test "ls > output2.txt" "Redirection ls"
run_test "echo first > overwrite.txt; echo second > overwrite.txt" "Écrasement fichier"

# Vérifier le contenu des fichiers créés
if [ -f "output1.txt" ] && [ "$(cat output1.txt)" = "test" ]; then
    ((TOTAL_TESTS++))
    print_test "Vérification contenu output1.txt"
    print_pass
else
    ((TOTAL_TESTS++))
    print_test "Vérification contenu output1.txt"
    print_fail "echo test > output1.txt"
fi

# 6. Tests de redirections d'ajout
print_header "6. REDIRECTIONS D'AJOUT (>>)"

run_test "echo line1 > append.txt" "Création fichier pour append"
run_test "echo line2 >> append.txt" "Append ligne 2"
run_test "echo line3 >> append.txt" "Append ligne 3"

# 7. Tests de redirections d'entrée
print_header "7. REDIRECTIONS D'ENTRÉE (<)"

run_test "cat < test_file.txt" "Redirection entrée cat"
run_test "wc < test_file.txt" "Redirection entrée wc"
run_test "cat < fichier_inexistant.txt" "Redirection fichier inexistant"

# 8. Tests de variables d'environnement
print_header "8. VARIABLES D'ENVIRONNEMENT"

run_test "echo \$HOME" "Variable HOME"
run_test "echo \$USER" "Variable USER"
run_test "echo \$PATH" "Variable PATH"
run_test "echo \$INEXISTANTE" "Variable inexistante"
run_test "echo \"Home: \$HOME\"" "Variable dans quotes"

# 9. Tests de quotes
print_header "9. TESTS DE QUOTES"

run_test "echo 'hello world'" "Quotes simples"
run_test "echo \"hello world\"" "Quotes doubles"
run_test "echo 'avec \$HOME'" "Variable dans quotes simples"
run_test "echo \"avec \$HOME\"" "Variable dans quotes doubles"
run_test "echo ''" "Quotes simples vides"
run_test "echo \"\"" "Quotes doubles vides"

# 10. Tests d'espaces
print_header "10. TESTS D'ESPACES"

run_test "echo    hello    world" "Multiples espaces"
run_test "   echo hello   " "Espaces début/fin"
run_test "ls     -l" "Espaces entre arguments"

# 11. Tests de combinaisons pipes + redirections
print_header "11. PIPES + REDIRECTIONS"

run_test "ls | cat > pipe_output.txt" "Pipe vers fichier"
run_test "echo test | cat | cat > multi_pipe.txt" "Multi-pipe vers fichier"
run_test "cat < test_file.txt | cat" "Redirection entrée vers pipe"

# 12. Tests d'erreurs
print_header "12. TESTS D'ERREURS"

run_test "cat /fichier/inexistant" "Fichier inexistant"
run_test "ls /dossier/inexistant" "Dossier inexistant"
run_test "/etc" "Répertoire comme commande"
run_test "echo test > /root/impossible.txt" "Écriture impossible"

# 13. Tests de cas limites
print_header "13. CAS LIMITES"

run_test "echo" "Echo sans arguments"
run_test "cat" "Cat sans arguments (timeout après $TIMEOUT sec)"
run_test "echo a b c d e f g h i j" "Nombreux arguments"
run_test "echo \"\$(echo nested)\"" "Commande nested (doit échouer proprement)"

# 14. Tests spéciaux
print_header "14. TESTS SPÉCIAUX"

# Test ligne vide (difficile à tester automatiquement)
run_test "   " "Ligne avec espaces seulement"
run_test "" "Ligne vide"

# Résumé final
print_header "RÉSUMÉ DES TESTS"

echo -e "${BLUE}Total des tests: $TOTAL_TESTS${NC}"
echo -e "${GREEN}Tests réussis: $PASSED_TESTS${NC}"
echo -e "${RED}Tests échoués: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 TOUS LES TESTS SONT PASSÉS !${NC}"
    success_rate=100
else
    success_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "${YELLOW}Taux de réussite: $success_rate%${NC}"
fi

# Nettoyage
echo -e "\n${BLUE}Nettoyage des fichiers de test...${NC}"
cd ..
rm -rf "$TEST_DIR"

# Code de sortie
if [ $FAILED_TESTS -eq 0 ]; then
    exit 0
else
    exit 1
fi
