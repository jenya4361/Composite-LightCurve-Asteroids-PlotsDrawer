#include "ManagersController.h"
#include "managers/LogManager.h"
#include "managers/PlotsManager.h"

ManagersController::ManagersController()
{
    m_logManager = LogManagerPtr( new LogManager() );
    m_plotsManager = PlotsManagerPtr( new PlotsManager() );
}

ManagersController::~ManagersController()
{

}

LogManagerPtr ManagersController::m_logManager = nullptr;
PlotsManagerPtr ManagersController::m_plotsManager = nullptr;
