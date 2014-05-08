#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

class AboutDialog : public QDialog {

        Q_OBJECT

    public:
        AboutDialog(QWidget *parent = 0);

    private:
        QWidget *initAboutTab();

        QWidget *initCreditsTab();

        QWidget *initLicenseTab();
};

#endif // ABOUTDIALOG_H
