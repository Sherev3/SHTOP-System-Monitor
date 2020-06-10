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
    string userName;

    vector<int> pids = LinuxParser::Pids();
    
    //std::cout <<"\n"<< "pid 0: "<< pids[0] << "\n";
    userName = LinuxParser::User(pids[0]);
    std::cout<< "userName: " << userName << "\n";

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