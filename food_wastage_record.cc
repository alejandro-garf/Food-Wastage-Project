// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf

#include "food_wastage_record.h"

FoodWastageRecord::FoodWastageRecord() {}

const std::string& FoodWastageRecord::GetDate() const { return date_; }
const std::string& FoodWastageRecord::GetMeal() const { return meal_; }
const std::string& FoodWastageRecord::GetFoodName() const { return food_name_; }
double FoodWastageRecord::GetQuantityOz() const { return quantity_oz_; }
const std::string& FoodWastageRecord::GetWastageReason() const {
  return wastage_reason_;
}
const std::string& FoodWastageRecord::GetDisposalMechanism() const {
  return disposal_mechanism_;
}
double FoodWastageRecord::GetCost() const { return cost_; }
void FoodWastageRecord::SetDate(std::string date) { date_ = date; }
void FoodWastageRecord::SetMeal(std::string meal) { meal_ = meal; }
void FoodWastageRecord::SetFoodName(std::string food_name) {
  food_name_ = food_name;
}
void FoodWastageRecord::SetQuantityOz(double quantity_oz) {
  quantity_oz_ = quantity_oz;
}
void FoodWastageRecord::SetWastageReason(std::string wastage_reason) {
  wastage_reason_ = wastage_reason;
}
void FoodWastageRecord::SetDisposalMechanism(std::string disposal_mechanism) {
  disposal_mechanism_ = disposal_mechanism;
}
void FoodWastageRecord::SetCost(double cost) { cost_ = cost; }
bool FoodWastageRecord::Equals(const FoodWastageRecord& other) const {
  return date_ == other.date_ && meal_ == other.meal_ &&
         food_name_ == other.food_name_ && quantity_oz_ == other.quantity_oz_ &&
         wastage_reason_ == other.wastage_reason_ &&
         disposal_mechanism_ == other.disposal_mechanism_ &&
         cost_ == other.cost_;
}