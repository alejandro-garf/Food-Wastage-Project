#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../food_wastage_tracker_backend.h"
#include "../cppaudit/gtest_ext.h"
#include "test_utils.h"

using ::testing::HasSubstr;
using ::testing::Not;
using json = nlohmann::json;

TEST(FoodWastageTrackerBackend, GetReportSingleRecord) {
  FoodWastageTrackerBackend backend{""};
  backend.AddRecord(CreateDefaultQueryString());
  json report = json::parse(backend.GetFoodWastageReport().dump());

  ASSERT_TRUE(
      jsonContains(report.at("most_commonly_wasted_food_"), kDefaultFood))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonListLength(report.at("most_commonly_wasted_food_")) == 1)
      << "Expected exactly 1 most commonly wasted food in this test "
         "case.";
  ASSERT_TRUE(jsonContains(report.at("most_common_disposal_mechanism_"),
                           kDefaultDisposal))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism mechanism.";
  ASSERT_TRUE(jsonListLength(report.at("most_common_disposal_mechanism_")) == 1)
      << "Expected exactly 1 most common disposal mechanism in this test "
         "case.";
  ASSERT_TRUE(jsonContains(report.at("most_common_wastage_reason_"),
                           kDefaultWastageReason))
      << "Food Wastage report incorrectly computed most common wastage reason.";
  ASSERT_TRUE(jsonListLength(report.at("most_common_wastage_reason_")) == 1)
      << "Expected exactly 1 most common wastage reason in this test "
         "case.";
  ASSERT_TRUE(
      jsonContains(report.at("most_waste_producing_meal_"), kDefaultMeal))
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonListLength(report.at("most_waste_producing_meal_")) == 1)
      << "Expected exactly 1 most common waste producing meal in this test "
         "case.";
  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == kDefaultCost)
      << "Food Wastage report incorrectly computed total cost of food wasted.";

  // Waste reduction strategies
  json strategiesJson = report.at("suggested_strategies_to_reduce_waste_");
  ASSERT_TRUE(jsonContains(strategiesJson, kBuyLessFoodT))
      << "Food wastage report should suggest buying less food.";
  ASSERT_TRUE(jsonContains(strategiesJson, kCookSmallerServingsT))
      << "Food wastage report should suggest cooking smaller servings.";
  ASSERT_TRUE(jsonContains(strategiesJson, kRecycleLeftOversT))
      << "Food wastage report should suggest recycling lefotvers.";
  ASSERT_TRUE(jsonListLength(strategiesJson) == 3)
      << "Food wastage report should suggest 3 strategies";
}

