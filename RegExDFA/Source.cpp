#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include "DeterministicFiniteAutomaton.h"
#include <cctype>
#include <vector>
#include <queue>
#include <regex>

DeterministicFiniteAutomaton alternare(DeterministicFiniteAutomaton A, DeterministicFiniteAutomaton B, int& contor) {
	std::set<std::string> stari;
	std::set<char> alfabet;
	std::set<transition> tranzitii;

	std::string newStart = "q" + std::to_string(contor++);
	std::string newEnd = "q" + std::to_string(contor++);

	for (const auto& state : A.getStates()) {
		stari.insert(state);
	}
	for (const auto& state : B.getStates()) {
		stari.insert(state);
	}
	stari.insert(newStart);
	stari.insert(newEnd);

	for (const auto& symbol : A.getAlphabet()) {
		alfabet.insert(symbol);
	}
	for (const auto& symbol : B.getAlphabet()) {
		alfabet.insert(symbol);
	}

	for (const auto& t : A.getTransitions()) {
		tranzitii.insert(transition(t.first, t.second, t.third));
	}
	for (const auto& t : B.getTransitions()) {
		tranzitii.insert(transition(t.first, t.second, t.third));
	}

	tranzitii.insert(transition(newStart, '#', A.getInitialState()));
	tranzitii.insert(transition(newStart, '#', B.getInitialState()));

	for (const auto& finalState : A.getFinalStates()) {
		tranzitii.insert(transition(finalState, '#', newEnd));
	}
	for (const auto& finalState : B.getFinalStates()) {
		tranzitii.insert(transition(finalState, '#', newEnd));
	}

	std::string stareInitiala = newStart;
	std::set<std::string> stariFinale = { newEnd };

	return DeterministicFiniteAutomaton(stari, alfabet, tranzitii, stareInitiala, stariFinale);
}


DeterministicFiniteAutomaton concatenare(const DeterministicFiniteAutomaton& A, const DeterministicFiniteAutomaton& B) {
	std::set<std::string> stari;
	std::set<char> alfabet;
	std::set<transition> tranzitii;

	for (const auto& state : A.getStates()) {
		stari.insert(state);
	}
	for (const auto& state : B.getStates()) {
		stari.insert(state);
	}

	for (const auto& symbol : A.getAlphabet()) {
		alfabet.insert(symbol);
	}
	for (const auto& symbol : B.getAlphabet()) {
		alfabet.insert(symbol);
	}

	for (const auto& t : A.getTransitions()) {
		tranzitii.insert(transition(t.first, t.second, t.third));
	}
	for (const auto& t : B.getTransitions()) {
		tranzitii.insert(transition(t.first, t.second, t.third));
	}

	for (const auto& finalState : A.getFinalStates()) {
		tranzitii.insert(transition(finalState, '#', B.getInitialState()));
	}

	std::string stareInitiala = A.getInitialState();
	std::set<std::string> stariFinale = B.getFinalStates();

	return DeterministicFiniteAutomaton(stari, alfabet, tranzitii, stareInitiala, stariFinale);
}


DeterministicFiniteAutomaton stelare(DeterministicFiniteAutomaton A, int& contor) {
	std::set<std::string> stari;
	std::set<char> alfabet;
	std::set<transition> tranzitii;

	std::string newStart = "q" + std::to_string(contor++);
	std::string newEnd = "q" + std::to_string(contor++);

	for (const auto& state : A.getStates()) {
		stari.insert(state);
	}
	stari.insert(newStart);
	stari.insert(newEnd);

	for (const auto& symbol : A.getAlphabet()) {
		alfabet.insert(symbol);
	}

	for (const auto& t : A.getTransitions()) {
		tranzitii.insert(transition(t.first, t.second, t.third));
	}

	tranzitii.insert(transition(newStart, '#', A.getInitialState()));
	tranzitii.insert(transition(newStart, '#', newEnd));
	for (const auto& finalState : A.getFinalStates()) {
		tranzitii.insert(transition(finalState, '#', newEnd));
		tranzitii.insert(transition(finalState, '#', A.getInitialState()));
	}

	std::string stareInitiala = newStart;
	std::set<std::string> stariFinale = { newEnd };

	return DeterministicFiniteAutomaton(stari, alfabet, tranzitii, stareInitiala, stariFinale);
}


