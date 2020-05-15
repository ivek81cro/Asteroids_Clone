#include "stdafx.h"
#include "LogToFile.h"

LogToFile::LogToFile(const char* filename, std::string& prefix)
{
    
    auto        t    = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(t);
    
    std::string fname = "";
    
    fname.append(filename);
    fname.append(prefix);
    fname.append(".txt");

    myFile.open(fname, std::fstream::in | std::fstream::out | std::fstream::app);

    // Write the first lines
    if (myFile.is_open())
    {
        myFile << "Log created at:" << std::ctime(&time);
    }
}

LogToFile::~LogToFile()
{

    if (myFile.is_open())
    {
        myFile << "Log_End\n" << std::endl;

        myFile.close();
    }
}
