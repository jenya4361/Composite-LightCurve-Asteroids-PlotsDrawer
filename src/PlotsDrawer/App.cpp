#include "App.h"
#include "ManagersController.h"

App::App()
{
    m_mc = std::shared_ptr<ManagersController>( new ManagersController () );
}

App::~App()
{

}

std::shared_ptr<ManagersController> App::m_mc = nullptr;