TEST(FoodWastageTrackerBackend, GetReportMultipleRecords) {
  // Load records to backend
  FoodWastageTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6)
      << "Initializing tracker with test data failed.";

  json report = json::parse(backend.GetFoodWastageReport().dump());

  json foodJson = report.at("most_commonly_wasted_food_");
  ASSERT_TRUE(jsonContains(foodJson, "Pasta"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Cake"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Milk"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Oats"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Rice"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Bread"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonListLength(foodJson) == 6)
      << "Expected exactly 6 most commonly wasted foods in this test case.";

  json reasonJson = report.at("most_common_wastage_reason_");
  ASSERT_TRUE(jsonContains(reasonJson, kTooMuchLeftOverT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonContains(reasonJson, kExpiredT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonContains(reasonJson, kTastesBadT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonListLength(reasonJson) == 3)
      << "Expected exactly 1 most common food wastage reason in this test "
         "case.";

  json disposalMechanismJson = report.at("most_common_disposal_mechanism_");
  ASSERT_TRUE(jsonContains(disposalMechanismJson, kTrashT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonContains(disposalMechanismJson, kDonationT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonListLength(disposalMechanismJson) == 2)
      << "Expected exactly 2 disposal mechanisms in this test "
         "case.";

  ASSERT_TRUE(report.at("most_waste_producing_meal_")[0] == kDefaultMeal)
      << "Food Wastage report incorrectly computed most waste producing "
         "meal.";
  ASSERT_TRUE(jsonListLength(report.at("most_waste_producing_meal_")) == 1)
      << "Expected exactly 1 most common waste producing meal in this test "
         "case.";

  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 13.5)
      << "Food Wastage report incorrectly computed total cost of food "
         "wasted.";

  // Waste reduction strategies
  json strategiesJson = report.at("suggested_strategies_to_reduce_waste_");
  ASSERT_TRUE(jsonContains(strategiesJson, kBuyLessFoodT))
      << "Food wastage report should suggest buying less food.";
  ASSERT_TRUE(jsonContains(strategiesJson, kCookSmallerServingsT))
      << "Food wastage report should suggest cooking smaller servings.";
  ASSERT_TRUE(jsonContains(strategiesJson, kDonateBeforeExpirationT))
      << "Food wastage report should suggest recycling lefotvers.";
  ASSERT_TRUE(jsonListLength(strategiesJson) == 3)
      << "Food wastage report should suggest 3 strategies";
}

// Get empty report
TEST(FoodWastageTrackerBackend, GetReportEmpty) {
  FoodWastageTrackerBackend backend{""};

  json report = json::parse(backend.GetFoodWastageReport().dump());

  ASSERT_TRUE(jsonEmpty(report.at("most_commonly_wasted_food_")))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonEmpty(report.at("most_common_disposal_mechanism_")))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonEmpty(report.at("most_common_wastage_reason_")))
      << "Food Wastage report incorrectly computed most common wastage reason.";
  ASSERT_TRUE(jsonEmpty(report.at("most_waste_producing_meal_")))
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonEmpty(report.at("suggested_strategies_to_reduce_waste_")));
  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 0)
      << "Food Wastage report incorrectly computed total cost of food wasted.";
}

// Get report waste reduction logic correctness
TEST(FoodWastageTrackerBackend, GetReportWasteReductionTestTooMuchLeftovers) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status =
      json::parse(backend
                      .AddRecord(CreateDefaultQueryStringWithWastageReason(
                          kTooMuchLeftOverT))
                      .dump());
  ASSERT_TRUE(add_status.at("success")) << "Failed to add record to tracker.";

  json report = json::parse(backend.GetFoodWastageReport().dump());

  // Waste reduction strategies
  json strategiesJson = report.at("suggested_strategies_to_reduce_waste_");
  ASSERT_TRUE(jsonContains(strategiesJson, kBuyLessFoodT))
      << "Food wastage report should suggest buying less food.";
  ASSERT_TRUE(jsonContains(strategiesJson, kCookSmallerServingsT))
      << "Food wastage report should suggest cooking smaller servings.";
  ASSERT_TRUE(jsonContains(strategiesJson, kRecycleLeftOversT))
      << "Food wastage report should suggest recycling lefotvers.";
  ASSERT_TRUE(jsonListLength(strategiesJson) == 3)
      << "Food wastage report should suggest 3 strategies";
}

// Get report waste reduction logic correctness
TEST(FoodWastageTrackerBackend, GetReportWasteReductionTestTastesBad) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithWastageReason(kTastesBadT))
          .dump());
  ASSERT_TRUE(add_status.at("success")) << "Adding record to tracker failed.";

  json report = json::parse(backend.GetFoodWastageReport().dump());

  // Waste reduction strategies
  json strategiesJson = report.at("suggested_strategies_to_reduce_waste_");
  ASSERT_TRUE(jsonContains(strategiesJson, kBuyLessFoodT))
      << "Food wastage report should suggest buying less food.";
  ASSERT_TRUE(jsonContains(strategiesJson, kRecycleLeftOversT))
      << "Food wastage report should suggest recycling lefotvers.";
  ASSERT_TRUE(jsonListLength(strategiesJson) == 2)
      << "Food wastage report should suggest 2 strategies";
}

