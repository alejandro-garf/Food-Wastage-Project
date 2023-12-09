#ifndef FOOD_WASTAGE_REPORT_H_
#define FOOD_WASTAGE_REPORT_H_

// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf

#include <set>
#include <vector>

#include "food_wastage_record.h"

class FoodWastageReport {


 public:
  FoodWastageReport(const std::vector<FoodWastageRecord>& records);
  const std::vector<std::string>& CommonFoods() const;
  const std::vector<std::string>& CostlyMeals() const;
  double TotalCost() const;
  const std::vector<std::string>& CommonReasons() const;
  const std::vector<std::string>& CommonMechanisms() const;
  const std::vector<std::string>& SuggestedStrategies() const;

 private:
  void ComputeCommonFoods(const std::vector<FoodWastageRecord>& records);
  void ComputeCostlyMeals(const std::vector<FoodWastageRecord>& records);
  void ComputeTotalCost(const std::vector<FoodWastageRecord>& records);
  void ComputeCommonReasons(const std::vector<FoodWastageRecord>& records);
  void ComputeCommonMechanisms(const std::vector<FoodWastageRecord>& records);
  void ComputeSuggestedStrategies();
  std::vector<std::string> common_foods_;
  std::vector<std::string> costly_meals_;
  double total_cost_;
  std::vector<std::string> common_reasons_;
  std::vector<std::string> common_mechanisms_;
  std::vector<std::string> suggested_strategies_;
};

#endif