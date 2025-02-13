#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>

struct Timer{
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration;

    Timer(){
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer(){
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;

        //count returns the duration in seconds
        double ms = duration.count() * 1000.0;
        std::cout << ms << "ms " << std::endl;
    }
};

void Function(){
    //The destructor of Timer will be called when the function ends, because the Timer object is created on the stack
    Timer timer;

    for(int i = 0; i < 100; i++){
        std::cout << "Hello" << std::endl;
    }
}

int main(){
    using namespace std::literals::chrono_literals;

    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << duration.count() << "s " << std::endl;

    Function();

    // Get the current time point using system clock
    //It returns time_point
    auto now = std::chrono::system_clock::now();

    // Convert to time_t (which represents seconds since the epoch)
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert to a human-readable format
    std::cout << "Current time: " << std::ctime(&now_c) << std::endl;
    //Unix epoch (January 1, 1970)
    auto duration_since_epoch = now.time_since_epoch();
    // Convert duration to seconds
    auto duration_in_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration_since_epoch);

    std::cout << "Duration since epoch (in seconds): " << duration_in_seconds.count() << std::endl;

    return 0;
}