#include "gcursor.h"

#include <QStringList>

// --------------------------------------------------------------------------------------
// static -------------------------------------------------------------------------------


const QString GCursor::_gcTypeNames[URL_LIST_SIZE] = {
    "CLOSE", "GOTO", "OPEN", "SEE", "TALK", "TAKE", "USE"
};

QString GCursor::_urls[URL_LIST_SIZE] = {
        "URL close",
        "URL goto",
        "URL open",
        "URL see",
        "URL talk",
        "URL take",
        "URL use"
};


// --------------------------------------------------------------------------------------
// magic --------------------------------------------------------------------------------


GCursor::GCursor(QObject *parent) : ISerializable(parent),
    _url(_urls[0]),
    _type(GCursor::CLOSE),
    _typeName(_gcTypeNames[0]){}


// --------------------------------------------------------------------------------------
// public -------------------------------------------------------------------------------


int GCursor::getCursor() const{
    return static_cast<int>(_type);
}

QString GCursor::getCursorName() const{
    return _typeName;
}

QString GCursor::getName() const {
    return getCursorName();
}

QString GCursor::getPosCursorName(const int i) const{
    return _gcTypeNames[i];
}

QStringList *GCursor::getPosCursorNames(){

    QStringList *cursList = new QStringList;

    for(int i = 0; URL_LIST_SIZE > i; ++i)
        cursList->append(_gcTypeNames[i]);
    return cursList;
}

GCursor::gcType GCursor::getType(){
    return GCursor::_type;
}

QString GCursor::getTypename(){
    return _typeName;
}

QString GCursor::getUrl() const{
    return _url;
}

void GCursor::setCursor(const int idx){

    for(int i = 0; URL_LIST_SIZE > i; ++i)
        if(idx == i){
            _type = static_cast<gcType>(i);
            _typeName = _gcTypeNames[i];
            _url = _urls[i];
        }
}
