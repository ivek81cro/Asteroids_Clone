#ifndef XFILEERROR_H_
#define XFILEERROR_H_

#include "XError.h"

class XFileError : public XError
{
  public:
    XFileError(const char* message_detail);

    void LogError(const char* message) override;
};

#endif