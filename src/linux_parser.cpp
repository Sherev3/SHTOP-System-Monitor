#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version,kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  else
  {
    return string();
  }
  
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() 
{ 
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  string line;
  string memTotalStringValue;
  string memTotalName;
  float memTotalValue;

  string memFreeStringValue;
  string memFreeName;
  float memFreeValue;

  float utlMem = 0;

  if (filestream.is_open()) 
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);

    linestream >> memTotalName >> memTotalStringValue;
    memTotalValue = std::stof(memTotalStringValue);

    std::getline(filestream, line);
    std::istringstream linestream2(line);
    linestream2 >> memFreeName >> memFreeStringValue;
    memFreeValue = std::stof(memFreeStringValue);

    utlMem = (memTotalValue - memFreeValue)/memTotalValue;
  }
  else
  {
    return 0.0;
  }
  
  return utlMem; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() 
{ 
  std::ifstream filestream(kProcDirectory + kUptimeFilename);  
  string line;
  string upTime,dummy;
  long upTimelong;

  if (filestream.is_open())
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
    upTimelong = std::stol(upTime);
  }
  else
  {
    return 0;
  }
  
  return upTimelong; 
} 

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

//  Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

//  Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

//  Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

//  Read and return the total number of processes
int LinuxParser::TotalProcesses() 
{ 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string processName,processNumber;
  int processNumberInt;
  string line;
  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
      {
        std::istringstream linestream(line);
        linestream >> processName >> processNumber;
        if(processName == "processes")
        {
          processNumberInt = std::stoi(processNumber);
          break;
        }

      }
  }
  return processNumberInt; 
}

int LinuxParser::RunningProcesses() 
{ 
  std::ifstream filestream(kProcDirectory + kStatFilename);
  string processRunningName,procsRunningNumber;
  string line;
  int procsRunningNumberInt;

  if (filestream.is_open())
  {
    while (std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> processRunningName >> procsRunningNumber;
      if(processRunningName == "procs_running")
      {
        procsRunningNumberInt = std::stoi(procsRunningNumber);
        break;
      }
    }
  }
  return procsRunningNumberInt; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) 
{ 
  string line,pidString,pidDirectory;
  pidString = to_string(pid);
  pidDirectory = "/" + pidString;

  std::ifstream filestream(kProcDirectory + pidDirectory + kCmdlineFilename);
  if (filestream.is_open()) 
  {
    std::getline(filestream, line);
  }
  else
  {
    return string(); 
  }
  
  return line; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process

string LinuxParser::Uid(int pid) 
{ 
  string pidString,line,pidDirectory,Uidlabel, UidValue;
  pidString = to_string(pid);

  pidDirectory = "/" + pidString;
  std::ifstream filestream(kProcDirectory + pidDirectory + kStatusFilename);
  if (filestream.is_open()) 
  {
    
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> Uidlabel >> UidValue;
      if(Uidlabel == "Uid:")
      {
        break;
      }
    }

  }
  else
  {
    return string(); 
  }
 
  return UidValue;
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) 
{ 
  string userID = Uid(pid);
  //std::cout << "\n" << "userID: "<<userID << "\n";
  string line, userName, x, userIDstring,token;

  std::ifstream filestream(kPasswordPath);

  if(filestream.is_open())
  {
    while(std::getline(filestream, line))
    {
      
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> userName >> x >> userIDstring;

      if(userIDstring == userID)
      {
        break;
      }
    }
  }
  else
  {
    return string();
  }
  
  return userName;
}

// Read and return the uptime of a process
long LinuxParser::UpTime(int pid) 
{
  string line,pidString,pidDirectory;
 
  long uptime;
  pidString = to_string(pid);
  pidDirectory = "/" + pidString;

  std::ifstream filestream(kProcDirectory + pidDirectory + kStatFilename);  
  if (filestream.is_open()) 
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<std::string> begin(linestream);
    std::istream_iterator<std::string> end;
    std::vector<std::string> elemVec(begin, end);
    
    uptime = std::stol(elemVec[21]);
    uptime = uptime /sysconf(_SC_CLK_TCK);
  }
  else
  {
    return 0; 
  }
  
  return uptime; 
}
//Get the Cpu Utilization for each process
float LinuxParser::ProcessCpuUtil(int pid) 
{ 
  string line,pidString,pidDirectory;
  long systemUptime = UpTime();
  long uTime,sTime,cuTime, csTime,startTime, totalTime, seconds;
  float cpuUsage{0};

  pidString = to_string(pid);
  pidDirectory = "/" + pidString;

  std::ifstream filestream(kProcDirectory + pidDirectory + kStatFilename);
  if (filestream.is_open()) 
  {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::istream_iterator<std::string> begin(linestream);
    std::istream_iterator<std::string> end;
    std::vector<std::string> elemVec(begin, end);

    uTime = std::stol(elemVec[13]);
    sTime = std::stol(elemVec[14]);
    cuTime = std::stol(elemVec[15]);
    csTime = std::stol(elemVec[16]);
    startTime = std::stol(elemVec[21]);

    totalTime = uTime + sTime + cuTime + csTime;

    seconds = systemUptime - (startTime / sysconf(_SC_CLK_TCK) );
    cpuUsage = (float((totalTime / sysconf(_SC_CLK_TCK))) / float(seconds));
  }
  else
  {
    return 0; 
  }

  return cpuUsage; 
}