#ifndef MainIncludes_H
#define MainIncludes_H

#include <memory>
#include <string>
#include <sstream>
#include <QMainWindow>
#include "managers/LogManager.h"
#include "App.h"
#include "ManagersController.h"
#include <QCoreApplication>

template< class T >
T FindUIElementInWindow( const QMainWindow* ui, const std::string& objectName )
{
    if( !ui )
        return nullptr;
    QWidget* centralWidget = ui->findChild<QWidget*>( "centralWidget" );
    if( !centralWidget )
        return nullptr;

    return centralWidget->findChild<T>( QString( objectName.c_str() ) );
}

inline void PLog( const std::string& str )
{
    const LogManagerPtr& logMng = App::getMC()->getLogManager();
    if( logMng )
        logMng->addLog( str );
}

inline void PLogIF( bool condition, const std::string& str )
{
    if( condition )
        PLog( str );
}

#define LOG_RETURN_IF( condition, str ) PLogIF( condition, str ); if( condition ) return;

inline bool IsFloat( const std::string& myString )
{
    std::istringstream iss( myString );
    float f;
    iss >> std::noskipws >> f;

    return iss.eof() && !iss.fail();
}

#endif // MainIncludes_H
