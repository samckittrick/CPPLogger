##Super Simple C++ Logger

This program is intended to provide simple, thread safe logging functionality. It is conatined entirely in a single header for simplicity.

Currently, it logs to standard output or to a file.

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
