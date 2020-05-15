#include "stdafx.h"
#include "XFileError.h"
#include"FilePaths.h"
#include "Messages.h"

XFileError::XFileError(const char* message_detail)
{
    message_detail_ = message_detail;
    file_prefix_    = "FileError";
}

void XFileError::LogError(const char* message)
{
    LogToFile log(PATH_LOG_FILE, file_prefix_);

    log << LogToFile::e_logType::LOG_ERROR;
    log << message;
    log << message_detail_;
}
