#ifndef GETSET_H
#define GETSET_H

// --------------------------------------------------------------------------------------
// A macro for getter and setter

#define GETSET(type, var, name) \
    protected: \
        type _##var; \
    public: \
        type get##name() const {\
            return _##var; \
        }\
    public slots:\
        void set##name(type val) {\
            _##var = val; \
        }

// --------------------------------------------------------------------------------------
// A macro for getter and setter with signal call.

#define GSUP(type, var, name) \
    protected: \
        type _##var; \
    public: \
        type get##name() const {\
            return _##var; \
        }\
    public slots:\
        void set##name(type val) {\
            _##var = val; \
            emit update##name(val);\
        }

#endif // GETSET_H
