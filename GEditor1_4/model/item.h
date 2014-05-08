#ifndef ITEM_H
#define ITEM_H

#include "toyobject.h"

// class --------------------------------------------------------------------------------

//! Item class.
/*!
 * \brief The Item class describes an item, that is draggable and usable
 * in the game world.
 */
class Item : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(bool _locked READ getLocked WRITE setLocked)
        Q_PROPERTY(int _textRelation READ getTextRelation WRITE setTextRelation)
        Q_PROPERTY(QStringList _urls READ getUrls WRITE setUrls)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Item(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

    // --------------------------------------------------------------------------------
    private:

        /*!< Defines whether the item is locked and draggable or not. */
        GETSET(bool, locked, Locked)

        /*!< Assign item to describable text. */
        GETSET(int, textRelation, TextRelation)

        /*!< Defines all image paths for each item state. */
        GETSET(QStringList, urls, Urls)

};

#endif // ITEM_H
