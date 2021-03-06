#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  int Pid();                               // TODO: See src/process.cpp
  void Pid(int pid);
  std::string User();                      // TODO: See src/process.cpp
  void User(std::string userName);
  std::string Command();                   // TODO: See src/process.cpp
  void Command(std::string command);
  float CpuUtilization();                  // TODO: See src/process.cpp
  void CpuUtilization(float processCpuUtl);
  std::string Ram();                       // TODO: See src/process.cpp
  void Ram(std::string pidRamValue);
  long int UpTime();                       // TODO: See src/process.cpp
  void UpTime(long uptime);
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // Declare any necessary private members
 private:
    std::string userName_;
    int pid_;
    std::string command_;
    long uptime_{0};
    float processCpuUtl_{0};
    std::string pidRamValue_;
};

#endif