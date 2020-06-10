#ifndef PROCESSOR_H
#define PROCESSOR_H


class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float user_ = 0;
    float prevUser_ = 0;
 
    float nice_ = 0;
    float prevNice_ = 0;
 
    float system_ = 0;
    float prevSystem_ = 0;

    float idle_ = 0;
    float prevIdle_ = 0;

    float ioWait_ = 0;
    float prevIoWait_ = 0;

    float irq_ = 0;
    float prevIrq_ = 0;

    float softIrq_ = 0; 
    float prevSoftIrq_ = 0;

    float steal_ = 0;
    float prevSteal_ = 0;

    float guest_ = 0;
    float prevGuest_ = 0;

    float guestNice_ = 0;
    float prevGuestNice_ = 0;

    float nonIdle_ = 0;
    float prevNonIdle_ = 0;

    float prevTotal_ = 0;
    float total_ = 0;

    float totald_ = 0;
    float idled_ = 0;
 
    float idleTotal_ = 0;
    float prevIdleTotal_ = 0;
};

#endif