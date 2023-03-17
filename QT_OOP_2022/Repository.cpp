#include "Repository.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <assert.h>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;
using std::getline;
using std::stod;

bool CarRepository::exists(const Masina& m) {
	try {
		find(m.getNr_inm());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}
const Masina& CarRepository::find(string nr_inm) {
	for (const Masina& m : this->allCars) {
		if (m.getNr_inm() == nr_inm) {
			return m;
		}
	}
	throw RepoException("Masina cu numarul de inmatriculare " + nr_inm + " nu exista in lista!");
}


void CarRepository::store(const Masina& m) {
	if (exists(m)) {
		throw RepoException("Masina cu numarul de inmatriculare" + m.getNr_inm() + "exista deja in lista!");
	}
	this->allCars.push_back(m);
}

void CarRepository::sterge(const Masina& m) {
	auto found = std::find_if(allCars.begin(), allCars.end(), [m](const Masina& mm) {
		return mm.getNr_inm() == m.getNr_inm();
		});
	if (found == allCars.end()) {
		throw RepoException("Masina specificata nu exista!");
	}
	auto rez = allCars.erase(found);
}

vector<Masina>& CarRepository::getAllCars() {
	return this->allCars;
}

void CarRepositoryFile::loadFromFile() {
	ifstream carFile(this->filename);
	if (!carFile.is_open()) {
		throw RepoException("Cannot read from file " + filename);
	}
	string line;
	while (getline(carFile, line))
	{
		string nr_inm, prod, model, tip;
		stringstream linestream(line);
		string current_item;
		int item_no = 0;
		while (getline(linestream, current_item, ','))
		{
			if (item_no == 0) nr_inm = current_item;
			if (item_no == 1) prod = current_item;
			if (item_no == 2) model = current_item;
			if (item_no == 3) tip = current_item;
			item_no++;
		}
		Masina m{ nr_inm, prod, model, tip };

		CarRepository::store(m);


	}
	carFile.close();
}

void CarRepositoryFile::saveToFile() {
	ofstream carOutput(this->filename);
	if (!carOutput.is_open())
		throw RepoException("Cannot write to file " + filename);
	for (auto& car : getAllCars()) {
		carOutput << car.getNr_inm() << "," << car.getProducator() << ",";
		carOutput << car.getModel() << "," << car.getTip() << endl;
	}
	carOutput.close();
}

void CarRepositoryFile::store(const Masina& m) {

	CarRepository::store(m);
	saveToFile();
}

void testAddRepo() {
	CarRepository testRepo;
	Masina m1{ "VN55FLO", "Suzuki","Vitara","suv" };
	testRepo.store(m1);
	assert(testRepo.getAllCars().size() == 1);

	Masina m2{ "IF77BUR", "Lamborghini", "Huracan", "supersport" };
	Masina m3{ "VN55FLO", "Suzuki","Vitara","suv" };
	try {
		testRepo.store(m3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}


}
void testFindRepo() {
	CarRepository testRepo;

	Masina m1{ "AB29ION", "Audi", "A5", "sedan" };
	Masina m2{ "HD23MIK","Volkswagen", "Passat", "sedan" };
	Masina m3{ "SV48BIN","Aston Martin", "DBS", "supersport" };
	testRepo.store(m1);
	testRepo.store(m2);

	assert(testRepo.exists(m1));
	assert(!testRepo.exists(m3));

	auto foundCar = testRepo.find("AB29ION");
	assert(foundCar.getProducator() == "Audi");
	assert(foundCar.getModel() == "A5");
	assert(foundCar.getTip() == "sedan");


	try {
		testRepo.find("B100BOS");
		assert(false);
	}
	catch (RepoException& ve) {
		assert(ve.getErrorMessage() == "Masina cu numarul de inmatriculare B100BOS nu exista in lista!");
	}
}

void testeRepo() {
	testAddRepo();
	testFindRepo();
}