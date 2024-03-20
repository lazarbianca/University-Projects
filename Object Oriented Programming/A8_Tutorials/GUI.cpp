#include "GUI.h"
#include <qformlayout.h>
#include <qlabel.h>
#include <string>
#include "Validator.h"
#include <qmessagebox.h>


GUI::GUI(const std::vector<Tutorial>& tutorials, QWidget* parent):
	QWidget{ parent }, tutorials{ tutorials }
{
	this->initGUI();
	this->populateTutorialsList();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
	QHBoxLayout* layout = new QHBoxLayout{ this };
	tutorialsList = new QListWidget{};

	layout->addWidget(tutorialsList);

	QVBoxLayout* tutorialsDataLayout = new QVBoxLayout{};

	layout->addLayout(tutorialsDataLayout);

	QFormLayout* tutorialInfoLayout = new QFormLayout{};
	QLabel* nameLabel = new QLabel{ "&Name" };   
	titleLineEdit = new QLineEdit{};

}

void GUI::populateTutorialsList()
{
	tutorialsList->clear();
	for (Tutorial& currentTutorial : service.getAllDataService())
	{
		//songsListWidget->addItem(QString::fromStdString(currentSong.getArtist() + "-" + currentSong.getTitle()));
		this->tutorialsList->addItem(QString::fromStdString(currentTutorial.toString()));
	}
}

void GUI::connectSignalsAndSlots()
{
}

void GUI::listItemChanged()
{
}

int GUI::getSelectedIndex()
{
	return 0;
}


