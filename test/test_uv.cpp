#include <iostream>
#include <uv.h>
#include <thread>
#include "uv_timer.h"
using namespace std;

void idle_cb(uv_idle_t* handle) {
    static int counter = 0;
    // std::cout << "run idle cb function." << std::endl;
    // if (counter++ >= 1000)
    //     uv_idle_stop(handle);
}


int main(int argc, char **argv)
{
    uv_loop_t *loop = uv_default_loop();
    
    // std::cout << this_thread::get_id() << std::endl;

    // std::cout << "hello world." << std::endl;


    // uv_run(loop,UV_RUN_DEFAULT);

    Timer timer;
    timer.start(0,100,[]()->void
    {
        std::cout << "hello world." << std::endl;
    });

    uv_idle_t idle;

    uv_idle_init(loop, &idle);

    uv_idle_start(&idle,idle_cb);

    Timer timer2;
    timer2.start(1000,100,[]()->void
    {
        std::cout << "there is an other func." << std::endl;
    });
   
    uv_run(uv_default_loop(),UV_RUN_DEFAULT);

    return 0;
}