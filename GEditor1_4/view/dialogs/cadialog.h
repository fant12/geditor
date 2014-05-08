#ifndef CADIALOG_H
#define CADIALOG_H

#include <QDialog>

class QComboBox;
class QVBoxLayout;

class CADialog : public QDialog {

        Q_OBJECT

    public:
        CADialog(QWidget *parent = 0);

    private slots:
        void addLineEdit();

    private:
        QVBoxLayout *_dLayout;

        QList<QComboBox *> *_numObjects;

};

#endif // CADIALOG_H
