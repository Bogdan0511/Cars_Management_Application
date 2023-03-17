#include "Spalatorie.h"

using std::shuffle;

void Car_Wash::addCarToWash(const Masina& m) {
	this->washing_queue.push_back(m);
}

void Car_Wash::emptyCarWash() {
	this->washing_queue.clear();
}

void Car_Wash::addRandomCars(vector<Masina> originalCars, int howMany) {
	shuffle(originalCars.begin(), originalCars.end(), std::default_random_engine(std::random_device{}())); //amestecam vectorul
	while (washing_queue.size() < howMany && originalCars.size() > 0) {
		washing_queue.push_back(originalCars.back());
		originalCars.pop_back();
	}
}

const vector<Masina>& Car_Wash::getAllWashCars() {
	return this->washing_queue;
}