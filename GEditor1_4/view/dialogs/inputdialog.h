#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include "../../templates/getset.h"
#include "../oinspector.h"

#include <QComboBox>
#include <QDialog>
#include <QLineEdit>

// class --------------------------------------------------------------------------------

//! InputDialog class.
/*!
 * \brief A Dialog to add new objects to the scene.
 */
class InputDialog : public QDialog {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param data the list that stores the form data
         * \param oi the object inspector
         * \param parent the parent widget
         */
        explicit InputDialog(QStringList *data, OInspector *oi, QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Filters the formular data and stores it.
         */
        void setData();

    // --------------------------------------------------------------------------------
    private:

        /*!< An instance of object inspector. */
        OInspector *_oi;

        /*!< The combobox in the dialog formular. */
        GETSET(QComboBox*, cBox, CBox)

        /*!< Is a list that stores all dialog formular data. */
        GETSET(QStringList*, data, Data)

        /*!< The input field in the dialog formular. */
        GETSET(QLineEdit*, lEdit, LEdit)

        /*!< The current selected value of combobox in the dialog formular. */
        GETSET(int, selected, Selected)

};

#endif // INPUTDIALOG_H
