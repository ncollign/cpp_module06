#include <iostream>
#include "Data.hpp"
#include "Serializer.hpp"


int main() {
	// Création d'un objet pour la démo
	Data *original = new Data("Alice", 42);

	// Sérialisation: Data* -> uintptr_t
	uintptr_t raw = Serializer::serialize(original);

	// Désérialisation: uintptr_t -> Data*
	Data *restored = Serializer::deserialize(raw);

	// Affichages de vérification
	std::cout << "Original ptr : " << original << "\n";
	std::cout << "Raw (hex) : 0x" << std::hex << raw << std::dec << "\n";
	std::cout << "Restored ptr : " << restored << "\n\n";

	// Vérifier que c'est bien le même objet
	if (restored == original)
	std::cout << "OK: restored pointe vers le même objet.\n";
	else
	std::cout << "KO: les pointeurs diffèrent (ce ne devrait pas arriver).\n";

	// Démonstration: on accède aux champs via restored
	std::cout << "name= " << restored->name << ", age= " << restored->age << "\n";

	// Nettoyage
	delete original;
	return 0;
}