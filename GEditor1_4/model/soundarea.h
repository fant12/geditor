#ifndef SOUNDAREA_H
#define SOUNDAREA_H

#include "mediaarea.h"

// class --------------------------------------------------------------------------------

//! SoundArea class.
/*!
 * \brief The SoundArea class describes an area, where sound can be played.
 */
class SoundArea : public MediaArea {

        Q_OBJECT

   // --------------------------------------------------------------------------------
   public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit SoundArea(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Plays the sound.
         * \param id the integer that defines the sound url
         */
        void play(quint32 id);

};

#endif // SOUNDAREA_H
