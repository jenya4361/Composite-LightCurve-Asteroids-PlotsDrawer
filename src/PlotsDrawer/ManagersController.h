#ifndef ManagersController_H
#define ManagersController_H

#include <memory>

class LogManager;
class PlotsManager;

using LogManagerPtr = std::shared_ptr< LogManager >;
using PlotsManagerPtr = std::shared_ptr< PlotsManager >;

class ManagersController
{
public:
    ManagersController();
    ~ManagersController();

    inline static const LogManagerPtr& getLogManager() { return m_logManager; }
    inline static const PlotsManagerPtr& getPlotsManager() { return m_plotsManager; }

private:

   static LogManagerPtr m_logManager;
   static PlotsManagerPtr m_plotsManager;

};

#endif // ManagersController_H
