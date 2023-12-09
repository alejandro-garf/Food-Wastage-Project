#include "food_wastage_tracker_backend.h"

#include <filesystem>

#include "food_wastage_record.h"
#include "food_wastage_report.h"
#include "server_utils/rapidjson/document.h"      // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

void SerializeFoodWastageRecordToJSON(
    const FoodWastageRecord &record,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->String("date_");  // DO NOT MODIFY
  const std::string &date = record.GetDate();
  writer->String(date.c_str());

  writer->String("meal_");  // DO NOT MODIFY

  const std::string &meal = record.GetMeal();
  writer->String(meal.c_str());

  writer->String("food_name_");  // DO NOT MODIFY

  const std::string &food_name = record.GetFoodName();
  writer->String(food_name.c_str());

  writer->String("qty_in_oz_");  // DO NOT MODIFY
  double quantity = record.GetQuantityOz();

  writer->Double(quantity);

  writer->String("wastage_reason_");  // DO NOT MODIFY
  const std::string &wastage_reason = record.GetWastageReason();

  writer->String(wastage_reason.c_str());

  writer->String("disposal_mechanism_");  // DO NOT MODIFY
  const std::string &disposal_mechanism = record.GetDisposalMechanism();

  writer->String(disposal_mechanism.c_str());

  writer->String("cost_");  // DO NOT MODIFY
  double cost = record.GetCost();

  writer->Double(cost);

  writer->EndObject();
}

FoodWastageRecord DeserializeFoodWastageRecordFromJSON(
    const rapidjson::Value &json_obj) {
  FoodWastageRecord record;

  std::string date = std::string(json_obj["date_"].GetString());
  record.SetDate(std::move(date));

  std::string meal = std::string(json_obj["meal_"].GetString());
  record.SetMeal(std::move(meal));

  std::string food_name = std::string(json_obj["food_name_"].GetString());
  record.SetFoodName(std::move(food_name));

  double quantity_oz = json_obj["qty_in_oz_"].GetDouble();
  record.SetQuantityOz(quantity_oz);

  std::string wastage_reason =
      std::string(json_obj["wastage_reason_"].GetString());
  record.SetWastageReason(std::move(wastage_reason));

  std::string disposal_mechanism =
      std::string(json_obj["disposal_mechanism_"].GetString());
  record.SetDisposalMechanism(std::move(disposal_mechanism));

  double cost = json_obj["cost_"].GetDouble();
  record.SetCost(cost);
  return record;
}

crow::json::wvalue FoodWastageRecordToCrowJSON(
    const FoodWastageRecord &record) {
  crow::json::wvalue record_json({});

  std::string date = record.GetDate();

  record_json["date"] = date;

  std::string meal = record.GetMeal();

  record_json["meal"] = meal;

  std::string food_name = record.GetFoodName();

  record_json["food_name"] = food_name;

  double quantity = record.GetQuantityOz();
  std::string quantity_str = std::to_string(quantity);

  record_json["qty_in_oz"] = quantity_str;

  std::string wastage_reason = record.GetWastageReason();

  record_json["wastage_reason"] = wastage_reason;

  std::string disposal_mechanism = record.GetDisposalMechanism();

  record_json["disposal_mechanism"] = disposal_mechanism;

  double cost = record.GetCost();
  std::string cost_str = std::to_string(cost);

  record_json["cost"] = cost_str;
  return record_json;
}

crow::json::wvalue FoodWastageReportToCrowJSON(
    const FoodWastageReport &report) {
  crow::json::wvalue report_json({});

  std::vector<std::string> most_common_disposal_mechanisms =
      report.CommonMechanisms();

  report_json["most_common_disposal_mechanism_"] =
      most_common_disposal_mechanisms;

  std::vector<std::string> most_commonly_wasted_foods = report.CommonFoods();

  report_json["most_commonly_wasted_food_"] = most_commonly_wasted_foods;

  std::vector<std::string> most_common_wastage_reasons = report.CommonReasons();

  report_json["most_common_wastage_reason_"] = most_common_wastage_reasons;

  std::vector<std::string> most_costly_waste_producing_meals =
      report.CostlyMeals();

  report_json["most_waste_producing_meal_"] = most_costly_waste_producing_meals;

  std::vector<std::string> suggested_strategies_to_reduce_waste =
      report.SuggestedStrategies();

  report_json["suggested_strategies_to_reduce_waste_"] =
      suggested_strategies_to_reduce_waste;

  double total_cost_of_wastage = report.TotalCost();

  report_json["total_cost_of_food_wasted_"] = total_cost_of_wastage;

  return report_json;
}

