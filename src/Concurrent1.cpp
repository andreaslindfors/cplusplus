#include <iostream>
#include <string>
#include <sstream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

std::mutex mtx;

int x;

void callback(const std::string& data)
{
    cout << "Callback called because: " << data << ".\n";
}

void do_add(int i){
    while(1){
        cout << "Attempting to + 1 in task " << i << ".\n";
        mtx.lock();
        x += 1;
        std::ostringstream oss;
        oss << "x is " << x << " after + 1. I am loop " << std::to_string(i) + ".\n";
        cout << oss.str();
        mtx.unlock();
        }
        callback("async task done");
}

int main()
{
    x = 0;
    cout  << "x is " << std::to_string(x) << ".\n";
    std::thread threads[3];
    for(int i = 0; i < 3; i++){
        threads[i] = std::thread(do_add,i);
        cout << "Async task " << i << " launched.\n";
    }
    for (auto& th : threads) th.join();
    cout << "Main finished executing.\n";
    return 0;
}