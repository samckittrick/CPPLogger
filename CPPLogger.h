/*
    Copyright (C) 2017 Scott McKittrick

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SAMLogger.  If not, see <http://www.gnu.org/licenses/>.
    
    By: Scott McKittrick

*/

#ifndef CPPLOGGER_H
#define CPPLOGGER_H

#include <string>
#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>

#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5

class CPPLogger 
{
 public:
  static CPPLogger& getLog() {
    static CPPLogger instance;
    return instance;
  }

  void setLogLevel(int logLevel)
  {
    
    std::lock_guard<std::mutex> lockGuard(mutex);
    if(logLevel < 6 && logLevel > 0)
      debugLevel = logLevel;
  }
 
  void writeLog(int severity, std::string message) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    if(severity >= debugLevel)
      {
	std::string time = getTimeStamp();
	std::string severityString = getSeverityString(severity);
	std::cout << time << ": " << severityString << " - " << message << std::endl;
      }
  }
    
 private:
  int debugLevel = ERROR; //Default to errors 
 
  //Block Constructors to ensure singleton
  CPPLogger() {}
  CPPLogger(CPPLogger const&);
  void operator=(CPPLogger const&);

  //Mutex for synchronization
  std::mutex mutex;

  std::string getTimeStamp()
    {
      time_t rawTime;
      time(&rawTime);
      tm *curTime = gmtime(&rawTime);
      char buffer[30];
      std::strftime(buffer, 30, "%Y-%m-%d %H:%M:%S %Z", curTime);
      std::string timeString(buffer);
      return timeString;
    }

  std::string getSeverityString(int severity)
    {
      switch(severity)
	{
	case DEBUG:
	  return "Debug";
	case INFO:
	  return "Info";
	case WARN: 
	  return "Warning";
	case ERROR: 
	  return "Error";
	case FATAL:
	  return "Fatal";
	default:
	  return "Unkown";
	}
    }
};

class LOG
{
 public:
  LOG() { debugLevel = ERROR; }
  LOG(int severity) { debugLevel = severity; }
  ~LOG() {
    CPPLogger::getLog().writeLog(debugLevel, stream.str());
  }

  template <typename T>
    LOG& operator<<(T const & value)
    {
      stream << value;
      return *this;
    }
  
 private:
  int debugLevel;
  std::stringstream stream;

};      
#endif
