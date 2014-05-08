#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <QObject>

class Observable {

    public:
        explicit Observable();
        virtual ~Observable(){}

        void attach(Observer<T> &observer){
            _observers.push_back(&observer);
        }

        void notify(){
            std::vector<Observer<T> *>::iterator it;

            for(it=_observers.begin(); _observers.end() != it; ++it)
                (*it)->update(static_cast<T *>(this));
        }

    private:
        std::vector<Observer<T> *> _observers;
};

#endif // OBSERVABLE_H
