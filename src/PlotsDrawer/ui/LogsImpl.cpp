#include "LogsImpl.h"
#include <QLabel>
#include <QLayout>
#include "MainIncludes.h"

LogsImpl::LogsImpl()
{
    m_fout.open( "log.txt" );
}

LogsImpl::~LogsImpl()
{
    m_fout.close();
}

void LogsImpl::assignUI( const QMainWindow* ui )
{
    m_logLabel = FindUIElementInWindow<QLabel*>( ui, "logLabel" );
}

void LogsImpl::addLog( const QString& str )
{
    if( !m_logLabel )
        return;

    m_logLabel->setStyleSheet( "QLabel { color : blue }" );
    m_logLabel->setText( str );
    m_fout << "| PlotsDrawer Log | " << std::string( str.toLocal8Bit() ) << "\n";
    printf( str.toLocal8Bit() );
}
