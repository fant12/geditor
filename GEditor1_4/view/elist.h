#ifndef ELIST_H
#define ELIST_H

#include <QMouseEvent>
#include <QTableWidget>

// class --------------------------------------------------------------------------------

//! EList class.
/*!
 * \brief The EList class describes a widget that contains all plains of a level.
 */
class EList : public QTableWidget {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent widget
         */
        explicit EList(QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    signals:

        /*!
         * \brief Updates the object name in object inspector widget.
         * \param name the new object name
         */
        void updateObjectName(QString name);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Sets a new layer name.
         * \param newName the new layer name
         */
        void setLayerName(QString newName);

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Ignores all key events for example the item selection with
         * arrow keys.
         * \param event the triggered keypress event
         */
        void keyPressEvent(QKeyEvent *event);

        /*!
         * \brief The event listener to renaming a plain.
         * \param event the triggered double click event
         */
        void mouseDoubleClickEvent(QMouseEvent *event);

};

#endif // ELIST_H
