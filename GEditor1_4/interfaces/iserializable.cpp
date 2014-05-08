#include "iserializable.h"

// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------

ISerializable::ISerializable(QObject *parent) : QObject(parent){}

// --------------------------------------------------------------------------------------
// extern -------------------------------------------------------------------------------

QDataStream &operator >>(QDataStream &stream, ISerializable &obj){

    QVariant var;
    for(int i = 0; obj.metaObject()->propertyCount() > i; ++i)
        if(obj.metaObject()->property(i).isStored(&obj)){
            stream >> var;
            obj.metaObject()->property(i).write(&obj, var);
        }
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const ISerializable &obj){

    for(int i = 0; obj.metaObject()->propertyCount() > i; ++i)
        if(obj.metaObject()->property(i).isStored(&obj))
            stream << obj.metaObject()->property(i).read(&obj);
    return stream;
}
