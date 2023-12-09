#ifndef FOOD_WASTAGE_RECORD_H_
#define FOOD_WASTAGE_RECORD_H_

#include <string>

// Alejandro Fonseca
// CPSC 121L-06
// 11-30-23
// gfon@csu.fullerton.edu
// alejandro-garf

class FoodWastageRecord {
 public:
  FoodWastageRecord();

  const std::string& GetDate() const;
  const std::string& GetMeal() const;
  const std::string& GetFoodName() const;
  double GetQuantityOz() const;
  const std::string& GetWastageReason() const;
  const std::string& GetDisposalMechanism() const;
  double GetCost() const;
  void SetDate(std::string date);
  void SetMeal(std::string meal);
  void SetFoodName(std::string food_name);
  void SetQuantityOz(double quantity_oz);
  void SetWastageReason(std::string wastage_reason);
  void SetDisposalMechanism(std::string disposal_mechanism);
  void SetCost(double cost);
  bool Equals(const FoodWastageRecord& other) const;

 private:
  std::string date_;
  std::string meal_;
  std::string food_name_;
  double quantity_oz_;
  std::string wastage_reason_;
  std::string disposal_mechanism_;
  double cost_;
};

#endif