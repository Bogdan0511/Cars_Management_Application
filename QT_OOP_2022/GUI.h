#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "Service.h"
#include "SpalatorieGUI.h"

using std::vector;
using std::string;
class CarStoreGUI : public QWidget {
private:

	CarStore& srv;
	CarWashGUI washWindow{ srv };
	QLabel* lblNrInm = new QLabel{ "Nr. inmatriculare masina:" };
	QLabel* lblProd = new QLabel{ "Producator masina:" };
	QLabel* lblModel = new QLabel{ "Model masina:" };
	QLabel* lblTip = new QLabel{ "Tip masina:" };

	QLineEdit* editNrInm;
	QLineEdit* editProd;
	QLineEdit* editModel;
	QLineEdit* editTip;

	QPushButton* btnAddCar;

	QGroupBox* groupBox = new QGroupBox(tr("Tip sortare"));

	QRadioButton* radioSrtProdModel = new QRadioButton(QString::fromStdString("Producator+Model"));
	QRadioButton* radioSrtNrInm = new QRadioButton(QString::fromStdString("Nr.Inmatriculare"));
	QPushButton* btnSortCars;

	QLabel* lblFilterCriteria = new QLabel{ "Producator dupa care se filtreaza:" };
	QLineEdit* editFilterProd;
	QPushButton* btnFilterCars;

	QPushButton* btnReloadData;

	QTableWidget* tableCars;

	QPushButton* btnWash;
	QPushButton* btnModel;

	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadCarList(vector<Masina> cars);
public:
	CarStoreGUI(CarStore& carSrv) : srv{ carSrv } {
		initializeGUIComponents();
		connectSignalsSlots();
		reloadCarList(srv.getAllCars());
	}
	void guiAddCar();

};
