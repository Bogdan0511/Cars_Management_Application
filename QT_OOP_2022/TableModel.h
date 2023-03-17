#pragma once
#include <QAbstractTableModel>
#include "Domain.h"
#include <vector>
#include <qdebug.h>
#include <QBrush>
class MyTableModel :public QAbstractTableModel {
	std::vector<Masina> cars;
public:
	MyTableModel(const std::vector<Masina>& masini) :cars{ masini } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return cars.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		if (role == Qt::ForegroundRole) {
			Masina p = cars[index.row()];
			if (p.getProducator().size() > 0) {
				return QBrush{ Qt::red };
			}
		}
		if (role == Qt::DisplayRole) {

			Masina p = cars[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getNr_inm());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getProducator());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getModel());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.getTip());
			}
		}

		return QVariant{};
	}

	void setMasina(const std::vector<Masina>& cars) {
		this->cars = cars;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}
};