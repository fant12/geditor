#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H

#include <QDataStream>
#include <QDebug>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

#include "../templates/getset.h"
#include "tobjecttypes.h"

// class --------------------------------------------------------------------------------

//! A Serializable interface.
/*!
 * \brief Defines a class as serializable.
 */
class ISerializable : public QObject {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent defines the pointer to parent object in object tree
         */
        explicit ISerializable(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief A virtual full abstract method that gives the name of object.
         * \return a QString which contains the name of object
         */
        virtual QString getName() const = 0;

};

/*!
 * \brief operator >> defines the new function of shiftR-operator to serialize an object.
 * \param stream the used QDataStream
 * \param obj the serializable object
 * \returns an object of type QDataStream
 */
QDataStream &operator >>(QDataStream &stream, ISerializable &obj);

/*!
 * \brief operator << defines the new function of shiftL-operator to unserialize an object.
 * \param stream stream the used QDataStream
 * \param obj the constant object to unserializable
 * \returns an object of type QDataStream
 */
QDataStream &operator <<(QDataStream &stream, const ISerializable &obj);

#endif // ISERIALIZABLE_H
