#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"


using std::stof;
using std::string;
using std::to_string;
using std::vector;

//  read data from the filesystem
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

// read data from the filesystem
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

// TODO: Update this to use std::filesystem
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

// Read and return the system memory utilization
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

//  Read and return the command associated with a process
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

//  Read and return the memory used by a process
string LinuxParser::Ram(int pid) 
{ 
  string line,pidString,pidDirectory, vmLabel,vmSizeValue;
  float size{0};
  int intsize{0};


  pidString = to_string(pid);
  pidDirectory = "/" + pidString;

  std::ifstream filestream(kProcDirectory + pidDirectory + kStatusFilename);
  if (filestream.is_open()) 
  {
    while(std::getline(filestream, line))
    {
      std::istringstream linestream(line);
      linestream >> vmLabel >> vmSizeValue;
      if(vmLabel == "VmSize:")
      {
        size = std::stof(vmSizeValue);
        size = size * KBTOMEG;
        size = round(size);
        intsize = int(size);
        vmSizeValue = to_string(intsize); 
        break;        
      }
    }
  }
  else
  {
    return string();
  }
  

  return vmSizeValue; 
}

// Read and return the user ID associated with a process

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
 
  long uptime,systemUptime;
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
    
    uptime = std::stol(elemVec[START_INDEX]);
    uptime = uptime /sysconf(_SC_CLK_TCK);
    systemUptime = UpTime();
    uptime = systemUptime - uptime;
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

    uTime = std::stol(elemVec[UTIME_INDEX]);
    sTime = std::stol(elemVec[STIME_INDEX]);
    cuTime = std::stol(elemVec[CUTIME_INDEX]);
    csTime = std::stol(elemVec[CSTIME_INDEX]);
    startTime = std::stol(elemVec[START_INDEX]);

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