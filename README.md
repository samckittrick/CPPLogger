##Super Simple C++ Logger

This program is intended to provide simple, thread safe logging functionality. It is conatined entirely in a single header for simplicity.

Currently, it logs to standard output or to a file or to a custom logger. The selection of a log mode is not exclusive and an application can set more than one at once.

**Example Usage:**
```
#include "CPPLogger.h"

int main()
{
  CPPLogger::getLog().setLogLevel(DEBUG);
  CPPLogger::getLog().setLogModeFile("/tmp/testlog.log");
  std::cout << "All Logs\n";
  LOG(DEBUG) << "Log 1";
  LOG(INFO) << "Log 2";
  LOG(WARN) << "Log 3";
  LOG(ERROR) << "Log 4";
  LOG(FATAL) << "Log 5";
  return 0;
}

```

The purpose of the custom logger is to allow logs to be redirected to application specific purposes that wouldn't normally be included in this tool.
Applications wishing to use this feature should extend and implement the CustomLogger class and then provide a dynamically allocated instance of the object to the CPPLogger tool.

Example custom logger and usage:
```
class simpleCustomLogger : public CustomLogger
{
public:
  void writeLogString(std::string message)
  {
    std::cout << "Custom - " << message << std::endl;
  }
};

CPPLogger::getLog().setLogModeCustom(new simpleCustomLogger());
```

