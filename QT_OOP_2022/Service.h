#pragma once
#include "Repository.h"
#include "Undo.h"
#include "Validator.h"
#include "Spalatorie.h"
#include <functional>
#include <memory>
#include <unordered_map>
using std::function;
using std::vector;
using std::unique_ptr;

class CarStore {
private:
	CarRepository& repo;
	CarValidator& val;
	Car_Wash spal;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	/*
	Filtreaza lista de masini pe baza unui criteriu

	@param fct: functia dupa care se filtreaza lista de melodii
	@return: lista cu melodiile care indeplinesc criteriul dat
	*/
	vector<Masina> filter(function<bool(const Masina&)> fct);

	/*
	* Functie de sortare proprie
	*
	* @param maiMicF: functia de comparare folosita pentru sortare
	*
	* @return: lista de masini sortata dupa criteriul dat (vector cu elemente de
	*			tip Masina)
	*/
	vector<Masina> generalSort(bool(*maiMicF)(const Masina&, const Masina&));

public:
	CarStore(CarRepository& carRepo, CarValidator& val) :repo{ carRepo }, val{ val }{};

	//constructor de copiere
	//punem delete fiindca nu vrem sa se faca nicio copie la Service
	//(in aplicatie avem 1 singur Service)
	CarStore(const CarStore& ot) = delete;

	void undo();

	/*
	Adauga o masina cu numarul de inmatriculare nr_inm, producatorul prod, modelul mod si tipul tip
	*@param nr_inm: numarul de inmatriculare al masinii care se adauga (string)
	*@param prod: producatorul masinii care se adauga (string)
	*@param mod: modelul masinii care se adauga (string)
	*@param tip: tipul masinii care se adauga (string)
	*
	* @throws:
	*	RepoException daca mai exista masina cu numarul de inmatriculare dat
	*	ValidationException daca masina nu este valida
	*/

	void addCar(string nr_inm, string prod, string mod, string tip);

	void removeCar(string nr_inm);

	void updateCar(string nr_inm, string new_prod, string new_mod, string new_tip);

	/*
	Returneaza un vector cu toate masinile disponibile

	@return: lista cu toate masinile disponibile (vector cu obiecte de tip Masina)
	*/

	vector<Masina>& getAllCars() {
		return this->repo.getAllCars();
	}


	/*
	* Returneaza o lista de masini cu producatorul dat
	*
	* @param prod: producatorul dupa care se filtreaza
	* @return: lista cu masinile care au producatorul dat (vector cu elemente de tip Masina)
	*/
	vector<Masina> filtrareProducator(string prod);

	/*
	* Returneaza o lista de masini cu tipul dat
	*
	* @param tip: tipul masinilor cautate (string)
	*
	* @return: lista cu masinile care au tipul dat (vector cu elemente de tip Masina)
	*/
	vector<Masina> filtrareTip(string tip);


	/*
	* Sorteaza masinile dupa numarul de inmatriculare
	*
	* @return: lista cu masinile sortate dupa numarul de inmatriculare
	*/
	vector<Masina> sortByNr_inm();

	/*
	* Sorteaza masinile dupa producator si model
	*
	* @return: lista cu masinile sortate dupa producator si model
	*/
	vector<Masina> sortByProducator();

	/*
	Adauga o masina cu numarul de inmatriculare dat in spalatorie
	param: nr_inm, numarul de inmatriculare al masinii care se adauga (string)

	post: masina este adaugata in spalatorie
	@throws: RepoException, daca nu exista masina cu numarul de inmatriculare dat
	*/
	void addToWash(string nr_inm);

	/*
	Adauga un numar aleatoriu de masini in spalatorie
	param: howMany, cate masini se adauga (int)

	return: numarul de masini adaugate in spalatorie
	post: se adauga un numar aleatoriu de masini in spalatorie
	*/
	int addRandomToWash(int howMany);

	/*
	Elimina toate masinile din spalatorie

	post: spalatoia nu contine nicio masina
	*/
	void emptyWash();

	/*
	Returneaza un vector cu toate masinile din spalatorie
	*/
	const vector<Masina>& getWashCars();

	/*
	Creeaza rapoarte
	*/
	void Rapoarte();

	/*
	Obtine spalatoria curenta
	*/
	Car_Wash& getWash();
};
void testeService();