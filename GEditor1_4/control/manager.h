#ifndef MANAGER_H
#define MANAGER_H

#include <QApplication>
#include <QMap>
#include <QSettings>

#include "../templates/singleton.h"
#include "../model/camera.h" //import: getset, iserializable, gcursor, toyobject, camera
#include "../model/door.h" //import: clickarea
#include "../model/gobject.h" //import: item, inventar
#include "../model/player.h" //import: gcharacter
#include "../model/soundarea.h" //import: mediaarea
#include "../model/videoarea.h"

class Drawer;

// class --------------------------------------------------------------------------------

//! Manager class.
/*!
 * \brief The Manager class is an singleton object that manages all objects and settings
 * of game scene.
 */
class Manager : public QObject, public Singleton<Manager> {

        Q_OBJECT

    /*!< The singleton template. */
    friend class Singleton<Manager>;

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default destructor.
         */
        ~Manager(){}

    protected:

        /*!
         * \brief The default constructor establishs a connection to drawer object.
         */
        Manager();

    // --------------------------------------------------------------------------------
    signals:

        /*!
         * \brief Notifies about an object change.
         * \param key the id of the object that changed
         */
        void notify(QString key);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Updates the game object map.
         * \param key the id of the object that changed
         */
        void updateMap(QString key);

        /*!
         * \brief Update the object name.
         * \param oldName the old name
         * \param newName the new name
         */
        void updateName(QString oldName, QString newName);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Defines whether it is allowed to send a signal forward, currently.
         * \returns true, if sending forward is allowed, otherwise false
         */
        static bool getForwardUpdate();

        /*!
         * \brief Inverts the value of the forward update attribute.
         * \returns true if forward update is not allowed, otherwise false
         */
        static bool invertForwardUpdate();

    public:

        /*!
         * \brief Inserts a new toy object to the map.
         * \param id the key
         * \param object the toy object
         */
        void addToyObject(QString id, ToyObject *object);

        /*!
         * \brief Loads the settings data.
         * \param key the assigned key to value
         * \return the stored data
         */
        QVariant loadSettings(QString key);

        /*!
         * \brief Gives the map with level objects.
         * \returns a map
         */
        QMap<QString, ToyObject*> *getLevelObjects();

        /*!
         * \brief Removes a certain object in map.
         * \param id the key that identifies the object
         * \returns whether removing was successful or not
         */
        bool removeToyObject(QString id);

        /*!
         * \brief Sets the map of level objects.
         * \param levelObjects the map
         */
        void setLevelObjects(QMap<QString, ToyObject*> *levelObjects);

        /*!
         * \brief Stores data in settings file.
         * \param key the hash key for value
         * \param value the data to store
         */
        void writeSettings(QString key, QVariant value);

    // --------------------------------------------------------------------------------
    private:

        /*!< Decides when a signal will be sent forward or not. */
        static bool forwardUpdate;

        /*!< The path to using settings file. */
        const QString SETTINGS_FILE;

    private:

        /*!< Stores all toy objects of level. */
        QMap<QString, ToyObject*> *_levelObjects;

        /*!< The level depth. */
        GETSET(quint32, depth, Depth)

        /*!< The level height. */
        GETSET(quint32, height, Height)

        /*!< The maximum number of frames. */
        GETSET(quint32, maxNumOfFrames, MaxNumOfFrames)

        /*!< The maximum number of loops. */
        GETSET(quint32, maxNumOfLoops, MaxNumOfLoops)

        /*!< The level width. */
        GETSET(quint32, width, Width)

};

#endif // MANAGER_H
