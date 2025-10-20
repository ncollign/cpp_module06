#!/bin/bash

# Couleurs (pour plus de lisibilité)
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m' # no color

# Vérifie que le binaire existe
if [ ! -f ./convert ]; then
	echo -e "${RED}Erreur : le binaire ./convert n'existe pas.${NC}"
	echo "Compile d'abord avec: make"
	exit 1
fi

# Liste des tests
tests=(
	# Chars
	"a" "Z" "~"
	# Ints simples + bornes
	"0" "31" "127" "42" "-1" "2147483647" "-2147483648" "2147483648" "-2147483649"
	# Floats
	"0.0f" "65.0f" "3.14f" "42.f" ".5f" "-0.0f" "1e10f"
	# Doubles
	"0.0" "65.0" "3.14" "42." ".5" "-0.0" "1e309" "-1e309"
	# Pseudos
	"nan" "nanf" "+inf" "-inf" "+inff" "-inff"
	# Invalides
	"f" "+" "--" "+.f" "3.f.5"
)

# En-tête
echo -e "${CYAN}=== 🚀 Tests automatiques CPP06 ex00 ===${NC}"
echo

# Boucle de tests
for t in "${tests[@]}"; do
	echo -e "${CYAN}Input:${NC} '$t'"
	./convert "$t"
	echo -e "${GREEN}----------------------------------------${NC}"
done