DeterministicFiniteAutomaton obtainAFN(const std::string& expression) {
	std::stack<DeterministicFiniteAutomaton> SA;
	int contor = 0;

	for (char simbol : expression) {
		if (isalnum(simbol)) {
			std::set<std::string> stari;
			std::set<char> alfabet;
			std::set<transition> tranzitii;

			std::string stareInitiala = "q" + std::to_string(contor++);
			std::string stareFinala = "q" + std::to_string(contor++);

			stari.insert(stareInitiala);
			stari.insert(stareFinala);
			alfabet.insert(simbol);
			tranzitii.insert(transition(stareInitiala, simbol, stareFinala));

			std::set<std::string> stariFinale = { stareFinala };
			DeterministicFiniteAutomaton a(stari, alfabet, tranzitii, stareInitiala, stariFinale);
			SA.push(a);
		}
		else if (simbol == '|') {
			DeterministicFiniteAutomaton B = SA.top(); SA.pop();
			DeterministicFiniteAutomaton A = SA.top(); SA.pop();
			SA.push(alternare(A, B, contor));
		}
		else if (simbol == '.') {
			DeterministicFiniteAutomaton B = SA.top(); SA.pop();
			DeterministicFiniteAutomaton A = SA.top(); SA.pop();
			SA.push(concatenare(A, B));
		}
		else if (simbol == '*') {
			DeterministicFiniteAutomaton A = SA.top(); SA.pop();
			SA.push(stelare(A, contor));
		}
	}
	return SA.top();
}

std::string addConcatenationDots(const std::string& regex) {
	std::string modifiedRegex;
	for (size_t i = 0; i < regex.size(); ++i) {
		char current = regex[i];
		modifiedRegex += current;

		if ((isalnum(current) || current == ')' || current == '*') &&
			(i + 1 < regex.size() && (isalnum(regex[i + 1]) || regex[i + 1] == '('))) {
			modifiedRegex += '.';
		}
	}
	return modifiedRegex;
}

std::string toPostfix(const std::string& regex) {
	std::stack<char> operators;
	std::string result;

	auto precedence = [](char op) {
		if (op == '*') return 3;
		if (op == '.') return 2;
		if (op == '|') return 1;
		return 0;
		};

	int parantezeDeschise = 0;

	for (char ch : regex) {
		if (isalnum(static_cast<unsigned char>(ch))) {
			result += ch;
		}
		else if (ch == '(') {
			operators.push(ch);
			parantezeDeschise++;
		}
		else if (ch == ')') {
			parantezeDeschise--;
			while (!operators.empty() && operators.top() != '(') {
				result += operators.top();
				operators.pop();
			}
			if (!operators.empty() && operators.top() == '(') {
				operators.pop();
			}
			else {
				std::cerr << "Eroare: Paranteză închisă fără pereche!" << std::endl;
				return "";
			}
		}
		else if (ch == '*' || ch == '.' || ch == '|') {
			while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
				result += operators.top();
				operators.pop();
			}
			operators.push(ch);
		}
		else {
			std::cerr << "Eroare: Caracter nevalid detectat: " << ch << std::endl;
			return "";
		}
	}

	if (parantezeDeschise != 0) {
		std::cerr << "Eroare: Paranteze deschise fără pereche!" << std::endl;
		return "";
	}

	while (!operators.empty()) {
		if (operators.top() == '(') {
			std::cerr << "Eroare: Paranteză deschisă lipsă!" << std::endl;
			return "";
		}
		result += operators.top();
		operators.pop();
	}

	return result;
}

std::set<std::string> lambdaClosure(
	const std::string& state,
	const std::map<std::string, std::vector<std::string>>& lambdaTransitions
) {
	std::set<std::string> closure;
	std::queue<std::string> toVisit;

	closure.insert(state);
	toVisit.push(state);

	while (!toVisit.empty()) {
		std::string current = toVisit.front();
		toVisit.pop();

		if (lambdaTransitions.count(current)) {
			for (const auto& nextState : lambdaTransitions.at(current)) {
				if (!closure.count(nextState)) {
					closure.insert(nextState);
					toVisit.push(nextState);
				}
			}
		}
	}

	return closure;
}

