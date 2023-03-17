#include "GUI.h"

void CarStoreGUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu masini

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain);


	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editNrInm = new QLineEdit;
	editProd = new QLineEdit;
	editModel = new QLineEdit;
	editTip = new QLineEdit;

	lyForm->addRow(lblNrInm, editNrInm);
	lyForm->addRow(lblProd, editProd);
	lyForm->addRow(lblModel, editModel);
	lyForm->addRow(lblTip, editTip);
	btnAddCar = new QPushButton("Adauga masina");
	lyForm->addWidget(btnAddCar);

	//adaugam toate componentele legate de adaugare masina
	//in layout-ul care corespunde partii din stanga a ferestrei
	lyLeft->addWidget(form);


	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare

	QVBoxLayout* lyRadioBox = new QVBoxLayout;
	this->groupBox->setLayout(lyRadioBox);
	lyRadioBox->addWidget(radioSrtProdModel);
	lyRadioBox->addWidget(radioSrtNrInm);

	btnSortCars = new QPushButton("Sorteaza masinile");
	lyRadioBox->addWidget(btnSortCars);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupBox);

	//cream un form pentru filtrarea dupa producator 
	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterProd = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterProd);
	btnFilterCars = new QPushButton("Filtreaza masinile dupa producator");
	lyFormFilter->addWidget(btnFilterCars);

	lyLeft->addWidget(formFilter);

	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate masinile in tabel, in ordinea initiala din fisier
	btnReloadData = new QPushButton("Reload data");
	lyLeft->addWidget(btnReloadData);


	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableCars = new QTableWidget{ noLines, noColumns };

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Nr. inmatriculare" << "Producator" << "Model" << "Tip";
	this->tableCars->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableCars->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	btnWash = new QPushButton{ "Deschide spalatorie" };
	lyLeft->addWidget(btnWash);
	lyLeft->addWidget(btnModel);
	lyRight->addWidget(tableCars);

	lyMain->addWidget(left);
	lyMain->addWidget(right);

}
void CarStoreGUI::reloadCarList(vector<Masina> cars) {
	this->tableCars->clearContents();
	this->tableCars->setRowCount(cars.size());

	int lineNumber = 0;
	for (auto& car : cars) {
		this->tableCars->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(car.getNr_inm())));
		this->tableCars->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(car.getProducator())));
		this->tableCars->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
		this->tableCars->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(car.getTip())));
		lineNumber++;
	}
}

void CarStoreGUI::connectSignalsSlots() {
	QObject::connect(btnAddCar, &QPushButton::clicked, this, &CarStoreGUI::guiAddCar);

	QObject::connect(btnSortCars, &QPushButton::clicked, [&]() {
		if (this->radioSrtProdModel->isChecked())
			this->reloadCarList(srv.sortByProducator());
		else if (this->radioSrtNrInm->isChecked())
			this->reloadCarList(srv.sortByNr_inm());
		});

	QObject::connect(btnFilterCars, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterProd->text().toStdString();
		this->reloadCarList(srv.filtrareProducator(filterC));
		});

	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
		this->reloadCarList(srv.getAllCars());
		});

	QObject::connect(btnWash, &QPushButton::clicked, [&]() {
		washWindow.show();
		});
}


void CarStoreGUI::guiAddCar() {
	try {
		//preluare detalii din QLineEdit-uri
		string nr_inm = editNrInm->text().toStdString();
		string prod = editProd->text().toStdString();
		string model = editModel->text().toStdString();
		string tip = editTip->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editNrInm->clear();
		editProd->clear();
		editModel->clear();
		editTip->clear();

		this->srv.addCar(nr_inm, prod, model, tip);
		this->reloadCarList(this->srv.getAllCars());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}


}