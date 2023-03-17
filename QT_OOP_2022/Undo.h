#pragma once
#include "Domain.h"
#include "Repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Masina m;
	CarRepository& repo;
public:
	UndoAdauga(CarRepository& rep, const Masina& mas) : repo{ rep }, m{ mas } {}
	void doUndo() override {
		repo.sterge(m);
	}
};

class UndoSterge : public ActiuneUndo {
	Masina m;
	CarRepository& repo;
public:
	UndoSterge(CarRepository& rep, const Masina& mas) : repo{ rep }, m{ mas } {}
	void doUndo() override {
		repo.store(m);
	}
};
