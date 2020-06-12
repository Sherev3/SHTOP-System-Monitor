#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() 
{ 

    return pid_; 
}
void Process::Pid(int pid)
{
    pid_ = pid;
} 

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() 
{ 
    return processCpuUtl_; 
}

void Process::CpuUtilization(float processCpuUtl)
{
    processCpuUtl_ = processCpuUtl;
}

// TODO: Return the command that generated this process
string Process::Command() 
{ 
    return command_; 
}

void Process::Command(std::string command)
{
    command_ = command;
}

// TODO: Return this process's memory utilization
string Process::Ram() 
{ 
    return pidRamValue_; 
}
void Process::Ram(string pidRamValue)
{
    pidRamValue_ = pidRamValue;
}

// TODO: Return the user (name) that generated this process
string Process::User() 
{ 
    return userName_; 
}

void Process::User(string userName)
{
    userName_ = userName;
}
// TODO: Return the age of this process (in seconds)
long int Process::UpTime() 
{ 
    return uptime_; 
}
void Process::UpTime(long uptime)
{
    uptime_ = uptime;
}
// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const 
{ 

    if( processCpuUtl_ < a.processCpuUtl_)
    {
        return true; 
    }
    else
    {
        return false;
    }
    
}