FoodWastageRecord QueryStringToFoodWastageRecord(
    const crow::query_string &query_string) {
  FoodWastageRecord record;

  std::string date = query_string.get("date");
  record.SetDate(date);

  std::string meal = query_string.get("meal");
  record.SetMeal(meal);

  std::string food_name = query_string.get("food_name");
  record.SetFoodName(food_name);

  double quantity = std::stod(std::string(query_string.get("qty_in_oz")));
  record.SetQuantityOz(quantity);

  std::string wastage_reason = query_string.get("wastage_reason");
  record.SetWastageReason(wastage_reason);

  std::string disposal_mechanism = query_string.get("disposal_mechanism");
  record.SetDisposalMechanism(disposal_mechanism);

  double cost = std::stod(std::string(query_string.get("cost")));
  record.SetCost(cost);

  return record;
}

bool FoodWastageTrackerBackend::LoadRecordsFromJSONFile() {
  std::ifstream records_file{food_wastage_records_filepath_};
  if (!records_file.is_open()) {
    std::filesystem::remove(food_wastage_records_filepath_);
    return false;
  }

  std::stringstream buffer;
  buffer << records_file.rdbuf();

  std::string s = buffer.str();
  rapidjson::Document doc;

  if (s.empty()) {
    std::filesystem::remove(food_wastage_records_filepath_);
    return false;
  }

  std::string validJson(s);

  bool doc_parse_error = doc.Parse(validJson.c_str()).HasParseError();
  if (doc_parse_error || !doc.IsArray()) {
    std::filesystem::remove(food_wastage_records_filepath_);
    return false;
  }

  for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End();
       ++itr) {
    FoodWastageRecord record = DeserializeFoodWastageRecordFromJSON(*itr);

    food_wastage_tracker_.AddRecord(std::move(record));
  }

  records_file.close();
  return true;
}

bool FoodWastageTrackerBackend::WriteRecordsToJSONFile() const {
  std::ofstream records_file{food_wastage_records_filepath_};
  rapidjson::StringBuffer ss;
  rapidjson::Writer<rapidjson::StringBuffer> writer(ss);
  writer.StartArray();

  for (FoodWastageRecord record : records) {
    const std::vector<FoodWastageRecord> &records =
        food_wastage_tracker_.GetRecords();

    for (const FoodWastageRecord &record : records) {
      SerializeFoodWastageRecordToJSON(record, &writer);
    }
    writer.EndArray();

    records_file << ss.GetString();

    records_file.flush();
    records_file.close();
    return true;
  }

  crow::json::wvalue FoodWastageTrackerBackend::AddRecord(
      const crow::query_string &query_string) {
    FoodWastageRecord record = QueryStringToFoodWastageRecord(query_string);
    crow::json::wvalue status;
    bool add_result = food_wastage_tracker_.AddRecord(record);

    status["success"] = add_result;
    return status;
  }

  crow::json::wvalue FoodWastageTrackerBackend::DeleteRecord(
      const crow::query_string &query_string) {
    FoodWastageRecord record = QueryStringToFoodWastageRecord(query_string);
    crow::json::wvalue status;
    bool delete_result = food_wastage_tracker_.RemoveRecord(record);

    status["success"] = delete_result;
    return status;
  }

  crow::json::wvalue FoodWastageTrackerBackend::GetRecords() const {
    const std::vector<FoodWastageRecord> &records =
        food_wastage_tracker_.GetRecords();

    crow::json::wvalue records_json({});
    records_json["num_records"] = records.size();

    std::vector<crow::json::wvalue> record_json_vector;
    for (const FoodWastageRecord &record : records) {
      record_json_vector.push_back(FoodWastageRecordToCrowJSON(record));
    }
    records_json["record_array"] = std::move(record_json_vector);
    return records_json;
  }

  crow::json::wvalue FoodWastageTrackerBackend::GetFoodWastageReport() const {
    FoodWastageReport generated_report = food_wastage_tracker_.GenerateReport();

    return FoodWastageReportToCrowJSON(generated_report);
  }