#include "plotdatareceiver.h"
#include <fstream>
#include <iostream>

PlotDataReceiver::PlotDataReceiver()
{
}

PlotDataReceiver::~PlotDataReceiver()
{

}

void PlotDataReceiver::readDataFromFile()
{
    double JD, R, RError;
    std::ifstream fin("d:/MyProjects/TerbiumTower/MariaDiploma/QtPlotsDrawer/build-PlotsDrawer-Desktop_Qt_5_6_0_MinGW_32bit-Debug/data.txt");

    if( fin.fail() )
    {
        int x = 0;
    }
    //fin.ignore();
    //fin.getline( "", 0 );

    while( !fin.eof() )
    {
        fin >> JD >> R >> RError;

        m_variablesTable["JD"].push_back( JD );
        m_variablesTable["R"].push_back( R );
        m_variablesTable["RError"].push_back( RError );
    }
}
