#include "test_utils.h"

#include <assert.h>

#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>

#include "../../food_wastage_tracker_backend.h"
#include "../../server_utils/rapidjson/document.h"  // rapidjson's DOM-style API
#include "../../server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "../../server_utils/rapidjson/rapidjson.h"
#include "../../server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "../../server_utils/rapidjson/writer.h"

using json = nlohmann::json;

crow::query_string CreateDefaultQueryString() {
  return QueryStringfromRecordDetails(kDefaultDate, kDefaultMeal, kDefaultFood,
                                      kDefaultQty, kDefaultDisposal,
                                      kDefaultCost, kDefaultWastageReason);
}

crow::query_string CreateDefaultQueryStringWithDate(std::string date) {
  return QueryStringfromRecordDetails(date, kDefaultMeal, kDefaultFood,
                                      kDefaultQty, kDefaultDisposal,
                                      kDefaultCost, kDefaultWastageReason);
}

crow::query_string CreateDefaultQueryStringWithFoodName(std::string food_name) {
  return QueryStringfromRecordDetails(kDefaultDate, kDefaultMeal, food_name,
                                      kDefaultQty, kDefaultDisposal,
                                      kDefaultCost, kDefaultWastageReason);
}

crow::query_string CreateDefaultQueryStringWithCost(double cost) {
  return QueryStringfromRecordDetails(kDefaultDate, kDefaultMeal, kDefaultFood,
                                      kDefaultQty, kDefaultDisposal, cost,
                                      kDefaultWastageReason);
}

crow::query_string CreateDefaultQueryStringWithWastageReason(
    std::string wastage_reason) {
  return QueryStringfromRecordDetails(kDefaultDate, kDefaultMeal, kDefaultFood,
                                      kDefaultQty, kDefaultDisposal,
                                      kDefaultCost, wastage_reason);
}

crow::query_string CreateDefaultQueryStringWithMeal(std::string meal) {
  return QueryStringfromRecordDetails(kDefaultDate, meal, kDefaultFood,
                                      kDefaultQty, kDefaultDisposal,
                                      kDefaultCost, kDefaultWastageReason);
}

crow::query_string CreateDefaultQueryStringWithDisposalMechanism(
    std::string disposal_mechanism) {
  return QueryStringfromRecordDetails(kDefaultDate, kDefaultMeal, kDefaultFood,
                                      kDefaultQty, disposal_mechanism,
                                      kDefaultCost, kDefaultWastageReason);
}

crow::query_string QueryStringfromRecordDetails(
    std::string date, std::string meal, std::string food_name, double qty,
    std::string disposal_mechanism, double cost, std::string wastage_reason) {
  std::string query_string = "?date=" + date + "&meal=" + meal +
                             "&food_name=" + food_name +
                             "&qty_in_oz=" + std::to_string(qty) +
                             "&wastage_reason=" + wastage_reason +
                             "&disposal_mechanism=" + disposal_mechanism +
                             "&cost=" + std::to_string(cost);

  crow::query_string res{query_string};

  return res;
}

bool jsonContains(json json, std::string strategy_string) {
  for (auto& element : json) {
    if (element == strategy_string) {
      return true;
    }
  }
  return false;
}

bool jsonEmpty(json json) { return (jsonListLength(json) == 0); }

int jsonListLength(json json) {
  int l = 0;
  for (auto& element : json) {
    l++;
  }
  return l;
}

bool loadTrackerWithDefaultTestData(FoodWastageTrackerBackend& backend) {
  return loadTrackerWithDefaultTestData(backend, kTestFilename);
}

bool loadTrackerWithDefaultTestData(FoodWastageTrackerBackend& backend,
                                    const std::string& json_filename) {
  std::ifstream records_file{json_filename};
  if (!records_file.is_open()) {
    return false;
  }

  std::stringstream buffer;
  buffer << records_file.rdbuf();

  std::string s = buffer.str();
  rapidjson::Document doc;

  if (s.empty()) {
    return false;
  }

  std::string validJson(s);

  bool doc_parse_error = doc.Parse(validJson.c_str()).HasParseError();
  if (doc_parse_error || !doc.IsArray()) {
    // std::filesystem::remove(food_wastage_records_filepath_);
    return false;
  }

  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End();
       ++itr) {
    const rapidjson::Value& obj = *itr;
    json add_status = json::parse(
        backend
            .AddRecord(QueryStringfromRecordDetails(
                obj["date_"].GetString(), obj["meal_"].GetString(),
                obj["food_name_"].GetString(), obj["qty_in_oz_"].GetDouble(),
                obj["disposal_mechanism_"].GetString(),
                obj["cost_"].GetDouble(), obj["wastage_reason_"].GetString()))
            .dump());
    assert(add_status.at("success"));
  }

  records_file.close();
  return true;
}
