#include "headers/utils.hpp"
#include <ctime>
#include <sys/syslog.h>
#include <string>

void write_log(int priority, const std::string &msg){
  std::time_t time = std::time(nullptr);
  syslog(priority, "%s: %s", std::ctime(&time), msg.c_str());
}
