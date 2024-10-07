#include <unistd.h>  // for usleep

#include <array>
#include <atomic>
#include <cstdlib>  // for rand() and srand()
#include <iostream>
#include <thread>

std::array<std::atomic_int, 10> numbers;
std::thread ts[3];

using std::cout;

unsigned int ms_to_microseconds(unsigned int ms) { return ms * 1000; }

int generate_random_num(int min, int max) {
  int random_num = min + rand() % (max - min + 1);
  return random_num;
}

void Output() {
  static int period = ms_to_microseconds(1000);
  while (true) {
    for (int i : numbers) {
      if (i >= 0) {
        cout << ' ';
      }
      if (i < 100 && i > -100) {
        cout << ' ';
      }
      if (i < 10 && i > -10) {
        cout << ' ';
      }
      cout << i << '\t';
    }
    cout << '\n';
    usleep(period);
  }
}

void InsertRandomNumbersInRandomPlaces() {
  while (true) {
    usleep(ms_to_microseconds(500));
    numbers[generate_random_num(0, numbers.size() - 1)] =
        generate_random_num(-150, 150);
  }
}

void InsertRandomNumbers() {
  unsigned int index = 0;
  while (true) {
    usleep(ms_to_microseconds(500));
    numbers[index] = generate_random_num(-150, 150);
    if (index >= numbers.size() - 1) {
      index = 0;
    } else {
      ++index;
    }
  }
}

void Swap(std::atomic_int& a, std::atomic_int& b) {
  int temp_a = a;
  int temp_b = b;
  b = temp_a;
  a = temp_b;
}

void EnsureFirstIsLessThanLast() {
  while (true) {
    std::atomic_int& first_number = numbers[0];
    std::atomic_int& last_number = numbers[numbers.size() - 1];
    if (first_number > last_number) {
      Swap(first_number, last_number);
    }
  }
}

int main() {
  srand(time(nullptr));

  for (unsigned int i = 0; i < numbers.size(); ++i) {
    numbers[i] = 0;
  }
  ts[0] = std::thread(Output);
  ts[1] = std::thread(InsertRandomNumbers);
  ts[2] = std::thread(EnsureFirstIsLessThanLast);
  for (std::thread& t : ts) {
    if (t.joinable()) {
      t.join();
    }
  }
}