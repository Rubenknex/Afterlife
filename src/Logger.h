#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
 
#include <fstream>
#include <sstream>
#include <string>
 
#define LOG_FILE "log.txt"
 
namespace al
{
class Logger
{
private:
    Logger();
    ~Logger();
 
public:
    static Logger* instance();
 
    void write(const std::string& category, const std::string& message);
 
private:
    static Logger* mLogger;
 
    std::ofstream mOfStream;
};
}
 
#endif // LOGGER_H_INCLUDED
 
