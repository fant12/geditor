#ifndef DOOR_H
#define DOOR_H

#include "clickarea.h"

// class --------------------------------------------------------------------------------

//! ClickArea class.
/*!
 * \brief The Door class describes a clickable area thats link to a new level.
 */
class Door : public ClickArea {

        Q_OBJECT

        Q_PROPERTY(int _anchor READ getAnchor WRITE setAnchor)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Door(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

    // --------------------------------------------------------------------------------
    private:

        /*!< The anchor id. */
        GETSET(int, anchor, Anchor)

};

#endif // DOOR_H
