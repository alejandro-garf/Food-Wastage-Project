// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf

#include "food_wastage_tracker.h"

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

FoodWastageReport FoodWastageTracker::GenerateReport() const {
  FoodWastageReport report(records_);
  return report;
}