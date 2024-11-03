#pragma once
#include "services.h"
#include <qwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlistwidget.h>

class GUI : 
	public QWidget {
	Q_OBJECT
private:
	std::vector<Tutorial> tutorials;

public:
	GUI(const std::vector<Tutorial>& tutorials, QWidget* parent = 0);

	void initGUI();
private:
	Services& service;
	QListWidget* tutorialsList;
	QLineEdit* titleLineEdit, * presenterNameLineEdit, * durationLineEdit, *nrLikesLineEdit, *linkLineEdit;
	QPushButton* addButton, * deleteButton;
	void populateTutorialsList();
	void connectSignalsAndSlots();

	void listItemChanged();
	int getSelectedIndex();
signals:
	void mySignal();
};