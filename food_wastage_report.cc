// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf

#include "food_wastage_report.h"

#include <map>
#include <string>

FoodWastageReport::FoodWastageReport(
    const std::vector<FoodWastageRecord>& records) {
  ComputeCommonFoods(records);
  ComputeCostlyMeals(records);
  ComputeTotalCost(records);
  ComputeCommonReasons(records);
  ComputeCommonMechanisms(records);
  ComputeSuggestedStrategies();
}

void FoodWastageReport::ComputeCommonFoods(
    const std::vector<FoodWastageRecord>& records) {
  common_foods_.clear();
  std::map<std::string, int> count_tracker;
  int max_count = 0;
  for (const FoodWastageRecord& r : records) {
    if (count_tracker.find(r.GetFoodName()) == count_tracker.end()) {
      count_tracker.insert({std::string(r.GetFoodName()), 1});
    } else {
      count_tracker[r.GetFoodName()]++;
    }
    max_count = std::max(count_tracker[r.GetFoodName()], max_count);
  }
  for (const auto& e : count_tracker) {
    if (e.second == max_count) {
      common_foods_.push_back(e.first);
    }
  }
}
void FoodWastageReport::ComputeCostlyMeals(
    const std::vector<FoodWastageRecord>& records) {
  costly_meals_.clear();
  std::map<std::string, double> cost_tracker;
  double max_cost = 0;
  for (const FoodWastageRecord& r : records) {
    if (cost_tracker.find(r.GetMeal()) == cost_tracker.end()) {
      cost_tracker.insert({std::string(r.GetMeal()), r.GetCost()});
    } else {
      cost_tracker[r.GetMeal()] += r.GetCost();
    }
    max_cost = std::max(cost_tracker[r.GetMeal()], max_cost);
  }
  for (const auto& e : cost_tracker) {
    if (e.second == max_cost) {
      costly_meals_.push_back(e.first);
    }
  }
}

void FoodWastageReport::ComputeTotalCost(
    const std::vector<FoodWastageRecord>& records) {
  total_cost_ = 0.0;
  for (const FoodWastageRecord& r : records) {
    total_cost_ += r.GetCost();
  }
}

void FoodWastageReport::ComputeCommonReasons(
    const std::vector<FoodWastageRecord>& records) {
  common_reasons_.clear();
  std::map<std::string, int> reason_tracker;
  int max_count = 0;
  for (const FoodWastageRecord& r : records) {
    if (reason_tracker.find(r.GetWastageReason()) == reason_tracker.end()) {
      reason_tracker.insert({std::string(r.GetWastageReason()), 1});
    } else {
      reason_tracker[r.GetWastageReason()]++;
    }
    max_count = std::max(reason_tracker[r.GetWastageReason()], max_count);
  }
  for (const auto& e : reason_tracker) {
    if (e.second == max_count) {
      common_reasons_.push_back(e.first);
    }
  }
}
void FoodWastageReport::ComputeCommonMechanisms(
    const std::vector<FoodWastageRecord>& records) {
  common_mechanisms_.clear();
  std::map<std::string, int> mechanism_tracker;
  int max_count = 0;
  for (const FoodWastageRecord& r : records) {
    if (mechanism_tracker.find(r.GetDisposalMechanism()) ==
        mechanism_tracker.end()) {
      mechanism_tracker.insert({std::string(r.GetDisposalMechanism()), 1});
    } else {
      mechanism_tracker[r.GetDisposalMechanism()]++;
    }
    max_count =
        std::max(mechanism_tracker[r.GetDisposalMechanism()], max_count);
  }
  for (const auto& e : mechanism_tracker) {
    if (e.second == max_count) {
      common_mechanisms_.push_back(e.first);
    }
  }
}
void FoodWastageReport::ComputeSuggestedStrategies() {
  suggested_strategies_.clear();
  std::set<std::string> strategy_set;

  for (const std::string& reason : common_reasons_) {
    if (reason == "Too much left overs") {
      strategy_set.insert("Cook small servings");
      strategy_set.insert("Recycle left overs");
      strategy_set.insert("Buy less food");
    } else if (reason == "Expired") {
      strategy_set.insert("Donate before expiration");
    } else if (reason == "Tastes bad") {
      strategy_set.insert("Buy less food");
      strategy_set.insert("Recycle left overs");
    }
  }

  suggested_strategies_ =
      std::vector<std::string>(strategy_set.begin(), strategy_set.end());
  while (suggested_strategies_.size() > 3) {
    suggested_strategies_.pop_back();
  }
}

const std::vector<std::string>& FoodWastageReport::CommonFoods() const {
  return common_foods_;
}
const std::vector<std::string>& FoodWastageReport::CostlyMeals() const {
  return costly_meals_;
}
double FoodWastageReport::TotalCost() const { return total_cost_; }
const std::vector<std::string>& FoodWastageReport::CommonReasons() const {
  return common_reasons_;
}
const std::vector<std::string>& FoodWastageReport::CommonMechanisms() const {
  return common_mechanisms_;
}
const std::vector<std::string>& FoodWastageReport::SuggestedStrategies() const {
  return suggested_strategies_;
}