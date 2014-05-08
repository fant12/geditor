#ifndef GEDITOR_H
#define GEDITOR_H

#include "view/workbox.h"

#include <QMainWindow>

namespace Ui { class GEditor; }

// class --------------------------------------------------------------------------------

//! GameEditor class.
/*!
 * \brief The GameEditor class is the game editor.
 */
class GEditor : public QMainWindow {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent widget
         */
        explicit GEditor(QWidget *parent = 0);

        /*!
         * \brief The default destructor.
         */
        ~GEditor();

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Closes the application.
         * \param event the released close event
         */
        void closeEvent(QCloseEvent *event);

    // --------------------------------------------------------------------------------
    private slots:

        /*!
         * \brief Closes the application.
         */
        void close();

        /*!
         * \brief Closes the active project.
         */
        void closeProject();

        /*!
         * \brief Copies the selected text in the script editor.
         */
        void copy();

        /*!
         * \brief Cuts out the selected text in the script editor.
         */
        void cut();

        /*!
         * \brief Exports the active project.
         */
        void exportProject();

        /*!
         * \brief Imports a file to the active project.
         */
        void import();

        /*!
         * \brief Adds a new level file to the active project.
         */
        void newLevel();

        /*!
         * \brief Creates a new project.
         */
        void newProject();

        /*!
         * \brief Opens a project file.
         */
        void open();

        /*!
         * \brief Inserts text from the clipboard.
         */
        void paste();

        /*!
         * \brief Saves the current project.
         */
        void save();

        /*!
         * \brief Saves the active file as a certain type.
         */
        void saveAs();

        /*!
         * \brief Scales the canvas view.
         * \param scale the scaling
         */
        void sceneScaleChanged(const QString &scale);

        /*!
         * \brief Searches a word in script editor.
         */
        void search();

        /*!
         * \brief Shows the information widget with information about
         * the application.
         */
        void showAbout();

        /*!
         * \brief Shows the audio widget.
         */
        void showAudioWindow();

        /*!
         * \brief Shows the connector widget to connect different levels.
         */
        void showConnector();

        /*!
         * \brief Shows the help.
         */
        void showHelp();

        /*!
         * \brief Shows the options widget.
         */
        void showOptions();

        /*!
         * \brief Shows the rotator dialog.
         */
        void showRotator();

        /*!
         * \brief Shows the Sprite Creator dialog.
         */
        void showSpriteCreator();

        /*!
         * \brief Triggers the event if the canvas view shall be scale
         * and emit the assigned signal.
         */
        void triggerScaleChanged();

        /*!
         * \brief Changes to the default cursor in the graphics scene.
         */
        void useDefCursorMode();

        /*!
         * \brief Changes to drag the cursor in the graphics scene.
         */
        void useDragCursorMode();

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Reads the application settings.
         */
        void readSettings();

        /*!
         * \brief Writes the application settings.
         */
        void writeSettings();

    // --------------------------------------------------------------------------------
    private:

        /*!< The work box area. */
        WorkBox *_area;

        /*!< The user interface. */
        Ui::GEditor *ui;

};

#endif // GEDITOR_H