// Get report waste reduction logic correctness
TEST(FoodWastageTrackerBackend, GetReportWasteReductionTestExpired) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithWastageReason(kExpiredT))
          .dump());
  ASSERT_TRUE(add_status.at("success")) << "Adding record to tracker failed.";

  json report = json::parse(backend.GetFoodWastageReport().dump());

  // Waste reduction strategies
  json strategiesJson = report.at("suggested_strategies_to_reduce_waste_");
  ASSERT_TRUE(jsonContains(strategiesJson, kDonateBeforeExpirationT))
      << "Food wastage report should suggest donating before expiration.";
  ASSERT_TRUE(jsonListLength(strategiesJson) == 1)
      << "Food wastage report should suggest 1 strategy";
}

// Get report most commonly wasted food
TEST(FoodWastageTrackerBackend, GetReportMostCommonWastedFood) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithFoodName("Pasta")).dump());
  ASSERT_TRUE(add_status.at("success")) << "Adding record to tracker failed.";

  json report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("most_commonly_wasted_food_")[0] == "Pasta")
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonListLength(report.at("most_commonly_wasted_food_")) == 1)
      << "Expected exactly one most commonly wasted food.";

  // Add second record
  add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithFoodName("Chips")).dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Adding second record to tracker failed.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  json foodJson = report.at("most_commonly_wasted_food_");
  ASSERT_TRUE(jsonContains(foodJson, "Pasta"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonContains(foodJson, "Chips"))
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonListLength(foodJson) == 2)
      << "Expected exactly 2 most commonly wasted foods in this test case.";

  // Add new record
  add_status =
      json::parse(backend
                      .AddRecord(QueryStringfromRecordDetails(
                          kDefaultDate, kDefaultMeal, "Pasta", kDefaultQty,
                          kDefaultDisposal, 9, kDefaultWastageReason))
                      .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Adding third record to tracker failed.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("most_commonly_wasted_food_")[0] == "Pasta")
      << "Food Wastage report incorrectly computed most common food.";
  ASSERT_TRUE(jsonListLength(report.at("most_commonly_wasted_food_")) == 1)
      << "Expected exactly 1 most commonly wasted food in this test case.";
}

// Get report ComputeMostCostlyWasteProducingMeal
TEST(FoodWastageTrackerBackend, GetReportMostCostlyWasteProducingMeal) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithMeal("Dinner")).dump());
  ASSERT_TRUE(add_status.at("success")) << "Failed to add record to tracker.";

  json report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("most_waste_producing_meal_")[0] == "Dinner")
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonListLength(report.at("most_waste_producing_meal_")) == 1)
      << "Expected exactly 1 most waste producing meal in this test case.";

  // Add second record
  add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithMeal("Breakfast")).dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add second record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  json foodJson = report.at("most_waste_producing_meal_");
  ASSERT_TRUE(jsonContains(foodJson, "Dinner"))
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonContains(foodJson, "Breakfast"))
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonListLength(foodJson) == 2)
      << "Expected exactly 2 most waste producing meals in this test case.";

  // Add new record
  add_status =
      json::parse(backend
                      .AddRecord(QueryStringfromRecordDetails(
                          kDefaultDate, "Dinner", kDefaultFood, kDefaultQty,
                          kDefaultDisposal, 9, kDefaultWastageReason))
                      .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add third record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  foodJson = report.at("most_waste_producing_meal_");
  ASSERT_TRUE(jsonContains(foodJson, "Dinner"))
      << "Food Wastage report incorrectly computed most waste producing meal.";
  ASSERT_TRUE(jsonListLength(foodJson) == 1)
      << "Expected exactly 1 most waste producing meal in this test case.";
}

// Get report ComputeTotalCostOfFodWasted
TEST(FoodWastageTrackerBackend, GetReportComputeTotalCostOfFoodWasted) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithMeal("Dinner")).dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add first record to tracker.";

  json report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 4.5)
      << "Food Wastage report incorrectly computed total cost of food wasted.";

  // Add second record
  add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithMeal("Breakfast")).dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add second record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 9)
      << "Food Wastage report incorrectly computed total cost of food wasted.";

  // Add new record
  add_status =
      json::parse(backend
                      .AddRecord(QueryStringfromRecordDetails(
                          kDefaultDate, "Dinner", kDefaultFood, kDefaultQty,
                          kDefaultDisposal, 9, kDefaultWastageReason))
                      .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add third record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 18)
      << "Food Wastage report incorrectly computed total cost of food wasted.";
}

