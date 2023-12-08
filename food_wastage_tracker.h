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

// ======================= YOUR CODE HERE =======================
// Write the FoodWastageTracker class here. Refer to your class design for the
// member variables, constructors, and member functions needed.
//
// Note: mark functions that do not modify the member variables
// as const, by writing `const` after the parameter list.
// Pass objects by const reference when appropriate.
// Remember that std::string is an object!
// ===============================================================
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