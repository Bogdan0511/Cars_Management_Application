#pragma once
#include "Domain.h"
#include <vector>
#include <algorithm>
#include <string>
using std::string;
using std::vector;
/*
Clasa de exceptii specifice Repo
*/
class RepoException {
private:
	string errorMsg;
public:
	RepoException(string errorMsg) :errorMsg{ errorMsg } {};
	string getErrorMessage() {
		return this->errorMsg;
	}
};

class CarRepository {
private:
	vector<Masina> allCars;
public:

	//CarRepository() = default;
	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Repository
	//(in aplicatie avem 1 singur Repo)
	//CarRepository(const CarRepository& ot);
	/*
	Adauga o masina in lista
	@param m: masina care se adauga (Masina)
	@return -
	post: masina va fi adaugata in lista

	@throws: RepoException daca o masina cu acelasi nr_inm
			 exista deja
	*/
	virtual void store(const Masina& m);
	/*
	Returneaza o lista cu toate masinile
	@return: lista cu masinile (vector of Masina objects)
	*/
	vector<Masina>& getAllCars();

	/*
	Cauta o masina cu nr_inm dat

	@param nr_inm: numarul de inmatriculare al masinii cautate (String)
	@returns: entitatea Masina cu nr_inm dat (daca aceasta exista)
	@throws: RepoException daca nu exista masina cu nr_inm dat*/
	const Masina& find(string nr_inm);

	/*
	Verifica daca o masina data exista in lista

	@param m: masina care se cauta in lista
	@return: true daca masina exista, false altfel
	*/
	bool exists(const Masina& m);

	virtual void sterge(const Masina& m);
};

class CarRepositoryFile : public CarRepository {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	* Salveaza datele din fisier
	* Format: nr_inm,producator,model,tip\n
	*/
	void saveToFile();
public:
	CarRepositoryFile(string fname) :CarRepository(), filename{ fname } {
		loadFromFile();
	};
	void store(const Masina& m) override;
};

void testeRepo();