// ComputeMostCommonWastageReason
TEST(FoodWastageTrackerBackend, GetReportComputeMostCommonWastageReason) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status =
      json::parse(backend
                      .AddRecord(CreateDefaultQueryStringWithWastageReason(
                          kTooMuchLeftOverT))
                      .dump());
  ASSERT_TRUE(add_status.at("success")) << "Failed to add record to tracker.";

  json report = json::parse(backend.GetFoodWastageReport().dump());
  json foodJson = report.at("most_common_wastage_reason_");
  ASSERT_TRUE(jsonContains(foodJson, kTooMuchLeftOverT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonListLength(foodJson) == 1)
      << "Expected exactly 1 most common food wastage reason in this test "
         "case.";

  ASSERT_TRUE(report.at("total_cost_of_food_wasted_") == 4.5)
      << "Food Wastage report incorrectly computed total cost of food wasted.";

  // Add second record
  add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithWastageReason(kTastesBadT))
          .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add second record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  foodJson = report.at("most_common_wastage_reason_");
  ASSERT_TRUE(jsonContains(foodJson, kTooMuchLeftOverT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonContains(foodJson, kTastesBadT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ASSERT_TRUE(jsonListLength(foodJson) == 2)
      << "Expected exactly 2 most common food wastage reasons in this test "
         "case.";

  // Add new record
  add_status =
      json::parse(backend
                      .AddRecord(QueryStringfromRecordDetails(
                          kDefaultDate, kDefaultMeal, kDefaultFood, kDefaultQty,
                          kDefaultDisposal, 9, kTooMuchLeftOverT))
                      .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add third record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  foodJson = report.at("most_common_wastage_reason_");
  ASSERT_TRUE(jsonContains(foodJson, kTooMuchLeftOverT))
      << "Food Wastage report incorrectly computed wastage reasons.";
  ;
  ASSERT_TRUE(jsonListLength(foodJson) == 1)
      << "Expected exactly 1 most common food wastage reason in this test "
         "case.";
}

// ComputeMostCommonDisposalMechanism
TEST(FoodWastageTrackerBackend, GetReportComputeMostCommonDisposalMechanism) {
  FoodWastageTrackerBackend backend{""};

  // Add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithDisposalMechanism(kSinkT))
          .dump());
  ASSERT_TRUE(add_status.at("success")) << "Failed to add record to tracker.";

  json report = json::parse(backend.GetFoodWastageReport().dump());
  json foodJson = report.at("most_common_disposal_mechanism_");
  ASSERT_TRUE(jsonContains(foodJson, kSinkT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonListLength(foodJson) == 1)
      << "Expected exactly 1 most common disposal mechanism in this test case.";

  // Add second record
  add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithDisposalMechanism(kTrashT))
          .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add second record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  foodJson = report.at("most_common_disposal_mechanism_");
  ASSERT_TRUE(jsonContains(foodJson, kTrashT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonContains(foodJson, kSinkT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonListLength(foodJson) == 2)
      << "Expected exactly 2 most common disposal mechanisms in this test "
         "case.";

  // Add new record
  add_status =
      json::parse(backend
                      .AddRecord(QueryStringfromRecordDetails(
                          kDefaultDate, kDefaultMeal, kDefaultFood, kDefaultQty,
                          kTrashT, 9, kDefaultWastageReason))
                      .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add third record to tracker.";

  report = json::parse(backend.GetFoodWastageReport().dump());
  foodJson = report.at("most_common_disposal_mechanism_");
  ASSERT_TRUE(jsonContains(foodJson, kTrashT))
      << "Food Wastage report incorrectly computed most common disposal "
         "mechanism.";
  ASSERT_TRUE(jsonListLength(foodJson) == 1)
      << "Expected exactly 1 most common disposal mechanism in this test case.";
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}