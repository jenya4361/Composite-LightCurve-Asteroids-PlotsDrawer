#ifndef LogManager_H
#define LogManager_H

#include <string>
#include <memory>
#include <functional>

class LogManager;

using LogManagerPtr = std::shared_ptr< LogManager >;
using LogCallback = std::function<void( const std::string& )>;

class LogManager
{
public:
    LogManager();
    ~LogManager();

    void setLogCallback( LogCallback callback );
    void addLog( const std::string& str );

private:

    LogCallback m_callback;

};

#endif // LogManager_H
