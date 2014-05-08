#ifndef GOBJECT_H
#define GOBJECT_H

#include "inventar.h"

#include <QStringList>

// class --------------------------------------------------------------------------------

//! GObject class.
/*!
 * \brief The GObject class describes normally game objects like tables,
 * chairs or robots.
 */
class GObject : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(bool _isDropable READ getIsDropable WRITE setIsDropable)
        Q_PROPERTY(int _clickAreaIdx READ getClickAreaIdx WRITE setClickAreaIdx)
        Q_PROPERTY(int _textRelation READ getTextRelation WRITE setTextRelation)
        Q_PROPERTY(QStringList _urls READ getUrls WRITE setUrls)
        Q_PROPERTY(Inventar* _inventar READ getInventar WRITE setInventar)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit GObject(QObject *parent = 0);

        /*!
         * \brief The default destructor.
         */
        ~GObject();

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

    // --------------------------------------------------------------------------------
    private:

        /*!< Defines whether the object can receive other draggable objects or not. */
        GETSET(bool, isDropable, IsDropable)

        /*!< The index to connected click areas. */
        GETSET(int, clickAreaIdx, ClickAreaIdx)

        /*!< The index to connected text monologs. */
        GETSET(int, textRelation, TextRelation)

        /*!< The list of each image for a certain state. */
        GETSET(QStringList, urls, Urls)

        /*!< The inventar box of game object. */
        GETSET(Inventar*, inventar, Inventar)

};

#endif // GOBJECT_H
