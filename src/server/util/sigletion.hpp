#ifndef SIGLETION_H
#define SIGLETION_H

#include "globals.hpp"

BEGIN_MEATBALL_NAMESPC

template <class T>
class Singleton
{
protected:
    Singleton() { }
    virtual ~Singleton() { }

private:
    static T* mInstance;

public:
    static void CreateInstance() { mInstance = new T(); }

    static void DestroyInstance() { delete mInstance; }

    static T* Instance() { return mInstance; }
};

template <class T>
T* Singleton<T>::mInstance = 0;

END_MEATBALL_NAMESPC

#endif
