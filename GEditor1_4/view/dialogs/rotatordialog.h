#ifndef ROTATORDIALOG_H
#define ROTATORDIALOG_H

#include <QDial>
#include <QDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSpinBox>

class QGraphicsItem;

class RotatorDialog : public QDialog {

        Q_OBJECT

    public:
        explicit RotatorDialog(QWidget *parent = 0);

    private slots:

        /*!
         * \brief Changes the item rotation.
         * \param value the value
         */
        void changeItemRotation(int value);

    private:

        QDial *_dial;

        QGraphicsItem *_item;

        QSpinBox *_spin;

};

#endif // ROTATORDIALOG_H
