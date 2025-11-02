#include "Serializer.hpp"
#include "Data.hpp"


// Définis mais non utilisables publiquement (classe utilitaire statique)
Serializer::Serializer() {}
Serializer::Serializer(const Serializer &) {}
Serializer &Serializer::operator=(const Serializer &) { return *this; }
Serializer::~Serializer() {}


uintptr_t Serializer::serialize(Data *ptr) {
// reinterpret_cast permet de re-lire les bits du pointeur comme un entier non signé
return reinterpret_cast<uintptr_t>(ptr);
}


Data* Serializer::deserialize(uintptr_t raw) {
// Opération inverse: on récupère le pointeur d'origine
return reinterpret_cast<Data*>(raw);
}