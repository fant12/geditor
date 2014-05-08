#ifndef GCURSOR_H
#define GCURSOR_H

#include "../interfaces/iserializable.h"

#define URL_LIST_SIZE ((int) 7)

// class --------------------------------------------------------------------------------

//! GCursor class.
/*!
 * \brief The GCursor class describes the cursor type on certain areas.
 */
class GCursor : public ISerializable {

        Q_OBJECT

        Q_PROPERTY(QString _url READ getUrl)
        Q_PROPERTY(QString _typeName READ getTypename)
        Q_PROPERTY(gcType _type READ getType)

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param parent the parent object
         */
        explicit GCursor(QObject *parent = 0);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief getPosCursorNames get all names of each possible cursor.
         * \return a list of strings.
         */
        static QStringList *getPosCursorNames();

    // --------------------------------------------------------------------------------
    public:

        /*!< Contains all possible cursor types. */
        enum gcType { CLOSE, GOTO, OPEN, SEE, TALK, TAKE, USE };

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the current cursor type.
         * \returns an integer that defines the current cursor type.
         */
        int getCursor() const;

        /*!
         * \brief Gives the current cursor name.
         * \returns a string that contains the cursor name.
         */
        QString getCursorName() const;

        /*!
         * \brief Gives the object name.
         * \returns a QString which contains information about the game object type
         */
        QString getName() const;

        /*!
         * \brief getPosCursorName get a name of each possible cursors.
         * \param i the array index
         * \returns a string which contains the cursor name
         */
        QString getPosCursorName(const int i) const;

        /*!
         * \brief Gives the enumeration for cursor types.
         * \returns an enumeration object
         */
        gcType getType();

        /*!
         * \brief Gives the current cursor type name.
         * \returns a string that contains the enumeration type
         */
        QString getTypename();

        /*!
         * \brief Gives the url of current cursor image.
         * \return a string that contains the path to the image
         */
        QString getUrl() const;

        /*!
         * \brief Sets the cursor type.
         * \param idx the enumeration index for cursor type
         */
        void setCursor(const int idx);

    // --------------------------------------------------------------------------------
    private:

        /*!< List of each possible cursor types name. */
        static const QString _gcTypeNames[URL_LIST_SIZE];

        /*!< Contains all image paths of each cursor type. */
        static QString _urls[URL_LIST_SIZE];


        /*!< The image path for the cursor type. */
        QString _url;

        /*!< The cursor type name. */
        QString _typeName;

        /*!< The current cursor type. */
        gcType _type;

};

#endif // GCURSOR_H
