#ifndef PlotDataReceiver_H
#define PlotDataReceiver_H

#include <QMainWindow>
#include <unordered_map>

using VariablesTable = std::unordered_map< std::string, std::vector< double > >;

class PlotDataReceiver
{
public:
    PlotDataReceiver();
    ~PlotDataReceiver();

    void readDataFromFile();
    const VariablesTable& getDataFromFile() const { return m_variablesTable; }

private:

    VariablesTable m_variablesTable;
};

#endif // PlotDataReceiver_H
