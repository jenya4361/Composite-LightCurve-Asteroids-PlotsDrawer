#ifndef App_H
#define App_H

#include <memory>

class ManagersController;

class App
{
public:
    App();
    ~App();

    App* GetInstancePtr() { return static_cast< App* >( this ); }

    inline static std::shared_ptr< ManagersController >& getMC() { return m_mc; }

private:

    static std::shared_ptr< ManagersController > m_mc;

};

#endif // App_H
