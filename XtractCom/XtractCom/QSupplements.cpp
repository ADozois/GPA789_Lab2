#include "QSupplements.h"
#include <qpushbutton.h>
#include <QGridLayout>
#include <Qapplication>
#include <qmessagebox.h>

QSupplements::QSupplements(QWidget * parent)
	:QWidget(parent)
{

//*********************Bouton pour XtractC
	mButtonXTractC = new QPushButton(QString("À propos de XtractC"));
	connect(mButtonXTractC, &QPushButton::clicked, this, &QSupplements::showAboutXtractC);

//*********************Boutton pour le langage C++
	mButtonCpp = new QPushButton(QString("À propos du langage C++"));	
	QPixmap cppIcon{ ":/XtractCom/IconCpp" };
	QPixmap cppIcon2= cppIcon.scaled(100, 100, Qt::IgnoreAspectRatio);
	QString titreCppWindow{ "À propos du langage C++" };
	QString messageCpp{ R"-%-(C++ is a general-purpose programming language. It has imperative, object-oriented and generic programming features, while also providing facilities for low-level memory manipulation. 

It was designed with a bias toward system programming and embedded, resource - constrained and large systems, with performance, efficiency and flexibility of use as its design highlights. C++ has also been found useful in many other contexts, with key strengths being software infrastructure and resource - constrained applications, including desktop applications, servers(e.g.e - commerce, web search or SQL servers), and performance - critical applications(e.g.telephone switches or space probes). C++ is a compiled language, with implementations of it available on many platforms. Many vendors provide C++ compilers, including the Free Software Foundation, Microsoft, Intel, and IBM.

C++ is standardized by the International Organization for Standardization(ISO), with the latest standard version ratified and published by ISO in December 2014 as ISO / IEC 14882:2014 (informally known as C++14). The C++ programming language was initially standardized in 1998 as ISO / IEC 14882 : 1998, which was then amended by the C++03, ISO / IEC 14882 : 2003, standard.The current C++14 standard supersedes these and C++11, with new features and an enlarged standard library. Before the initial standardization in 1998, C++ was developed by Bjarne Stroustrup at Bell Labs since 1979, as an extension of the C language as he wanted an efficient and flexible language similar to C, which also provided high - level features for program organization. The C++17 standard is due in July 2017, with the draft largely implemented by some compilers already, and C++20 is the next planned standard thereafter.

Many other programming languages have been influenced by C++, including C#, D, Java, and newer versions of C

Source principale: https://en.wikipedia.org/wiki/C%2B%2B)-%-" };
	mMessageCpp = new QMessageBox(QMessageBox::NoIcon, titreCppWindow, messageCpp);
	mMessageCpp->setIconPixmap(cppIcon2);
	mMessageCpp->setWindowIcon(QIcon(":/XtractCom/Icon"));
	
	connect(mButtonCpp, &QPushButton::clicked, mMessageCpp, &QMessageBox::exec);


//*********************Boutton pour Qt
	mButtonQt = new QPushButton(QString("À propos de Qt"));
	connect(mButtonQt, &QPushButton::clicked, this, &QApplication::aboutQt);

	QGridLayout * gridLayout = new QGridLayout;
	gridLayout->addWidget(mButtonXTractC, 0, 0);
	gridLayout->addWidget(mButtonCpp, 1, 0);
	gridLayout->addWidget(mButtonQt, 2, 0);

	gridLayout->setAlignment(Qt::AlignRight|Qt::AlignBottom);

	setLayout(gridLayout);

}



void QSupplements::showAboutXtractC() {
	QString titreXtractCWindow{ "À propos de XtractC" };
	QString messageXtractC{ R"-%-(XtractC est un logiciel qui permet d'extraire les commentaire de style C et C++ du code d'un programme C ou C++

Ce programme est réalisé par:
	-Antoine Dozois
	-Guillaume Chabot-Nobert

Dans le cadre du cours:
	-GPA789 - Analyse et conception orientées objet
	-Laboratoire 2

Version 1.0)-%-" };


	QMessageBox::about(this, titreXtractCWindow, messageXtractC);


}