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
    int limit = 20000;
    while(x < limit){
        cout << "Task: " << i << ". Attempting to + 1.\n";
        mtx.lock();
        if(x < limit)
        {
            x += 1;
            std::ostringstream oss;
            oss << "Task: " << i << ". x is " << x << " after + 1.\n";
            cout << oss.str();
            mtx.unlock();
        } else 
        {
            mtx.unlock();
        }
        
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
    cout << "Main finished executing. x is " << x << ".\n";
    return 0;
}