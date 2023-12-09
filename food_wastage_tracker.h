#ifndef FOOD_WASTAGE_TRACKER_H_
#define FOOD_WASTAGE_TRACKER_H_

#include <vector>

#include "food_wastage_record.h"
#include "food_wastage_report.h"

// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf


class FoodWastageTracker {
 public:
  FoodWastageTracker();
  bool AddRecord(FoodWastageRecord record);
  bool RemoveRecord(FoodWastageRecord record);
  const std::vector<FoodWastageRecord>& GetRecords() const;
  FoodWastageReport GenerateReport() const;

 private:
  std::vector<FoodWastageRecord> records_;
};

#endif