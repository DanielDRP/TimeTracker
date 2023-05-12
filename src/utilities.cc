#pragma once
#include "../include/Activity.h"
#include <vector>

Activity* findActivity(std::vector<Activity>& activities, std::string& title) {
  for (auto& activity : activities) {
    if (activity.getTitle() == title) {
      return &activity;
    }
  }
  return nullptr;
}

void printActivities(std::vector<Activity>& activities) {
  for (auto& activity : activities) {
    std::cout << activity << std::endl;
  }
}
