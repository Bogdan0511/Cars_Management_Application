#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qtablewidget.h>
#include "Service.h"
#include "Domain.h"
#include <vector>
#include "TableModel.h"

class CarGuiModele : public QWidget {
private:
	CarStore& ctr;
	MyTableModel* model;
	QLabel* lblCate = new QLabel{ "Cate:" };
	QListView* lstV;

	QTableView* tblV = new QTableView;

	QPushButton* btnSortByNrInm;
	QPushButton* btnSortByProducator;

	QLineEdit* txtNrInm;
	QLineEdit* txtProducator;
	QLineEdit* txtModel;
	QLineEdit* txtTip;
	QPushButton* btnAdd;


	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector<Masina> cars);
	void addNewCar();
public:
	CarGuiModele(CarStore& ctr) :ctr{ ctr } {
		initGUICmps();
		model = new MyTableModel{ ctr.getAllCars() };
		lstV->setModel(model);
		tblV->setModel(model);
		connectSignalsSlots();
	}

};