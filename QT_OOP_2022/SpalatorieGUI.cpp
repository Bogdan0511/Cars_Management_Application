#include "SpalatorieGUI.h"

void CarWashGUI::initGUI() {
	lyMain = new QHBoxLayout{};
	this->setLayout(lyMain);

	QWidget* leftSide = new QWidget{};
	QVBoxLayout* lyLeft = new QVBoxLayout{};
	leftSide->setLayout(lyLeft);

	QWidget* formW = new QWidget{};
	QFormLayout* lyEdits = new QFormLayout{};
	lblNrInm = new QLabel{ "Nr. inmatriculare" };
	lblProducator = new QLabel{ "Producator" };
	editNrInm = new QLineEdit{};
	editProducator = new QLineEdit{};

	lblSlider = new QLabel{ "Nr. masini de generat" };
	editNoSlider = new QLineEdit{};
	lyEdits->addRow(lblNrInm, editNrInm);
	lyEdits->addRow(lblProducator, editProducator);
	lyEdits->addRow(lblSlider, editNoSlider);
	formW->setLayout(lyEdits);


	btnAdd = new QPushButton{ "Adauga in spalatorie" };
	btnGenerate = new QPushButton{ "Genereaza random" };
	btnEmpty = new QPushButton{ "Goleste spalatoria" };
	btnClose = new QPushButton{ "Inchide" };

	btnLabelWindow = new QPushButton{ "Fereastra label" };
	btnLabelWindow->setStyleSheet("background-color: cyan");

	btnTableWindow = new QPushButton{ "Fereastra spalatorie tabel" };
	btnTableWindow->setStyleSheet("background-color: magenta");

	btnDrawWindow = new QPushButton{ "Fereastra desen" };
	btnDrawWindow->setStyleSheet("background-color: yellow");


	sliderGenerate = new QSlider{};
	sliderGenerate->setMinimum(1);
	sliderGenerate->setMaximum(static_cast<int>(srv.getAllCars().size()));

	lyLeft->addWidget(formW);
	lyLeft->addWidget(btnAdd);
	lyLeft->addWidget(btnGenerate);
	lyLeft->addWidget(btnEmpty);
	lyLeft->addWidget(btnClose);
	lyLeft->addWidget(btnLabelWindow);
	lyLeft->addWidget(btnTableWindow);
	lyLeft->addWidget(btnDrawWindow);

	QWidget* rightSide = new QWidget{};
	QVBoxLayout* lyRight = new QVBoxLayout{};
	rightSide->setLayout(lyRight);

	carList = new QListWidget{};
	carList->setFixedWidth(320);
	carList->setSelectionMode(QAbstractItemView::SingleSelection);

	lyRight->addWidget(carList);

	widgetDynamic = new QWidget{};
	lyBtnDynamic = new QVBoxLayout{};
	widgetDynamic->setLayout(lyBtnDynamic);
	reloadDynamicButtons();

	lyMain->addWidget(leftSide);
	lyMain->addWidget(sliderGenerate);
	lyMain->addWidget(rightSide);
	lyMain->addWidget(widgetDynamic);


}
set<string> CarWashGUI::getProd(const vector<Masina>& washCars) {
	set<string> prod;

	for (const auto& m : washCars) {
		prod.insert(m.getProducator());
	}
	return prod;
}
int howManyWithProd(const vector<Masina>& cars, string prod) {
	int noCars = count_if(cars.begin(), cars.end(), [&](Masina m) {
		return m.getProducator() == prod; });
	return noCars;
}
void clearLayout(QLayout* layout) {
	if (layout == NULL)
		return;
	QLayoutItem* item;
	while ((item = layout->takeAt(0))) {
		if (item->layout()) {
			clearLayout(item->layout());
			delete item->layout();
		}
		if (item->widget()) {
			delete item->widget();
		}
		delete item;
	}
}
void CarWashGUI::reloadDynamicButtons() {
	clearLayout(this->lyBtnDynamic);
	const vector<Masina>& washCars = this->srv.getWashCars();
	set<string> prod = this->getProd(washCars);

	for (string p : prod) {
		QPushButton* btn = new QPushButton{ QString::fromStdString(p) };
		lyBtnDynamic->addWidget(btn);
		int howMany = howManyWithProd(washCars, p);
		//mult mai eficient: puteam sa folosim un dictionar cu cheia = gen, valoare=nr masini
		//->o singura parcurgere a listei de melodii
		QObject::connect(btn, &QPushButton::clicked, [p, howMany]() {
			QMessageBox::information(nullptr, "Info", QString::fromStdString("Masini cu producatorul " + p + " : " + to_string(howMany)));

			});
	}

}
void CarWashGUI::connectSignalsSlots() {
	srv.getWash().addObserver(this);
	QObject::connect(btnAdd, &QPushButton::clicked, this, &CarWashGUI::addToCarWash);
	QObject::connect(sliderGenerate, &QSlider::sliderReleased, [&]() {
		qDebug() << sliderGenerate->value();
		});
	QObject::connect(btnGenerate, &QPushButton::clicked, [&]() {
		int noSongs = this->sliderGenerate->value();
		editNoSlider->setText(QString::number(noSongs));
		qDebug() << "This many cars to add:" << noSongs;
		srv.addRandomToWash(noSongs);
		this->reloadCarWash();
		});
	QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
		srv.emptyWash();
		this->reloadCarWash();
		});
	QObject::connect(btnClose, &QPushButton::clicked, this, &CarWashGUI::close);

	QObject::connect(btnLabelWindow, &QPushButton::clicked, this, [&]() {
		auto labelWindow = new CarWashGUILabel{ srv.getWash() };
		labelWindow->show();
		});
	QObject::connect(btnTableWindow, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new CarWashGUITable{ srv.getWash() };
		tableWindow->show();
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new CarWashGUIDraw{ srv.getWash() };
		drawWindow->show();
		});

	QObject::connect(carList, &QListWidget::itemSelectionChanged, [&]() {
		auto selItms = carList->selectedItems();
		for (auto item : selItms) {
			qDebug() << item->text();
			item->setBackground(Qt::green); // sets green background
		}

		});




}


void CarWashGUI::reloadCarWash() {

	this->carList->clear();

	const vector<Masina>& cars = srv.getWashCars();
	for (auto& car : cars) {
		QString currentItem = QString::fromStdString(car.getNr_inm() + "\t" + car.getProducator() + "\t" + car.getModel() + "\t" + car.getTip());
		this->carList->addItem(currentItem);
	}
	reloadDynamicButtons();

}


void CarWashGUI::addToCarWash() {
	try {
		string nrinm = editNrInm->text().toStdString();
		string prod = editProducator->text().toStdString();

		editNrInm->clear();
		editProducator->clear();


		this->srv.addToWash(nrinm);
		this->reloadCarWash();

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