#include "ModelGUI.h"
#include "Domain.h"
#include <QtWidgets/QHBoxLayout>
/*#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include "TableModel.h"

void CarGuiModele::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);

	vl->addWidget(lblCate);

	lstV = new QListView;
	lstV->setUniformItemSizes(true);
	vl->addWidget(lstV);


	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByNrInm = new QPushButton("Sortare nr. inmatriculare");
	lyBtnsDr->addWidget(btnSortByNrInm);

	btnSortByProducator = new QPushButton("Sortare producator");
	lyBtnsDr->addWidget(btnSortByProducator);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	QWidget* widDreapta2 = new QWidget;
	QVBoxLayout* lyDreapta = new QVBoxLayout;
	widDreapta2->setLayout(lyDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtNrInm = new QLineEdit;
	formLDetalii->addRow(new QLabel("Nr. inmatriculare:"), txtNrInm);
	txtProducator = new QLineEdit;
	formLDetalii->addRow(new QLabel("Producator:"), txtProducator);
	txtModel = new QLineEdit;
	formLDetalii->addRow(new QLabel("Model:"), txtModel);
	txtTip = new QLineEdit;
	formLDetalii->addRow(new QLabel("Tip:"), txtTip);

	btnAdd = new QPushButton("Adauga masina");
	formLDetalii->addWidget(btnAdd);
	lyDreapta->addWidget(widDetalii);


	ly->addWidget(widDreapta2);

	ly->addWidget(tblV);

}


void CarGuiModele::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByNrInm, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByNr_inm());
		});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByProducator, &QPushButton::clicked, [&]() {
		reloadList(ctr.sortByProducator());
		});

	QObject::connect(btnAdd, &QPushButton::clicked, this, &CarGuiModele::addNewCar);


	//selectia in tabel
	QObject::connect(tblV->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tblV->selectionModel()->selectedIndexes().isEmpty()) {
			txtNrInm->setText("");
			txtProducator->setText("");
			txtModel->setText("");
			txtTip->setText("");
			return;
		}
		int selRow = tblV->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tblV->model()->index(selRow, 0);
		auto cel0Value = tblV->model()->data(cel0Index, Qt::DisplayRole).toString();
		txtNrInm->setText(cel0Value);
		auto cel1Index = tblV->model()->index(selRow, 1);
		auto cel1Value = tblV->model()->data(cel1Index, Qt::DisplayRole).toString();
		txtProducator->setText(cel1Value);
		auto cel2Index = tblV->model()->index(selRow, 2);
		auto cel2Value = tblV->model()->data(cel2Index, Qt::DisplayRole).toString();
		txtModel->setText(cel2Value);
		auto cel3Index = tblV->model()->index(selRow, 3);
		auto cel3Value = tblV->model()->data(cel3Index, Qt::DisplayRole).toString();
		txtTip->setText(cel3Value);
		});
}

void CarGuiModele::addNewCar() {

	ctr.addCar(txtNrInm->text().toStdString(), txtProducator->text().toStdString(), txtModel->text().toStdString(), txtTip->text().toStdString());
	reloadList(ctr.getAllCars());


}
void CarGuiModele::reloadList(std::vector<Masina> cars) {
	lblCate->setText(QString{ "Cate:" } + QString::number(cars.size()));
	model->setMasina(cars);
}*/