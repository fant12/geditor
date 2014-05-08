#ifndef MEDIAAREA_H
#define MEDIAAREA_H

#include "toyobject.h"

// class --------------------------------------------------------------------------------

//! MediaArea class.
/*!
 * \brief The MediaArea describes an abstract area for media input.
 */
class MediaArea : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(bool _loop READ getLoop WRITE setLoop)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit MediaArea(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        virtual int getToyType() = 0;

        /*!
         * \brief Plays the media.
         * \param id defines the url to the media source.
         */
        virtual void play(quint32 id) = 0;

    // --------------------------------------------------------------------------------
    protected:

        /*!< Defines how often the media source will be played. */
        GETSET(bool, loop, Loop)

};

#endif // MEDIAAREA_H
