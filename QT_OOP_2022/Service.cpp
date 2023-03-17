#pragma once
#include "Service.h"
#include <assert.h>
#include <unordered_map>
#include <functional>
#include <algorithm>
using std::sort;
using std::cout;
using std::function;

void CarStore::addCar(string nr_inm, string prod, string mod, string tip) {
	Masina m1{ nr_inm, prod, mod, tip };
	val.valideaza(m1);
	repo.store(m1);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, m1));
}

void CarStore::updateCar(string nr_inm, string new_prod, string new_mod, string new_tip) {
	Masina m_searched = repo.find(nr_inm);
	repo.sterge(m_searched);
	m_searched.setProducator(new_prod);
	m_searched.setModel(new_mod);
	m_searched.setTip(new_tip);
	val.valideaza(m_searched);
	repo.store(m_searched);
	undoActions.push_back(std::make_unique<UndoAdauga>(repo, m_searched));
}

void CarStore::removeCar(string nr_inm) {
	Masina m = repo.find(nr_inm);
	repo.sterge(m);
	undoActions.push_back(std::make_unique<UndoSterge>(repo, m));
}

void CarStore::undo() {
	if (undoActions.empty()) {
		throw RepoException("Nu mai exista operatii recente!");
	}
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

vector<Masina> CarStore::generalSort(bool(*maiMicF)(const Masina&, const Masina&)) {
	vector<Masina> v{ repo.getAllCars() };
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Masina aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}



vector<Masina> CarStore::sortByNr_inm() {
	auto sortedCopy = repo.getAllCars();
	sort(sortedCopy.begin(), sortedCopy.end(), cmpNr_inmMasina);
	return sortedCopy;
}

vector<Masina> CarStore::sortByProducator() {
	return generalSort(cmpProducatorMasina);
}

vector<Masina> CarStore::filter(function<bool(const Masina&)> fct) {
	vector<Masina> filteredCars;
	for (const auto& car : repo.getAllCars()) {
		if (fct(car)) {
			filteredCars.push_back(car);
		}
	}
	return filteredCars;
}

vector<Masina> CarStore::filtrareProducator(string prod) {
	return filter([prod](const Masina& m) {
		return m.getProducator() == prod;
		});
}

vector<Masina> CarStore::filtrareTip(string tip) {
	return filter([tip](const Masina& m) {
		return m.getTip() == tip;
		});
}

void CarStore::addToWash(string nr_inm) {
	const auto& car = repo.find(nr_inm);
	spal.addCarToWash(car);
}

int CarStore::addRandomToWash(int howMany) {
	spal.addRandomCars(this->getAllCars(), howMany);
	return spal.getAllWashCars().size();
}

void CarStore::emptyWash() {
	spal.emptyCarWash();
}

const vector<Masina>& CarStore::getWashCars() {
	return spal.getAllWashCars();
}

Car_Wash& CarStore::getWash() {
	return this->spal;
}


void testAddService() {
	CarRepository testRepo;
	CarValidator testVal;
	CarStore testService{ testRepo,testVal };

	testService.addCar("CJ65GEN", "Audi", "A8", "sedan");
	testService.addCar("BT33HER", "Porsche", "Cayenne", "suv");
	testService.addCar("SB49REX", "Mitsubishi", "Lancer", "sedan");

	assert(testService.getAllCars().size() == 3);
	try {
		testService.addCar("CJ65GEN", "Audi", "A8", "sedan");
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}

	try {
		testService.addCar("DB27GOL", "Ferrari", "LaFerrari", "supersport");
		assert(true);
	}
	catch (ValidationException&) {
		assert(false);
	}

	try {
		testService.addCar("CALIFORNIA900BOSS", "Ford", "Mustang", "sport");
		assert(false);
	}
	catch (ValidationException& ve) {
		assert(ve.getErrorMessages() == "Numarul de inmatriculare nu este valid!\n");
	}

	try {
		testService.addCar("MH78DUN", "", "Splash", "hatchback");
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}


	try {
		testService.addCar("VS91GEG", "Dacia", "Sandero", "cotetz");
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}

	try {
		testService.addCar("GL42EWQ", "Nissan", "", "sedan");
		assert(false);
	}
	catch (ValidationException&) {
		assert(true);
	}


}

void testFilterService() {
	CarRepository testRepo;
	CarValidator testVal;
	CarStore testService{ testRepo,testVal };

	testService.addCar("BH10VFB", "Mercedes-Benz", "CLS", "sedan");
	testService.addCar("BH21DNS", "Mercedes-Benz", "GLE", "suv");
	testService.addCar("B43TOY", "Renault", "Talisman", "sedan");
	testService.addCar("DJ55FEY", "Volkswagen", "Arteon", "sedan");
	testService.addCar("CT61FLO", "Suzuki", "Splash", "hatchback");
	testService.addCar("IL22PAN", "Dacia", "Logan", "combi");

	vector<Masina> Mertane = testService.filtrareProducator("Mercedes-Benz");
	assert(Mertane.size() == 2);
	vector<Masina> Sedanuri = testService.filtrareTip("sedan");
	assert(Sedanuri.size() == 3);


	vector<Masina> cars1 = testService.filtrareProducator("Maybach");
	assert(cars1.size() == 0);
	vector<Masina> cars2 = testService.filtrareTip("sport");
	assert(cars2.size() == 0);

}

void testSortService() {

	CarRepository testRepo;
	CarValidator testVal;
	CarStore testService{ testRepo,testVal };

	testService.addCar("BH10VFB", "Mercedes-Benz", "CLS", "sedan");
	testService.addCar("BH21DNS", "Mercedes-Benz", "GLE", "suv");
	testService.addCar("DJ55FEY", "Volkswagen", "Arteon", "sedan");
	testService.addCar("CT61FLO", "Suzuki", "Splash", "hatchback");
	testService.addCar("IL22PAN", "Dacia", "Logan", "combi");

	vector<Masina> sortedByNr_inm = testService.sortByNr_inm();
	assert(sortedByNr_inm[0].getNr_inm() == "BH10VFB");
	assert(sortedByNr_inm[1].getNr_inm() == "BH21DNS");
	assert(sortedByNr_inm[2].getNr_inm() == "CT61FLO");
	assert(sortedByNr_inm[4].getNr_inm() == "IL22PAN");

	vector<Masina> sortedByProducator = testService.sortByProducator();
	assert(sortedByProducator[0].getProducator() == "Dacia");
	assert(sortedByProducator[0].getModel() == "Logan");

	assert(sortedByProducator[2].getProducator() == "Mercedes-Benz");
	assert(sortedByProducator[2].getModel() == "GLE");

	assert(sortedByProducator[4].getProducator() == "Volkswagen");
	assert(sortedByProducator[4].getModel() == "Arteon");

}

void testeService() {
	testAddService();
	testFilterService();
	testSortService();
}