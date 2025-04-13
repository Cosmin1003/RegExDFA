#include "DeterministicFiniteAutomaton.h"

DeterministicFiniteAutomaton::DeterministicFiniteAutomaton(std::set<std::string> stari, std::set<char> alfabet, std::set<transition> tranzitii, std::string stareInitiala, std::set<std::string> stariFinale)
{
	this->stari = stari;
	this->alfabet = alfabet;
	this->tranzitii = tranzitii;
	this->stareInitiala = stareInitiala;
	this->stariFinale = stariFinale;
}


bool DeterministicFiniteAutomaton::VerifyAutomaton()
{
	if (stari.empty()) {
		std::cerr << "Multimea starilor este vida." << std::endl;
		return false;
	}

	if (alfabet.empty()) {
		std::cerr << "Alfabetul este vid." << std::endl;
		return false;
	}


	if (stareInitiala.empty() || stari.find(stareInitiala) == stari.end()) {
		std::cerr << "Starea initiala nu este valida sau nu apartine multimii de stari." << std::endl;
		return false;
	}

	for (const auto& sf : stariFinale) {
		if (stari.find(sf) == stari.end()) {
			std::cerr << "Eroare: Una dintre starile finale (" << sf << ") nu se afla in multimea starilor.\n";
			return false;
		}
	}

	for (const auto& tranzitie : tranzitii) {
		if (stari.find(tranzitie.first) == stari.end()) {
			std::cerr << "Eroare: Starea sursa (" << tranzitie.first << ") a unei tranzitii nu se afla in multimea starilor.\n";
			return false;
		}
		if (stari.find(tranzitie.third) == stari.end()) {
			std::cerr << "Eroare: Starea destinatie (" << tranzitie.third << ") a unei tranzitii nu se afla in multimea starilor.\n";
			return false;
		}
		if (alfabet.find(tranzitie.second) == alfabet.end()) {
			std::cerr << "Eroare: Simbolul (" << tranzitie.second << ") al unei tranzitii nu se afla in alfabet.\n";
			return false;
		}
	}

	return true;
}

void DeterministicFiniteAutomaton::PrintAutomaton(std::ostream& out)
{
	out << "Stari: ";
	for (const auto& stare : stari)
		out << stare << ' ';
	out << '\n';

	out << "Alfabet: ";
	for (const auto& simbol : alfabet)
		out << simbol << ' ';
	out << '\n';

	out << "Starea initiala: " << stareInitiala << '\n';

	out << "Stari finale: ";
	for (const auto& stare : stariFinale)
		out << stare << ' ';
	out << '\n';

	out << "Tranzitii: " << '\n';
	for (const auto& tranzitie : tranzitii)
		out << "(" << tranzitie.first << "," << tranzitie.second << ") -> " <<tranzitie.third << '\n';
	out << '\n';
	out << '\n';

}

bool DeterministicFiniteAutomaton::CheckWord(const std::string& cuvant)
{
	std::string stareCurenta = stareInitiala;

	for (char simbol : cuvant) {
		if (alfabet.find(simbol) == alfabet.end()) {
			std::cerr << "Eroare: Simbolul '" << simbol << "' nu se afla in alfabet.\n";
			return false;
		}

		bool tranzitieGasita = false;
		for (const auto& tranzitie : tranzitii) {
			if (tranzitie.first == stareCurenta && tranzitie.second == simbol) {
				stareCurenta = tranzitie.third;
				tranzitieGasita = true;
				break;
			}
		}

		if (!tranzitieGasita) {
			std::cerr << "Eroare: Nu exista o tranzitie valida din starea '" << stareCurenta
				<< "' pentru simbolul '" << simbol << "'.\n";
			return false;
		}
	}

	if (stariFinale.find(stareCurenta) != stariFinale.end()) {
		return true;
	}
	else {
		return false;
	}
}
