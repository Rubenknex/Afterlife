#include "Logger.h"
 
namespace al
{
Logger* Logger::mLogger = NULL;
 
Logger::Logger()
{
    mOfStream.open(LOG_FILE);
}
 
Logger::~Logger()
{
    if (mOfStream.is_open())
        mOfStream.close();
}
 
Logger* Logger::instance()
{
    if (mLogger == NULL)
        mLogger = new Logger();
 
    return mLogger;
}
 
void Logger::write(const std::string& category, const std::string& message)
{
    std::ostringstream oss;
    oss << "[" << category.c_str() << "]: " << message.c_str() << std::endl;
 
    mOfStream.write(oss.str().c_str(), static_cast<std::streamsize>(oss.str().length()));
}
}
 
