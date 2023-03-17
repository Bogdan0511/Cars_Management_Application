#include "Domain.h"
#include <assert.h>
string Masina::getNr_inm() const {
	return this->nr_inm;
}
string Masina::getProducator() const {
	return this->producator;
}
string Masina::getModel() const {
	return this->model;
}
string Masina::getTip() const {
	return this->tip;
}

void Masina::setNr_inm(string nrNou) {
	this->nr_inm = nrNou;
}
void Masina::setProducator(string producatorNou) {
	this->producator = producatorNou;
}
void Masina::setModel(string modelNou) {
	this->model = modelNou;
}
void Masina::setTip(string tipNou) {
	this->tip = tipNou;
}


bool cmpProducatorMasina(const Masina& m1, const Masina& m2) {
	if (m1.getProducator() == m2.getProducator())
		return m1.getModel() < m2.getModel();
	else
		return m1.getProducator() < m2.getProducator();
}

bool cmpNr_inmMasina(const Masina& m1, const Masina& m2) {
	return m1.getNr_inm() < m2.getNr_inm();
}

void testGetSet() {
	Masina m1{ "BH30STE", "Mercedes-Benz","S 63", "sedan" };
	assert(m1.getNr_inm() == "BH30STE");
	assert(m1.getProducator() == "Mercedes-Benz");
	assert(m1.getModel() == "S 63");
	assert(m1.getTip() == "sedan");

	Masina m2{ "CJ10OOP", "BMW", "M5", "sport" };
	assert(m2.getNr_inm() == "CJ10OOP");
	assert(m2.getProducator() == "BMW");
	assert(m2.getModel() == "M5");
	assert(m2.getTip() == "sport");

	m2.setNr_inm("BR33ROK");
	m2.setProducator("Ford");
	m2.setModel("Focus");
	m2.setTip("combi");

	assert(m2.getNr_inm() == "BR33ROK");
	assert(m2.getProducator() == "Ford");
	assert(m2.getModel() == "Focus");
	assert(m2.getTip() == "combi");



}

void testeDomain() {
	testGetSet();
}