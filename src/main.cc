#include <atomic>
#include <chrono>
#include <thread>

#include "../include/Activity.h"
#include "system_services.cc"
#include "utilities.cc"


std::atomic<bool> stop(false);

void listenForEnter();

int main() {
  std::vector<Activity> activities;
  std::string window_title = getActiveProgram();
  Activity* currentActivity = new Activity(window_title);
  activities.push_back(*currentActivity);
  currentActivity = findActivity(activities, window_title);
  std::chrono::system_clock::time_point startTime =
      std::chrono::system_clock::now();
  std::thread inputThread(listenForEnter);

  while (!stop) {
    window_title = getActiveProgram();
    if (currentActivity->getTitle() != getActiveProgram()) {
      std::chrono::system_clock::time_point stopTime =
          std::chrono::system_clock::now();
      std::chrono::duration<double> elapsedTime = stopTime - startTime;
      currentActivity->updateTimeElapsed(elapsedTime.count());

      if (findActivity(activities, window_title) == nullptr) {
        currentActivity = new Activity(window_title);
        activities.push_back(*currentActivity);
        currentActivity = findActivity(activities, window_title);
      } else {
        currentActivity = findActivity(activities, window_title);
      }
      startTime = std::chrono::system_clock::now();
    }
    Sleep(2000);
  }
  std::chrono::system_clock::time_point stopTime =
          std::chrono::system_clock::now();
      std::chrono::duration<double> elapsedTime = stopTime - startTime;
      currentActivity->updateTimeElapsed(elapsedTime.count());
  inputThread.join();
  printActivities(activities);
  return 0;
}

void listenForEnter() {
  std::cout << "Press Enter to see the results..." << std::endl;
  std::cin.get();

  stop = true;
}