#ifndef TOYOBJECT_H
#define TOYOBJECT_H

#include "gcursor.h"

class Manager;

// class --------------------------------------------------------------------------------

//! An abstract superclass for game objects.
/*!
 * \brief The ToyObject class describe general properties of toy
 * objects in game. It's a abstract super class that implements from
 * serializable interface.
 */
class ToyObject : public ISerializable {

        Q_OBJECT

        Q_PROPERTY(GCursor* _cursor READ getCursor WRITE setCursor)
        Q_PROPERTY(QString _name READ getName WRITE setName)
        Q_PROPERTY(int _height READ getHeight WRITE setHeight)
        Q_PROPERTY(int _width READ getWidth WRITE setWidth)
        Q_PROPERTY(int _rotation READ getRotation WRITE setRotation)
        Q_PROPERTY(int _x READ getX WRITE setX)
        Q_PROPERTY(int _y READ getY WRITE setY)
        Q_PROPERTY(int _z READ getZ WRITE setZ)
        Q_PROPERTY(bool _isMovable READ getIsMovable WRITE setIsMovable)
        Q_PROPERTY(bool _visibility READ getVisibility WRITE setVisibility)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit ToyObject(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the information about the toy type.
         * \returns the enum index for the object type
         */
        virtual int getToyType() = 0;

        /*!
         * \brief Defines a visible range of toy object.
         * \param x defines the start point at x-axis
         * \param y defines the start point at y-axis
         * \param width defines the width of choosen range
         * \param height defines the height of choosen range
         */
        void crop(quint32 x, quint32 y, quint32 width, quint32 height);

    // --------------------------------------------------------------------------------
    protected:

        /*!< The cursor. */
        GETSET(GCursor*, cursor, Cursor)

        /*!< The object height. */
        GETSET(int, height, Height)

        /*!< Defines whether the object is movable or not. */
        GETSET(bool, isMovable, IsMovable)

        /*!< The object name. With this the virtual method of interface is fulfilled. */
        GETSET(QString, name, Name)

        /*!< Defines whether the object is visible or not. */
        GETSET(bool, visibility, Visibility)

        /*!< The object width. */
        GETSET(int, width, Width)

        /*!< The object rotation. */
        GETSET(int, rotation, Rotation)

        /*!< The position on x-axis. */
        GETSET(int, x, X)

        /*!< The position on y-axis. */
        GETSET(int, y, Y)

        /*!< The position on z-axis. */
        GETSET(int, z, Z)

};

#endif // TOYOBJECT_H
