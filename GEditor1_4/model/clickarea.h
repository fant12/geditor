#ifndef CLICKAREA_H
#define CLICKAREA_H

#include "toyobject.h"

// class --------------------------------------------------------------------------------

//! Clickarea class.
/*!
 * \brief The ClickArea class describes a clickable area.
 */
class ClickArea : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(bool _locked READ getLocked WRITE setLocked)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit ClickArea(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

    // --------------------------------------------------------------------------------
    private:

        /*!< Defines whether the area is receivable or not. */
        GETSET(bool, locked, Locked)

};

#endif // CLICKAREA_H
