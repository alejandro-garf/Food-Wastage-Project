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

TEST(FoodWastageTrackerBackend, GetRecords) {
  FoodWastageTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));

  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6)
      << "Failed to return all the records.";
}

// Add, then get a record
TEST(FoodWastageTrackerBackend, AddAndGetRecord) {
  // Load records to backend
  FoodWastageTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6)
      << "Failed to return all the records.";

  // Create and add new record
  json add_status = json::parse(
      backend.AddRecord(CreateDefaultQueryStringWithFoodName("Pineapples"))
          .dump());
  ASSERT_TRUE(add_status.at("success"))
      << "Failed to add the food wastage record. Make sure that Feature 1 is "
         "functioning properly before working on Get Records feature.";

  // There are now 7 records
  records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 7)
      << "Failed to return all the records.";
}

// Get records with a large number of records already added
TEST(FoodWastageTrackerBackend, GetManyRecords) {
  // Load records to backend
  FoodWastageTrackerBackend backend{""};
  ASSERT_TRUE(loadTrackerWithDefaultTestData(backend));
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6);

  // Create and add new records
  for (int i = 0; i < BIG_N; i++) {
    json add_status = json::parse(
        backend.AddRecord(CreateDefaultQueryStringWithCost(i + 1)).dump());
    ASSERT_TRUE(add_status.at("success"));
  }

  // There are now BIG_N + 6 records
  records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == BIG_N + 6);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
