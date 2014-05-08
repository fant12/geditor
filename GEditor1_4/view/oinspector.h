#ifndef OINSPECTOR_H
#define OINSPECTOR_H

#include "elist.h"
#include "../control/manager.h"

#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>

// class --------------------------------------------------------------------------------

//! OInspector class.
/*!
 * \brief The OInspector class describes a widget for managing game elements
 * attributes on view.
 */
class OInspector : public QTableWidget {

        Q_OBJECT

    // --------------------------------------------------------------------------------
    public:

        /*!
         * \brief The default constructor.
         * \param elist the list for all game elements
         * \param parent the parent object
         */
        explicit OInspector(EList *elist, QWidget *parent = 0);

    // --------------------------------------------------------------------------------
    signals:

        /*!
         * \brief Emitted when a field value was changed.
         * \param the value
         */
        void fieldChanged(QString value);

        /*!
         * \brief Updates an object.
         * \param to the object
         */
        void notify(ToyObject *to);

    // --------------------------------------------------------------------------------
    public slots:

        /*!
         * \brief Shows a dialog for multiple values assignment.
         */
        void createCADialog();

        /*!
         * \brief Creates a game element.
         * \param type defines the object
         * \param name the object name or id
         */
        void createGameElem(TObjectTypes type, QString name);

        /*!
         * \brief Sets the background color.
         * \param row the row where the cell has changed
         * \param col the colum where the cell has changed
         */
        void setBGColor(int row, int col);

        /*!
         * \brief Sets the background url.
         * \param url the url value
         */
        void setBGURL(QString url);

        /*!
         * \brief Sets the locked attribute of the click area.
         * \param locked the locked value
         */
        void setCALocked(int locked);

        /*!
         * \brief Sets the door anchor.
         * \param value the anchors value
         */
        void setDRAnchor(QString value);

        /*!
         * \brief Sets the adjustment volume of the game character object.
         * \param adjVolumWithScaling the adjustment volume value
         */
        void setGCAdjVolumWithScaling(QString adjVolumWithScaling);

        /*!
         * \brief Sets the animation delay of the character.
         * \param animDelay the animation delay value
         */
        void setGCAnimDelay(QString animDelay);

        /*!
         * \brief Sets the character object as dropable or not.
         * \param isDropable the isDropable value
         */
        void setGCDropable(int isDropable);

        /*!
         * \brief Sets the urls of the character object.
         * \param urls the urls
         */
        void setGCUrls(QString urls);

        /*!
         * \brief Sets the game object as dropable.
         * \param isDropable the isDropable value
         */
        void setGODropable(int isDropable);

        /*!
         * \brief Sets the urls of the game object.
         * \param urls the urls
         */
        void setGOUrls(QString urls);

        /*!
         * \brief Sets the loop attribute of the media object.
         * \param loop the loop value
         */
        void setMALoop(int loop);

        /*!
         * \brief Sets the object cursor.
         * \param idx defines the cursor value
         */
        void setTOCursor(int idx);

        /*!
         * \brief Sets the flag, if the toy object is movable or not.
         * \param isMovable the boolean isMovable value
         */
        void setTOMovable(int isMovable);

        /*!
         * \brief Sets the visibility of toy object.
         * \param visibility the visibility value
         */
        void setTOVisibility(int visibility);

        /*!
         * \brief Sets the url.
         */
        void setUrl();

        /*!
         * \brief Sets the urls.
         */
        void setUrls();

        /*!
         * \brief Updates the object inspector view.
         * \param to the toy object
         */
        void update(ToyObject *to);

        /*!
         * \brief Updates the name.
         * \param newName the new name
         */
        void updateName(QString newName);

        /*!
         * \brief Changes the object in view.
         * \param row the row in elist
         */
        void updateSelectedObject(int row);

    // --------------------------------------------------------------------------------
    private:

        /*!
         * \brief Clears the table.
         */
        void clearTable();

        /*!
         * \brief Creates a combobox with selection between boolean values.
         * \param value the current value
         * \returns the combobox
         */
        QComboBox *createBoolCBox(bool value);

        /*!
         * \brief Creates a new spinner object.
         * \param value the current value
         * \param max the maximum value
         * \returns the spinner
         */
        QSpinBox *createSpinner(quint32 value, quint32 max);

        /*!
         * \brief Prepares the default list of object inspector.
         * \param to the toy object
         */
        void defaultPreparation(ToyObject *to);

        /*!
         * \brief Sets all rows on same height and text alignment to center.
         */
        void formatCells();

        /*!
         * \brief Initializes a new object.
         * \param to the object
         * \param name the object name
         */
        void initNewObject(ToyObject *to, QString name);

        /*!
         * \brief Prepares the object inspector for a background object.
         * \param background the background object
         */
        void prepare(Background *background);

        /*!
         * \brief Prepares the object inspector for a camera object.
         * \param camera the camera object
         */
        void prepare(Camera *camera);

        /*!
         * \brief Prepares the object inspector for a click area object.
         * \param clickArea the click area object
         */
        void prepare(ClickArea *clickArea);

        /*!
         * \brief Prepares the object inspector for a door object.
         * \param door the door object
         */
        void prepare(Door *door);

        /*!
         * \brief Prepares the object inspector for a game character object.
         * \param gCharacter the game character object
         */
        void prepare(GCharacter *gCharacter);

        /*!
         * \brief Prepares the object inspector for a game scene object.
         * \param gObject the game scene object
         */
        void prepare(GObject *gObject);

        /*!
         * \brief Prepares the object inspector for an inventar object.
         * \param inventar the inventar object
         */
        void prepare(Inventar *inventar);

        /*!
         * \brief Prepares the object inspector for an item object.
         * \param item the item object
         */
        void prepare(Item *item);

        /*!
         * \brief Prepares the object inspector for a player object.
         * \param player the player object
         */
        void prepare(Player *player);

        /*!
         * \brief Prepares the object inspector for a media area object.
         * \param mediaArea the sound area object
         */
        void prepare(MediaArea *mediaArea);

    // --------------------------------------------------------------------------------
    private:

        /*!< The input field for different items. */
        QTextEdit *_itemsEdit;


        /*!< The current toy object. */
        GETSET(ToyObject*, curObject, CurObject)

        /*!< The EList object that manages all plains. */
        GETSET(EList*, elist, EList)

};

#endif // OINSPECTOR_H
