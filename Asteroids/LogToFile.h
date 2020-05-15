#ifndef LOGTOFILE_H_
#define LOGTOFILE_H_

class LogToFile
{
  public:
    enum class e_logType
    {
        LOG_ERROR,
        LOG_WARNING,
        LOG_INFO
    };

    LogToFile(const char* filename, std::string& prefix);

    ~LogToFile();    

    friend LogToFile& operator<<(LogToFile& logger, const e_logType l_type)
    {

        switch (l_type)
        {
            case LogToFile::e_logType::LOG_ERROR:
                logger.myFile << "[ERROR]: ";
                break;

            case LogToFile::e_logType::LOG_WARNING:
                logger.myFile << "[WARNING]: ";
                break;

            default: logger.myFile << "[INFO]: "; break;
        }

        return logger;
    }

    friend LogToFile& operator<<(LogToFile& logger, std::string message)
    {

        logger.myFile << message << std::endl;
        return logger;
    }

    LogToFile(const LogToFile&) = delete;
    LogToFile& operator=(const LogToFile&) = delete;

  private:
    std::fstream myFile;
};

#endif // !LOGTOFILE_H_