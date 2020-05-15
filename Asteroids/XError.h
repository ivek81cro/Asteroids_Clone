#ifndef XERROR_H_
#define XERROR_H_

#include "stdafx.h"
#include "LogToFile.h"

class XError
{
  public:
    virtual void LogError(const char* message) = 0;

  protected:
    std::string message_detail_;
    std::string file_prefix_;
};

#endif // !XERROR_H_