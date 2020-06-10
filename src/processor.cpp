#include "processor.h"
#include "linux_parser.h"
#include <iostream>
#include <string>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{ 
    std::string line,cpu;
    float cpuPercentage;
    std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
    if (stream.is_open()) 
    {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> cpu >> user_ >> nice_ >> system_ >> idle_ >> ioWait_\
	    >> irq_ >> softIrq_ >> steal_ >> guest_ >> guestNice_;       
        
        prevIdleTotal_ = prevIdle_ + prevIoWait_;
        //Idle = idle + iowait
        idleTotal_ = idle_ + ioWait_;

        //PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
        prevNonIdle_ = prevUser_ + prevNice_ + prevSystem_ + prevIrq_+ prevSoftIrq_ + prevSteal_;
        //NonIdle = user + nice + system + irq + softirq + steal
        nonIdle_ = user_ + nice_ + system_ +irq_ + softIrq_ + steal_;

        //PrevTotal = PrevIdle + PrevNonIdle
        prevTotal_ = prevIdle_ + prevNonIdle_;
        //Total = Idle + NonIdle
        total_ = idle_ + nonIdle_;

        // differentiate: actual value minus the previous one
        //totald = Total - PrevTotal
        totald_ = total_ - prevTotal_;
        //idled = Idle - PrevIdle
        idled_ = idle_ - prevIdle_;
        //CPU_Percentage = (totald - idled)/totald 
        cpuPercentage = (totald_ - idled_)/totald_;

        prevUser_ = user_;
        prevNice_ = nice_;
        prevSystem_ = system_;
        prevIdle_ = idle_;
        prevIoWait_ = ioWait_;
        prevIrq_ = irq_;
        prevSoftIrq_ = softIrq_;
        prevSteal_ = steal_;
        prevGuest_ = guest_;
        prevGuestNice_ = guestNice_;
        prevIdle_ = idle_;
        prevNonIdle_ = nonIdle_;
    }
    else
    {
       cpuPercentage = 0; 
    }
    
    

    return cpuPercentage; 
}