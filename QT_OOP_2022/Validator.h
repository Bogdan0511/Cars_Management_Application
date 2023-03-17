#pragma once

#include "Domain.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
class ValidationException {
	vector<string> errorMsg;
public:
	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};
/*
Clasa pentru validarea masinilor
O masina este valida daca:
	are numarul de inmatriculare format din 6 sau 7 caractere
	are producatorul format din mai mult de 1 caracter
	are modelul format din cel putin un caracter
	are tipul unul dintre: sedan, combi, suv, hatchback, sport, supersport
*/
class CarValidator {

public:
	void valideaza(const Masina& m) {
		vector<string> errors;
		if (m.getNr_inm().length() != 6 && m.getNr_inm().length() != 7)
			errors.push_back("Numarul de inmatriculare nu este valid!");
		if (m.getProducator().length() < 2)
			errors.push_back("Producatorul nu este valid!");
		if (m.getModel().length() < 1)
			errors.push_back("Modelul nu este valid!");
		if (m.getTip() != "sedan" && m.getTip() != "combi" && m.getTip() != "suv" && m.getTip() != "hatchback" && m.getTip() != "sport" && m.getTip() != "supersport")
			errors.push_back("Tipul nu este valid!");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};
