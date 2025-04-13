#pragma once

#include <iostream>
#include <string>
#include <set>
#include <map>

struct transition {
	std::string first;
	char second;
	std::string third;

	transition(std::string f, char s, std::string t)
		: first(f), second(s), third(t) {}

	bool operator<(const transition& other) const {
		if (first != other.first)
			return first < other.first;
		if (second != other.second)
			return second < other.second;
		return third < other.third;
	}
};

class DeterministicFiniteAutomaton
{
private:
	std::set<std::string> stari;
	std::set<char> alfabet;
	std::set<transition> tranzitii;
	std::string stareInitiala;
	std::set<std::string> stariFinale;


public:
	DeterministicFiniteAutomaton(
		std::set<std::string> stari,
		std::set<char> alfabet,
		std::set<transition> tranzitii,
		std::string stareInitiala,
		std::set<std::string> stariFinale
		);

	std::set<std::string> getStates() const { return stari; }
	std::set<char> getAlphabet() const { return alfabet; }
	std::set<transition> getTransitions() const { return tranzitii; }
	std::string getInitialState() const { return stareInitiala; }
	std::set<std::string> getFinalStates() const { return stariFinale; }

	bool VerifyAutomaton();
	void PrintAutomaton(std::ostream& out);
	bool CheckWord(const std::string& cuvant);
};

