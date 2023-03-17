#pragma once
#include "Domain.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"

using std::vector;

class Car_Wash: public Observable {
private:
	vector<Masina> washing_queue;
public:
	Car_Wash() = default;
	/*
	Adaugam o masina la spalatorie
	param: m, masina care se adauga (Masina)

	post: masina se va afla in spalatorie
	*/
	void addCarToWash(const Masina& m);

	/*
	Elimina toate masinile din spalatorie

	post: spalatoria este goala
	*/
	void emptyCarWash();

	/*
	Adauga un numar aleatoriu de masini in spalatorie
	param: originalCars, masinile din care se alege (vector<Masina>)
	param: howMany, cate masini se adauga (int)

	post: masinile sunt adaugate in spalatorie
	*/
	void addRandomCars(vector<Masina> originalCars, int howMany);

	/*
	Returneaza un vector care contine toate masinile din spalatorie
	*/
	const vector<Masina>& getAllWashCars();
};