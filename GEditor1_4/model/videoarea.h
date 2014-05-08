#ifndef VIDEOAREA_H
#define VIDEOAREA_H

#include "mediaarea.h"

// class --------------------------------------------------------------------------------

//! VideoArea class.
/*!
 * \brief The VideoArea class describes an area, where video scenes
 * can be played.
 */
class VideoArea : public MediaArea {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit VideoArea(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Plays the video.
         * \param id the integer that defines the video url
         */
        void play(quint32 id);

};

#endif // VIDEOAREA_H
