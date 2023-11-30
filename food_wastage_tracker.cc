// Alejandro Fonseca 
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu 
// alejandro-garf

#include "food_wastage_tracker.h"

// ========================= YOUR CODE HERE =========================
// This implementation file is where you should implement
// the member functions declared in the header (food_wastage_tracker.h), only
// if you didn't implement them inline within food_wastage_tracker.h.
//
// Remember to specify the name of the class with :: in this format:
//     <return type> MyClassName::MyFunction() {
//        ...
//     }
// to tell the compiler that each function belongs to the FoodWastageTracker
// class.
// ===================================================================
FoodWastageTracker::FoodWastageTracker() {}

bool FoodWastageTracker::AddRecord(FoodWastageRecord record) {
  for (FoodWastageRecord& r : records_) {
    if (r.Equals(record)) {
      return false;
    }
  }
  records_.push_back(record);
  return true;
}
bool FoodWastageTracker::RemoveRecord(FoodWastageRecord record) {
  int i;
  for (i = 0; i < records_.size(); i++) {
    if (records_[i].Equals(record)) {
      break;
    }
  }
  if (i < records_.size()) {
    records_.erase(records_.begin() + i);
    return true;
  }
  return false;
}
const std::vector<FoodWastageRecord>& FoodWastageTracker::GetRecords() const {
  return records_;
}