#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "toyobject.h"
#include <QColor>

// class --------------------------------------------------------------------------------

//! Background class.
/*!
 * \brief The Background class describes the level background.<br />
 * It inherits from ToyObject.
 */
class Background : public ToyObject {

        Q_OBJECT

        Q_PROPERTY(QColor _color READ getColor WRITE setColor)
        Q_PROPERTY(QString _url READ getUrl WRITE setUrl)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit Background(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the class type.
         * \returns the enum index for the object type
         */
        int getToyType();

    // --------------------------------------------------------------------------------
    private:

        /*!< The background color. */
        GETSET(QColor, color, Color)

        /*!< The url to background image. */
        GETSET(QString, url, Url)

};

#endif // BACKGROUND_H
