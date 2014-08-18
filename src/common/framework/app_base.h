/**
 *  @file   app_base.h
 *  @brief   应用模块抽象基类
 *  @author   stanjiang
 *  @date   2014-08-11
*/

#ifndef _APP_BASE_H_
#define _APP_BASE_H_

#include "comm_def.h"

class AppModuleBase;

class AppBase
{
public:
    virtual ~AppBase() throw();
    virtual int app_init()                                      = 0;
    virtual void app_stop()                                 = 0;
    virtual void app_reload()                             = 0;
    virtual void app_clean()                               = 0;
    virtual const char* app_name() const           = 0;
    virtual int app_run()                                      = 0;
    virtual AppModuleBase* find_module(int module_id) const     = 0;
    // 在子类实现
    static AppBase* create_instance();
};

class AppModuleBase
{
public:
    virtual ~AppModuleBase() throw();
    virtual void module_init()                  = 0;
    virtual void module_fini()                  = 0;
    virtual const char* module_name() const     = 0;
};

template<class AppModule>
AppModule* find_module(const AppBase* app_base)
{
    AppModuleBase* module = app_base->find_module(AppModule::module_id());
    return static_cast<AppModule*>(module);
}

#endif //_APP_BASE_H_