DeterministicFiniteAutomaton convertToAFD(
	const DeterministicFiniteAutomaton& afn
) {
	auto afnStates = afn.getStates();
	auto afnAlphabet = afn.getAlphabet();
	auto afnTransitions = afn.getTransitions();
	auto afnInitialState = afn.getInitialState();
	auto afnFinalStates = afn.getFinalStates();

	std::map<std::string, std::vector<std::string>> lambdaTransitions;
	for (const auto& t : afnTransitions) {
		if (t.second == '#') {
			lambdaTransitions[t.first].push_back(t.third);
		}
	}

	std::set<std::string> initialClosure = lambdaClosure(afnInitialState, lambdaTransitions);

	std::map<std::set<std::string>, std::string> stateMapping;
	std::set<std::string> afdStates;
	std::set<transition> afdTransitions;
	std::string afdInitialState = "q0";
	std::set<std::string> afdFinalStates;

	stateMapping[initialClosure] = afdInitialState;
	afdStates.insert(afdInitialState);

	std::queue<std::set<std::string>> toProcess;
	toProcess.push(initialClosure);

	int stateCounter = 1;

	while (!toProcess.empty()) {
		std::set<std::string> current = toProcess.front();
		toProcess.pop();
		std::string currentStateName = stateMapping[current];

		for (const auto& s : current) {
			if (afnFinalStates.count(s)) {
				afdFinalStates.insert(currentStateName);
				break;
			}
		}

		for (char symbol : afnAlphabet) {
			std::set<std::string> newSet;

			for (const auto& state : current) {
				for (const auto& t : afnTransitions) {
					if (t.first == state && t.second == symbol) {
						std::set<std::string> closure = lambdaClosure(t.third, lambdaTransitions);
						newSet.insert(closure.begin(), closure.end());
					}
				}
			}

			if (!newSet.empty()) {
				if (!stateMapping.count(newSet)) {
					stateMapping[newSet] = "q" + std::to_string(stateCounter++);
					afdStates.insert(stateMapping[newSet]);
					toProcess.push(newSet);
				}

				afdTransitions.insert(transition(currentStateName, symbol, stateMapping[newSet]));
			}
		}
	}

	return DeterministicFiniteAutomaton(afdStates, afnAlphabet, afdTransitions, afdInitialState, afdFinalStates);
}

bool esteRegexValid(const std::string& regexPattern) {
	try {
		std::regex regexTest(regexPattern);
		return true;
	}
	catch (const std::regex_error& e) {
		return false;
	}
}

DeterministicFiniteAutomaton CreateAFD(const std::string& expression)
{
	std::string newExpression = addConcatenationDots(expression);
	newExpression = toPostfix(newExpression);

	DeterministicFiniteAutomaton afn = obtainAFN(newExpression);

	DeterministicFiniteAutomaton afd = convertToAFD(afn);

	return afd;
}

int main() {
	std::string expression;
	std::ifstream file("Text.txt");
	if (!file.is_open()) {
		std::cerr << "Nu s-a putut deschide fișierul Text.txt!" << std::endl;
		return 1;
	}
	std::getline(file, expression);
	std::string cleanExpression;
	for (char ch : expression) {
		if (isalnum(static_cast<unsigned char>(ch)) || ch == '(' || ch == ')' || ch == '*' || ch == '|' || ch == '.') {
			cleanExpression += ch;
		}
		else {
			std::cerr << "Caracter nevalid detectat: " << ch << std::endl;
		}
	}
	expression = cleanExpression;

	file.close();


	if (esteRegexValid(expression))
	{
		DeterministicFiniteAutomaton afd = CreateAFD(expression);
		std::ofstream fileOut("Out.txt");

		bool continua = true;
		while (continua) {
			std::cout << "\nMeniu:\n";
			std::cout << "a) Afisarea inteligibila a expresiei regulate\n";
			std::cout << "b) Afisarea automatului M (in consola si fisier)\n";
			std::cout << "c) Verificarea unui cuvant in automat\n";
			std::cout << "s) Iesire\n";
			std::cout << "Alege optiunea: ";

			char optiune;
			std::cin >> optiune;
			std::string cuvant;

			switch (optiune) {
			case 'a':
				std::cout << expression << '\n';
				break;

			case 'b':
				std::cout << '\n';
				afd.PrintAutomaton(std::cout);
				afd.PrintAutomaton(fileOut);
				break;

			case 'c':
				std::cout << '\n' << "Introduceti cuvantul pe care doriti sa il verificati: ";
				std::cin >> cuvant;
				if (afd.CheckWord(cuvant))
					std::cout << "Cuvantul introdus se potriveste automatului!" << '\n';
				else
					std::cout << "Cuvantul introdus nu se potriveste automatului!" << '\n';
				break;

			case 's':
				continua = false;
				std::cout << "Iesire din program.\n";
				break;

			default:
				std::cout << "Optiune invalida. Incercati din nou.\n";
				break;
			}
		}

		fileOut.close();
	}
	else
		std::cout << "Expresia introdusa nu este valida!";



	return 0;
}

