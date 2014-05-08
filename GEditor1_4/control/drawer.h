#ifndef DRAWER_H
#define DRAWER_H

#include "../templates/singleton.h"
#include "../view/canvas/canvasitem.h"
#include "../view/canvas/canvas.h"
#include "../view/canvas/canvasview.h"

#include "manager.h"

// class --------------------------------------------------------------------------------

//! Drawer class.
/*!
 * \brief The Drawer class is an singleton object that paints and manages all items on
 * graphics scene.
 */
class Drawer : public QObject, public Singleton<Drawer> {

        Q_OBJECT

    /*!< The singleton template. */
    friend class Singleton<Drawer>;

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default destructor.
         */
        ~Drawer(){}

    protected:

        /*!
         * \brief The default constructor establishs a connection to manager object.
         */
        Drawer();

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
         * \brief Draws an object.
         * \param key the id of the object
         */
        void drawObject(QString key);

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief Gives the map of graphics scene items.
         * \returns the map of graphics scene items.
         */
        QMap<QString, CanvasItem *> *getItems();

        /*!
         * \brief Removes a certain item from the graphics scene.
         * \param key the key of item
         */
        void removeItemFromScene(QString key);

        /*!
         * \brief Sets the map of items.
         * \param items the map
         */
        void setItems(QMap<QString, CanvasItem *> *items);

        /*!
         * \brief Converts a graphics item to a toy object.
         * \param item the graphics item
         * \param to the toy object
         */
        void updateToyObject(CanvasItem *item, ToyObject *to);

    // --------------------------------------------------------------------------------
    protected:

        /*!
         * \brief Draws the background.
         * \param background the background object
         */
        void drawBackground(Background *background);

        /*!
         * \brief Draws a camera area.
         * \param camera the camera object
         */
        void drawCamera(Camera *camera);

        /*!
         * \brief Draws a click area.
         * \param clickArea the click area object
         */
        void drawClickArea(ClickArea *clickArea);

        /*!
         * \brief Draws a door.
         * \param door the door object
         */
        void drawDoor(Door *door);

        /*!
         * \brief Draws a game character.
         * \param gCharacter the game character object
         */
        void drawGCharacter(GCharacter *gCharacter);

        /*!
         * \brief Draws the inventar box.
         * \param inventar the inventar box object
         */
        void drawInventar(Inventar *inventar);

        /*!
         * \brief Draws an inventar box item.
         * \param item the item object
         */
        void drawItem(Item *item);

        /*!
         * \brief Draws a game object.
         * \param gObject the game object
         */
        void drawGObject(GObject *gObject);

        /*!
         * \brief Draws a player.
         * \param player the player object
         */
        void drawPlayer(Player *player);

        /*!
         * \brief Draws a sound area.
         * \param sound the sound area object
         */
        void drawSoundArea(SoundArea *soundArea);

        /*!
         * \brief Draws a video area.
         * \param videoArea the video area object
         */
        void drawVideoArea(VideoArea *videoArea);

    // --------------------------------------------------------------------------------
    private:

        /*!< The canvas items. */
        QMap<QString, CanvasItem *> *_items;


        /*!< The graphics scene object. */
        GETSET(Canvas*, scene, Scene)

        /*!< The graphics view object. */
        GETSET(CanvasView*, view, View)

};

#endif // DRAWER_H
