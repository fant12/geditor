#ifndef PROJECTDIALOG_H
#define PROJECTDIALOG_H

#include "../../control/manager.h"

#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>

// class --------------------------------------------------------------------------------

//! ProjectDialog class.
/*!
 * \brief The ProjectDialog class is a dialog window as preparation
 * or configuration box.
 */
class ProjectDialog : public QDialog {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief ProjectDialog the default constructor.
         * \param parent the parent widget
         */
        explicit ProjectDialog(QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Shows a file dialog.
         */
        void iconSearch();

        /*!
         * \brief Shows a file dialog to choosing a directory.
         */
        void locationSearch();

        /*!
         * \brief Configurates and prepares the game.
         */
        void prepare();

        /*!
         * \brief Stores all configurations in settings file.
         */
        void save();

    // --------------------------------------------------------------------------------
    private:

        /*!< Print formular errors on dialog screen. */
        QLabel *_error;

        /*!< Input field for project author. */
        QLineEdit *_projAutorField;

        /*!< Input field for icon image url. */
        QLineEdit *_projIconField;

        /*!< Input field for project location. */
        QLineEdit *_projLocationField;

        /*!< Input field for project name. */
        QLineEdit *_projNameField;

        /*!< Combobox with values for game resolution. */
        QComboBox *_resolution;

};

#endif // PROJECTDIALOG_H
