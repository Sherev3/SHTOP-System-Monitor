#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    string hours;
    long hoursLong;

    string minutes;
    long minutesLong;

    // string seconds;
    // long secondsLong;

    hoursLong = seconds/3600;
    hours = std::to_string(hoursLong);
    
    return hours; 
}