#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "Service.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>

using std::to_string;
using std::set;
using std::vector;

class CarWashGUI : public QWidget, public Observer {
private:
	CarStore& srv;
	QHBoxLayout* lyMain;
	QListWidget* carList;

	QLabel* lblNrInm;
	QLabel* lblProducator;
	QLineEdit* editNrInm;
	QLineEdit* editProducator;

	QPushButton* btnAdd;
	QPushButton* btnGenerate;
	QPushButton* btnEmpty;
	QPushButton* btnClose;
	QPushButton* btnLabelWindow;
	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	QLineEdit* editNoSlider;
	QLabel* lblSlider;
	QSlider* sliderGenerate;

	QWidget* widgetDynamic;
	QVBoxLayout* lyBtnDynamic;
	void initGUI();
	void connectSignalsSlots();

	void reloadCarWash();
	void addToCarWash();

	//ar trebui ca aceasta metoda sa fie aici sau in service?
	set<string> getProd(const vector<Masina>& washCars);
	void reloadDynamicButtons();
	void update() override {
		reloadCarWash();
	}

public:
	CarWashGUI(CarStore& carStore) : srv{ carStore } {
		initGUI();
		connectSignalsSlots();
	}

};
class CarWashGUILabel :public QWidget, public Observer {
private:
	Car_Wash& p;
	QLabel* lblNoCars;
	QLineEdit* editNoCars;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		lblNoCars = new QLabel{ "Numar de masini:" };
		editNoCars = new QLineEdit{};
		ly->addWidget(lblNoCars);
		ly->addWidget(editNoCars);
		setAttribute(Qt::WA_DeleteOnClose);
		p.addObserver(this);
	};
	void update() override {
		this->editNoCars->setText(QString::number(p.getAllWashCars().size()));
	};
	~CarWashGUILabel() {
		p.removeObserver(this);
	}

public:
	CarWashGUILabel(Car_Wash& wash) :p{ wash } {
		initGUI();
	};

};
class CarWashGUITable :public QWidget, public Observer {
private:
	Car_Wash& p;
	QTableWidget* table;
	QPushButton* btnEmpty;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout{};
		this->setLayout(ly);
		table = new QTableWidget{};
		btnEmpty = new QPushButton{ "Goleste spalatoria" };
		ly->addWidget(table);
		ly->addWidget(btnEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		p.addObserver(this);
	};
	void reloadTableData(const vector<Masina>& cars) {
		this->table->setColumnCount(4);
		this->table->setRowCount(static_cast<int>(cars.size()));
		for (int i = 0; i < cars.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(cars[i].getNr_inm())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(cars[i].getProducator())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(cars[i].getModel())));
			table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(cars[i].getTip())));
		}

	};

	void connectSignalsSlots() {
		p.addObserver(this);

		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			p.emptyCarWash();
			reloadTableData(p.getAllWashCars());
			});
	}


public:
	CarWashGUITable(Car_Wash& wash) :p{ wash } {
		initGUI();
		connectSignalsSlots();
	};

	void update() override {
		this->reloadTableData(p.getAllWashCars());
	}
	~CarWashGUITable() {
		p.removeObserver(this);
	}

};

class CarWashGUIDraw :public QWidget, public Observer {
private:
	Car_Wash& wash;
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 10;
		int y = 10;
		int w = 10;
		for (auto car : wash.getAllWashCars()) {
			//p.drawRect(x, y, 10, song.getDurata() * 10);
			//x = rand() % 400 + 1;
			//y = rand() % 400 + 1;
			//qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 732, 720);
			QImage image("sun.jpg");

			p.drawRect(x,y,w,car.getModel().size() * 10);

			x += 40;

		}
	}

	void update() override {
		repaint();
	};
	~CarWashGUIDraw() {
		wash.removeObserver(this);
	}

public:
	CarWashGUIDraw(Car_Wash& wash) :wash{ wash } {
		wash.addObserver(this);
		update();
	};
};
