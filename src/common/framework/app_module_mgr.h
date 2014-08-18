#ifndef _APP_MODULE_MGR_H_
#define _APP_MODULE_MGR_H_

#include "comm_def.h"
#include "app_base.h"

/**
* @brief 模块管理类
*/
class AppModuleMgr : public AppBase
{
public:

    ~AppModuleMgr() throw()
    {
        app_stop();
    }

    /**
     * @brief app_reload APP重新加载 
     */
    virtual void app_reload()
    {
        LOG(INFO) << " AppModuleMgr recv reload signal!";
    }

    /**
     * @brief app_clean APP清理 
     */
    virtual void app_clean()
    {
        LOG(INFO) << " AppModuleMgr recv clean signal!";
    }

protected:

    /**
     * @brief add_module 添加模块 
     *
     * @param module_id
     * @param app_module
     */
    void add_module(uint64_t module_id, AppModuleBase* app_module)
    {
        m_module_map[module_id] = app_module;
    }

    /**
     * @brief get_module 获取module 
     *
     * @return module
     */
    template<typename T>
    T* get_module() const
    {
        ModuleMap_T::const_iterator it = m_module_map.find(T::module_id());
        CHECK(it != m_module_map.end())
            << "get_module error!";
        return dynamic_cast<T*>(it->second); 
    }
    
    /**
     * @brief find_module 根据module_id查找module 
     *
     * @param module_id 模块ID
     *
     * @return 
     */
    virtual AppModuleBase* find_module(int module_id) const
    {
        AppModuleBase* module;
        ModuleMap_T::const_iterator it = m_module_map.find(module_id);
        if(it == m_module_map.end())
            module = NULL;
        else
            module = it->second;

        CHECK(module != NULL)
            << "module[" << module_id
            << "]  not register!";
        return module; 
    }

    /**
     * @brief app_stop APP停止处理 
     */
    void app_stop()
    {
        if(m_module_map.empty())
        {
            return;
        }

        LOG(INFO) << app_name() << " now stoping";

        //按创建相反的顺序来析构，从而可以解决析构中有相互依赖的情况
        ModuleMap_T::const_reverse_iterator it = m_module_map.rbegin();
        AppModuleBase* temp = NULL;
        while (it != m_module_map.rend())
        {
            temp = it->second;            
            if (temp != NULL)
            {
                temp->module_fini();
                delete temp;
                temp = NULL;
            }
            ++it;
        }

        m_module_map.clear();

        LOG(INFO) << app_name() << " stop completed!";
        sleep(1);
    }

private:
    AppModuleMgr(){}
    AppModuleMgr(const AppModuleMgr&);
    AppModuleMgr& operator=(const AppModuleMgr&);
    

private:
    typedef std::map<uint64_t, AppModuleBase*>     ModuleMap_T;
    ModuleMap_T   m_module_map;
};

#endif // _APP_MODULE_MGR_H_

