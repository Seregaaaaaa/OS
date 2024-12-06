#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class Monitor {
private:
    mutex mtx;
    condition_variable cv;
    bool event_occurred = false;
    int event = 0;
    
public:
    void produce() {
        while (true) {
            this_thread::sleep_for(chrono::seconds(1));
            unique_lock<mutex> lock(mtx);
            event_occurred = true;
            event += 1;
            cout << "Событие отправлено: " << event << endl;
            cv.notify_one();
        }
    }

    void receive() {
        while (true) {
            unique_lock<mutex> lock(mtx);
            cv.wait(lock, [this] { return event_occurred; });
            cout << "Событие получено: " << event << endl;
            event_occurred = false;
        }
    }
};

int main() {
    Monitor monitor;
    thread producer(&Monitor::produce, &monitor);
    thread receiver(&Monitor::receive, &monitor);

    producer.join();
    receiver.join();

    return 0;
}
