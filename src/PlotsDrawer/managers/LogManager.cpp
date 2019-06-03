#include "LogManager.h"

LogManager::LogManager()
{
}

LogManager::~LogManager()
{

}

void LogManager::setLogCallback( LogCallback callback )
{
    m_callback = callback;
}

void LogManager::addLog( const std::string& str )
{
    if( m_callback )
        m_callback( str );
}
