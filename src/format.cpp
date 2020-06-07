#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    string hours = "";
    long hoursLong;

    string minutes = "";
    long minutesLong;

    string sec = "";
    long secondsLong;

    string timeString;

    minutesLong = seconds / 60;

    hoursLong = minutesLong / 60;

    minutesLong = minutesLong % 60;

    secondsLong = seconds % 60;

    if(hoursLong < 10)
    {
        hours = "0" + std::to_string(hoursLong);
    }
    else
    {
        hours = std::to_string(hoursLong);
    }
    
    if(minutesLong < 10)
    {
        minutes = "0" + std::to_string(minutesLong);
    }
    else
    {
        minutes = std::to_string(minutesLong);
    }

    if(secondsLong < 10)
    {
        sec = "0" + std::to_string(secondsLong);
    }
    else
    {
        sec = std::to_string(secondsLong);
    } 

    timeString = hours  + ":" + minutes + ":" + sec;
    return timeString; 
}