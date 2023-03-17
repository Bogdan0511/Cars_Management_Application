#pragma once
#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
class Masina {
private:
	string nr_inm;
	string producator;
	string model;
	string tip;
public:
	//Masina() = default;
	Masina(string nr_inm, string producator, string model, string tip) :nr_inm{ nr_inm }, producator{ producator }, model{ model }, tip{ tip }{};
	Masina(const Masina& ot) :nr_inm{ ot.nr_inm }, producator{ ot.producator }, model{ ot.model }, tip{ ot.tip }{};
	string getNr_inm() const;
	string getProducator() const;
	string getModel() const;
	string getTip() const;

	void setNr_inm(string nrNou);
	void setProducator(string producatorNou);
	void setModel(string modelNou);
	void setTip(string tipNou);
};

/*
Compara doua masini dupa producator si model
@return: true daca producatorul masinii m1 e inaintea (alfabetic)
		 producatorului masinii m2, false altfel
		 daca avem acelasi producator, atunci comparam modelele masinilor
		 */
bool cmpProducatorMasina(const Masina& m1, const Masina& m2);

/*
Compara doua masini dupa numarul de inmatriculare
@return: true daca numarul de inmatriculare al masinii m1 e inaintea (alfabetic)
		 numarului de inmatriculare al masinii m2, false altfel
		 */
bool cmpNr_inmMasina(const Masina& m1, const Masina& m2);

void testeDomain();