#include <unistd.h> // for usleep
#include <iostream>
#include <thread>

int counter_1 = 0;
int counter_2 = 0;
int counter_3 = 0;

std::thread ts[4];

int ms_to_micro_sec(int x) { return (x * 1000); }

using std::cout;

void Count1() {
  while (true) {
    ++counter_1;
    usleep(ms_to_micro_sec(200));
  }
}

void Count2() {
  while (true) {
    ++counter_2;
    usleep(ms_to_micro_sec(10));
  }
}

void Count3() {
  while (true) {
    ++counter_3;
    usleep(ms_to_micro_sec(50));
  }
}

void DisplayCounters() {
  while (true) {
    usleep(ms_to_micro_sec(500));
    cout << "Counter 1: " << counter_1 << ";\t" << "Counter 2: " << counter_2
         << ";\t" << "Counter 3: " << counter_3 << '\n';
  }
}

int main() {
  ts[1] = std::thread(Count2);
  ts[2] = std::thread(Count3);
  ts[3] = std::thread(DisplayCounters);
  while (true) {
    if (counter_2 >= 100 && counter_3 >= 100) {
      ts[0] = std::thread(Count1);
      break;
    }
  }
  ts[1].join();
  ts[2].join();
  ts[3].join();
  ts[0].join();
}