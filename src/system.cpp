#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


Processor& System::Cpu() 
{     
    return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() 
{ 
    string userName,command;
    long uptime;
    float processCpuUtl;
    vector<int> pids = LinuxParser::Pids();
    

    for(int pid: pids)
    {
        Process dummy;
    	userName = LinuxParser::User(pid);
        dummy.Pid(pid);
        dummy.User(userName);

        command  = LinuxParser::Command(pid);
        dummy.Command(command);

        uptime =  LinuxParser::UpTime(pid);  
        dummy.UpTime(uptime);
        
        processCpuUtl = LinuxParser::ProcessCpuUtil(pid);
        dummy.CpuUtilization(processCpuUtl);

        processes_.push_back(dummy);
    }
    

    return processes_; 
}


std::string System::Kernel()
 {
     return LinuxParser::Kernel();
 }

float System::MemoryUtilization()
 { 
    return LinuxParser::MemoryUtilization();
 }

std::string System::OperatingSystem()
 { 
     return LinuxParser::OperatingSystem();
 }

int System::RunningProcesses() 
{ 
  return LinuxParser::RunningProcesses(); 
}

int System::TotalProcesses() 
{ 
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() 
{ 
    return LinuxParser::UpTime(); 
}