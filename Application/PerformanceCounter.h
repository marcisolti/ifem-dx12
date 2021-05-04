#define NOMINMAX
#include <windows.h>

class PerformanceCounter
{
public:

    PerformanceCounter()
    {
        // reset the counter frequency
        QueryPerformanceFrequency(&timerFrequency);
        StartCounter();
    }

    void StartCounter(); // call this before your code block
    void StopCounter(); // call this after your code block

    // read elapsed time (units are seconds, accuracy is up to microseconds)
    double GetElapsedTime();

protected:
    LARGE_INTEGER timerFrequency;
    LARGE_INTEGER startCount, stopCount;
};

inline void PerformanceCounter::StartCounter()
{
    QueryPerformanceCounter(&startCount);
}

inline void PerformanceCounter::StopCounter()
{
    QueryPerformanceCounter(&stopCount);
}


inline double PerformanceCounter::GetElapsedTime()
{
    return ((double)(stopCount.QuadPart - startCount.QuadPart))
        / ((double)timerFrequency.QuadPart);
}