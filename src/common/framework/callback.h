#ifndef _CALLBACK_H_
#define _CALLBACK_H_

#include <stdlib.h>
#include <new>

class CallbackBase
{
public:
    virtual ~CallbackBase() throw() {}
    virtual int execute(int code, void* data) = 0;
};

template<class T>
class Callback : public CallbackBase
{
public:
    typedef int (T::*Func)(int code, void* data);

    Callback(T* obj, Func func) : m_obj(obj), m_func(func) {}

    virtual ~Callback() throw() {}

    int execute(int code, void* data)
    {
        return (m_obj->*m_func)(code, data);
    }

private:
    T*      m_obj;
    Func    m_func;
};

class CallbackObject
{
public:
    CallbackObject() : m_callback(NULL) {}

    virtual ~CallbackObject() throw()
    {
        if(m_callback)
            m_callback->~CallbackBase();
    }

    template<class T>
    void set_handler(T* obj, typename Callback<T>::Func func)
    {
        m_callback = new((void*)m_storage)Callback<T>(obj, func);
    }

    int execute(int code, void* data)
    {
        return m_callback->execute(code, data);
    }

private:
    char            m_storage[sizeof(Callback<CallbackBase>)];
    CallbackBase*   m_callback;
};

#endif //_CALLBACK_H_

