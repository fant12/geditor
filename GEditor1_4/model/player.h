#ifndef PLAYER_H
#define PLAYER_H

#include "gcharacter.h"

// class --------------------------------------------------------------------------------

//! Player class.
/*!
 * \brief The Player class describes the player character.
 */
class Player : public GCharacter {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Player(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Checks whether the player character is inside of a range area or not.
         * \returns true, if it collides with border of range area, otherwise false.
         */
        bool isCollide();

        /*!
         * \brief Lets the player character walking.
         */
        void walking();

};

#endif // PLAYER_H
