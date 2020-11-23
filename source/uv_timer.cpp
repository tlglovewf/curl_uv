#include "uv.h"
#include <stdexcept>
#include "uv_timer.h"

class Timer::Impl
{
public: 

    Impl() : mhandle(new uv_timer_t) 
    {
        auto* loop = uv_default_loop();
        if (uv_timer_init(loop, mhandle) != 0) {
            throw std::runtime_error("Failed to initialize timer.");
        }

        handle()->data = this;
        uv_unref(handle());
    }

    ~Impl() {
        uv_close(handle(), [](uv_handle_t* h) {
            delete reinterpret_cast<uv_timer_t*>(h);
        });
    }

    void start(uint64_t timeout, uint64_t repeat, std::function<void ()>&& cb) 
    {
        mfCb = std::move(cb);
        if (uv_timer_start(mhandle, timerCallBack, timeout, repeat) != 0) {
            throw std::runtime_error("Failed to start timer.");
        }
    }

    void stop() 
    {
        mfCb = nullptr;
        if (uv_timer_stop(mhandle) != 0) {
            throw std::runtime_error("Failed to stop timer.");
        }
    }


protected:
    static void timerCallBack(uv_timer_t *hd)
    {
        reinterpret_cast<Impl*>(hd->data)->mfCb();
    }

    uv_handle_t* handle()
    {
        
        return reinterpret_cast<uv_handle_t*>(mhandle);
    }
private:
    uv_timer_t           *mhandle;
    std::function<void()> mfCb;

};  
Timer::Timer()
    : mpImpl(std::make_unique<Timer::Impl>()) {
}
Timer::~Timer() = default;
/*
 * @param timeout  start time (ms)
 * @param repeat   interanl   (ms)
 * @param func     cb function 
 */ 
void Timer::start(int timeout, int repeat, std::function<void()>&& cbf)
{
    mpImpl->start(timeout,repeat,std::move(cbf));
}

void Timer::stop()
{
    mpImpl->stop();
}
