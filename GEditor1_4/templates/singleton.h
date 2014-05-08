#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>

/*!< Templace Singleton class.
 * \param C is the generic typename.
 */
template <typename C>

//! Singleton class.
/*!
 * \brief The Singleton class describes a generic singleton pattern.
 */
class Singleton {

    public:

        /*!
         * \brief getinstance is a static method that gets
         * the single singleton instance.
         * \returns the instance of C.
         */
        static C *instance(){
            if(!_instance)
                _instance = new C();
            return _instance;
        }

        /*!
         * \brief The destructor of class.
         */
        virtual ~Singleton(){ _instance = 0; }

    protected:

        /*!
         * @brief The default constructor.
         */
        Singleton(){}

    private:

        /*!< The single instance of class. */
        static C *_instance;
};

/*!< Sets the template instance to null. */
template <typename C> C *Singleton<C>::_instance = 0;

#endif // SINGLETON_H
