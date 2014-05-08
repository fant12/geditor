#ifndef INVENTAR_H
#define INVENTAR_H

#include "item.h"

// class --------------------------------------------------------------------------------

//! Inventar class.
/*!
 * \brief The Inventar class describes players inventar.
 */
class Inventar : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(QList<Item*>* _items READ getItems WRITE setItems)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Inventar(QObject *parent = 0);

        /*!
         * \brief The default destructor.
         */
        ~Inventar();

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Add an item to the inventar item list.
         * \param item the item
         */
        void addItem(Item *item);

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

        /*!
         * \brief Removes an item from the inventar item list.
         * \param item the item
         * \returns true if success, otherwise false
         */
        bool removeItem(Item *item);

    // --------------------------------------------------------------------------------
    private:

        /*!< The inventar item list. */
        GETSET(QList<Item*>*, items, Items)

};

#endif // INVENTAR_H
