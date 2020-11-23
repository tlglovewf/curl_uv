#ifndef _UV_TIMER_H_
#define _UV_TIMER_H_

#include "noncopyable.h"
#include <functional>
#include <memory>

class Timer : private noncopyable 
{
public:
    Timer();
    ~Timer();

    /*
     * @param timeout  start time (ms)
     * @param repeat   interanl   (ms)
     * @param func     cb function 
     */ 
    void start(int timeout, int repeat, std::function<void()>&& cbf);

    void stop();

private:
    class Impl;
    std::unique_ptr<Impl> mpImpl;
};




#endif