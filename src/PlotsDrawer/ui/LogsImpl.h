#ifndef LogsImpl_H
#define LogsImpl_H

#include <string>
#include <fstream>

class QString;
class QLabel;
class QMainWindow;

class LogsImpl
{
public:
    LogsImpl();
    ~LogsImpl();

    void assignUI( const QMainWindow* ui );

    void addLog( const QString& str );

private:

    QLabel* m_logLabel;
    std::ofstream m_fout;
};

#endif // LogsImpl_H
