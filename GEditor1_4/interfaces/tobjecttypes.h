#ifndef TOBJECTTYPES_H
#define TOBJECTTYPES_H

#include <QMap>
#include <QString>

// enum ---------------------------------------------------------------------------------

//! enum TObjectTypes
/*!
 * \brief The TObjectTypes enum defines all allowed object types in game scene.
 */
enum TObjectTypes {

    TBackground, //*!< Background */
    TCamera,     //*!< Camera */
    TClickArea,  //*!< ClickArea */
    TCursor,     //*!< Cursor */
    TDoor,       //*!< Door */
    TGCharacter, //*!< Game character */
    TGObject,    //*!< Game object */
    TInventar,   //*!< Inventar box */
    TItem,       //*!< Inventar item */
    TPlayer,     //*!< Player */
    TSoundArea,  //*!< Sound area */
    TVideoArea   //*!< Video area */

};

// --------------------------------------------------------------------------------------

#define TOTYPES_LENGTH 12

static const QString TOTYPES[TOTYPES_LENGTH] = {
    "Background",
    "Camera",
    "ClickArea",
    "Cursor",
    "Door",
    "GCharacter",
    "GObject",
    "Inventar",
    "Item",
    "Player",
    "SoundArea",
    "VideoArea"
};

#endif // TOBJECTTYPES_H
