#ifndef GCHARACTER_H
#define GCHARACTER_H

#include "inventar.h"

#include <QStringList>

// class --------------------------------------------------------------------------------

//! GCharacter class.
/*!
 * \brief The GCharacter class describes a game character.
 */
class GCharacter : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(int _animDelay READ getAnimDelay WRITE setAnimDelay)
        Q_PROPERTY(int _numOfFrames READ getNumOfFrames WRITE setNumOfFrames)
        Q_PROPERTY(int _numOfLoop READ getNumOfLoop WRITE setNumOfLoop)
        Q_PROPERTY(bool _isDropable READ getIsDropable WRITE setIsDropable)
        Q_PROPERTY(float _adjVolumWithScaling READ getAdjVolumWithScaling WRITE setAdjVolumWithScaling)
        Q_PROPERTY(QStringList _urls READ getUrls WRITE setUrls)
        Q_PROPERTY(Inventar* _inventar READ getInventar WRITE setInventar)
        //TODO Q_PROPERTY(GCState state)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit GCharacter(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Checks whether the object is inside of a range area or not.
         * \returns true, if it collides with border of the range area, otherwise false
         */
        virtual bool isCollide();

        /*!
         * \brief Lets the character walking.
         */
        virtual void walking();

    // --------------------------------------------------------------------------------
    public:

        //! enum GCState
        /*!
         * \brief The GCState enum defines two states. Standing and walking.
         */
        enum GCState { STANDING, WALKING };

    // --------------------------------------------------------------------------------
    private:

        /*!< The animation delay defines how long one frame needs to playing or how
         * long one animation takes. */
        GETSET(int, animDelay, AnimDelay)

        /*!< Defines how many frames will be used for one animation. */
        GETSET(int, numOfFrames, NumOfFrames)

        /*!< Defines the times of loop in one animation. */
        GETSET(int, numOfLoop, NumOfLoop)

        /*!< Defines whether the object can receive other draggable objects or not. */
        GETSET(bool, isDropable, IsDropable)

        /*!< Defines the adjustment volume with scaling or the behaviour of object while
         * scaling. It is necessary to moving in different z-values. */
        GETSET(float, adjVolumWithScaling, AdjVolumWithScaling)

        /*!< The list of image paths for each animation frame.
         */
        GETSET(QStringList, urls, Urls)

        /*!< The inventar box of character. */
        GETSET(Inventar*, inventar, Inventar)

        //!< Defines whether the character is standing or walking now. */
        //TODO GETSET(GCState, state, State);
};

#endif // GCHARACTER_H
