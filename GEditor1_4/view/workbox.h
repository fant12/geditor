#ifndef WORKBOX_H
#define WORKBOX_H

#include "../control/manager.h"
#include "elist.h"
#include "oinspector.h"
#include "scripteditor.h"

#include <QTableWidget>
#include <QTabWidget>

class CanvasView;

// class --------------------------------------------------------------------------------

//! WorkBox class.
/*!
 * \brief The WorkBox class is the widget with canvas element, script editor,
 * attribute list and plain widget.
 */
class WorkBox : public QWidget {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent widget
         */
        explicit WorkBox(QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Adds new plain entries.
         */
        void addObject();

        /*!
         * \brief Removes a selected plain entry.
         */
        void removeObject();

        /*!
         * \brief Shows the context menu.
         * \param pos the mouse pointer that describes the position,
         * where user has clicked.
         */
        void showContextMenu(const QPoint &pos);

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Initializes the main tool widget with script editor
         * and graphics scene.
         */
        void initMainToolWindow();

        /*!
         * \brief Initializes the side tool widgets.
         */
        void initSideToolWindow();

    // --------------------------------------------------------------------------------
    private:

        /*!< The attribute widget. */
        OInspector *_attributeWindow;

        /*!< The main tool widget. */
        QTabWidget *_mainToolWindow;

        /*!< The side tool widget. */
        QTabWidget *_sideToolWindow;


        /*!< The script editor widget. */
        GETSET(ScriptEditor*, editor, Editor)

        /*!< The EList. */
        GETSET(EList*, objectsTab, ObjectsTab)

        /*!< The Canvas view. */
        GETSET(CanvasView*, view, View)

};

#endif // WORKBOX_H
