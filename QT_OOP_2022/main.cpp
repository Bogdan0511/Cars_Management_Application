#include "QT_OOP_2022.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>

using std::cout;
using std::endl;

void testAll() {
	testeDomain();
	cout << "Finished domain tests." << endl;
	testeRepo();
	cout << "Finished repo tests." << endl;
	testeService();
	cout << "Finished service tests." << endl;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	CarRepositoryFile repoFile{ "fisier_input.txt" };
	CarValidator val;
	CarStore srv{ repoFile, val };
	CarStoreGUI gui{ srv };
	gui.show();
    return a.exec();
}
