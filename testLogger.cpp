#include "CPPLogger.h"
#include <thread>
#include <unistd.h>
#include <iostream>

class simpleCustomLogger : public CustomLogger
{
public:
  void writeLogString(std::string message)
  {
    std::cout << "Custom - " << message << std::endl;
  }
};

void sendLogs()
{
  LOG(DEBUG) << "Log 1";
  LOG(INFO) << "Log 2";
  LOG(WARN) << "Log 3";
  LOG(ERROR) << "Log 4";
  LOG(FATAL) << "Log 5";
}

void threadedSendLogs()
{
  for(int i = 0; i < 10; i++)
    {
      LOG(DEBUG) << "Iteration " << i << " in thread " << std::this_thread::get_id();
      sendLogs();
      usleep(100000);
    }
}

int runTest()
{
  CPPLogger::getLog().setLogLevel(DEBUG);
  
  std::cout << "All Logs\n";
  sendLogs();
  std::cout << std::endl;

  CPPLogger::getLog().setLogLevel(INFO);
  std::cout << "Info or higher\n";
  sendLogs();
  std::cout << std::endl;
  
  CPPLogger::getLog().setLogLevel(WARN);
  std::cout << "Warning or higher\n";
  sendLogs();
  std::cout << std::endl;

  CPPLogger::getLog().setLogLevel(ERROR);
  std::cout << "Error or Higher\n";
  sendLogs();
  std::cout << std::endl;


  CPPLogger::getLog().setLogLevel(FATAL);
  std::cout << "Fatal or higher\n";
  sendLogs();
  std::cout << std::endl;
    
  CPPLogger::getLog().setLogLevel(DEBUG);

  std::thread thread1(threadedSendLogs);
  std::thread thread2(threadedSendLogs);
  thread1.join();
  thread2.join();

  return 0;
}

int main()
{
  /*CPPLogger::getLog().unSetLogMode(LOGMODE_STDOUT);
  std::cout << "Running log test for stdout only. " << std::endl << std::endl;
  runTest();

  std::cout << "Running test for file only. " << std::endl << std::endl;
  CPPLogger::getLog().setLogModeFile("/tmp/testlog_fonly.log");
  CPPLogger::getLog().unSetLogMode(LOGMODE_STDOUT);
  runTest();

  std::cout << "Running test with both stdout and file "<< std::endl << std::endl;
  CPPLogger::getLog().setLogModeFile("/tmp/testlog_both.log");
  CPPLogger::getLog().setLogModeStdOut();
  runTest();

  */
  CPPLogger::getLog().unSetLogMode(LOGMODE_FILE);
  CPPLogger::getLog().unSetLogMode(LOGMODE_STDOUT);
  CPPLogger::getLog().setLogModeCustom(new simpleCustomLogger());
  runTest();
  
  
  return 0;
}
