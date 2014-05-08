#include "aboutdialog.h"

#include <QDialogButtonBox>
#include <QLabel>
#include <QTabWidget>
#include <QTextCodec>
#include <QTextEdit>
#include <QVBoxLayout>

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent){

    setFixedSize(500, 400);
    setLayoutDirection(Qt::LeftToRight);
    setWindowTitle("About");
    setWindowIcon(QIcon(":/images/images/icons/about.ico"));
    setWindowFlags(windowFlags() & (~Qt::WindowContextHelpButtonHint));

    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setCurrentIndex(0);
    tabWidget->addTab(initAboutTab(), "About");
    tabWidget->addTab(initCreditsTab(), "Credits");
    tabWidget->addTab(initLicenseTab(), "License");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Close);

    //layout
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(tabWidget);
    vlayout->addWidget(buttonBox);
    setLayout(vlayout);

    connect(buttonBox, SIGNAL(rejected()), this, SLOT(close()));
}


// --------------------------------------------------------------------------------------
// private ------------------------------------------------------------------------------


QWidget* AboutDialog::initAboutTab(){

    QWidget *aboutTabWidget = new QWidget(this);

        QString desc = tr("GEditor is a cross-platform game editor, using Qt5 for the editor and engine.");
        QString copyright = "Copyright &copy; 2014, Christian Kusan";
        QString version = "GEditor 1.3 alpha";

        QLayout* aboutTabLayout = new QVBoxLayout(aboutTabWidget);
        QLabel* label = new QLabel(QString("<p><b>%1</b></p><p>%2</p><p>%3</p>").arg(version).arg(desc).arg(copyright), aboutTabWidget);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

    aboutTabLayout->addWidget(label);
    aboutTabWidget->setLayout(aboutTabLayout);

    return aboutTabWidget;
}

QWidget* AboutDialog::initCreditsTab(){

    QGridLayout *gl = new QGridLayout(this);
    QWidget *creditsTabWidget = new QWidget(this);

        QStringList thanksTo;
        thanksTo    << "Main Developer:"
                    << "Christian Kusan <ckusan@live.de>"
                    << ""
                    << "Thanks to:"
                    << "Qt5 Libraries <http://qt-project.org/>";

        QTextEdit *creditsEdit = new QTextEdit(creditsTabWidget);
        creditsEdit->setReadOnly(true);
        creditsEdit->setText(thanksTo.join("\n"));

    gl->addWidget(creditsEdit, 0, 0);
    creditsTabWidget->setLayout(gl);
    return creditsTabWidget;
}

QWidget* AboutDialog::initLicenseTab(){

    QGridLayout *gl = new QGridLayout(this);
    QWidget *licenseTabWidget = new QWidget(this);

        QStringList license;
        license << "This program is free software: you can redistribute it and/or modify"
                << "it under the terms of the GNU General Public License as published by"
                << "the Free Software Foundation, either version 3 of the License, or"
                << "(at your option) any later version."
                << ""
                << "This program is distributed in the hope that it will be useful,"
                << "but WITHOUT ANY WARRANTY; without even the implied warranty of"
                << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
                << "GNU General Public License for more details."
                << ""
                << "You should have received a copy of the GNU General Public License"
                << "along with this program.  If not, see <http://www.gnu.org/licenses/>.";

        QTextEdit *licenseEdit = new QTextEdit(licenseTabWidget);
        licenseEdit->setReadOnly(true);
        licenseEdit->setText(license.join("\n"));

    gl->addWidget(licenseEdit, 0, 0);
    licenseTabWidget->setLayout(gl);
    return licenseTabWidget;
}
