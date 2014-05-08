#ifndef CAMERA_H
#define CAMERA_H

#include "background.h"

// class --------------------------------------------------------------------------------

//! Camera class.
/*!
 * \brief The Camera class describes the level camera that shows
 * currently active range of background.
 */
class Camera : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(Background* _background READ getBackground WRITE setBackground)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Camera(QObject *parent = 0);

        /*!
         * \brief The default destructor.
         */
        ~Camera();

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Moves the visible range.
         * \param cx the central point at x-axis in range
         * \param cy the central point at y-axis in range
         */
        void move(qint32 cx, qint32 cy);

    // --------------------------------------------------------------------------------
    private:

        /*!< The background. */
        GETSET(Background*, background, Background)

};

#endif // CAMERA_H
