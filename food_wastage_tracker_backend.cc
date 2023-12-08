#include "food_wastage_tracker_backend.h"

#include <filesystem>

#include "food_wastage_record.h"
#include "food_wastage_report.h"
#include "server_utils/rapidjson/document.h"      // rapidjson's DOM-style API
#include "server_utils/rapidjson/prettywriter.h"  // for stringify JSON
#include "server_utils/rapidjson/rapidjson.h"
#include "server_utils/rapidjson/stringbuffer.h"  // wrapper of C stream for prettywriter as output
#include "server_utils/rapidjson/writer.h"

// Util function to convert a FoodWastageRecord class object into a serialized
// JSON object.
void SerializeFoodWastageRecordToJSON(
    const FoodWastageRecord &record,
    rapidjson::Writer<rapidjson::StringBuffer> *writer) {
  writer->StartObject();

  writer->String("date_");  // DO NOT MODIFY
  const std::string &date = record.GetDate();
  writer->String(date.c_str());

  writer->String("meal_");  // DO NOT MODIFY
  
  // TODO 2. Use the accessor/getter function for meal from the
  // FoodWastageRecord class object to get the meal and store it in the meal
  // string declared above.
  const std::string &meal = record.GetMeal();
  writer->String(meal.c_str());

  writer->String("food_name_");  // DO NOT MODIFY
  // TODO 3. Use the accessor/getter function for food name from the
  // FoodWastageRecord class object to get the food name and store it in the
  // food_name string declared above.
  const std::string &food_name = record.GetFoodName();
  writer->String(food_name.c_str());

  writer->String("qty_in_oz_");  // DO NOT MODIFY
  double quantity = record.GetQuantityOz();
  // TODO 4. Use the accessor/getter function for quantity from the
  // FoodWastageRecord class object to get the quantity and store it in the
  // quantity variable declared above.
  writer->Double(quantity);

  writer->String("wastage_reason_");  // DO NOT MODIFY
  const std::string &wastage_reason = record.GetWastageReason();
  // TODO 5. Use the accessor/getter function for wastage reason from the
  // FoodWastageRecord class object to get the wastage reason and store it in
  // the wastage_reason string declared above.
  writer->String(wastage_reason.c_str());

  writer->String("disposal_mechanism_");  // DO NOT MODIFY
  const std::string &disposal_mechanism = record.GetDisposalMechanism();
  // TODO 6. Use the accessor/getter function for disposal mechanism from the
  // FoodWastageRecord class object to get the disposal mechanism and store it
  // in the disposal_mechanism string declared above.
  writer->String(disposal_mechanism.c_str());

  writer->String("cost_");  // DO NOT MODIFY
  double cost = record.GetCost();
  // TODO 7. Use the accessor/getter function for cost from the
  // FoodWastageRecord class object to get the cost and store it in the cost
  // variable declared above.
  writer->Double(cost);

  writer->EndObject();
}

// Util function to convert a serialized JSON object in to a FoodWastageRecord
// class object.
FoodWastageRecord DeserializeFoodWastageRecordFromJSON(
    const rapidjson::Value &json_obj) {
  FoodWastageRecord record;

  /* TODO 1. Use the mutator/setter function for date from the FoodWastageRecord
   *  class to set the date in `record` object. You can get the date from JSON
   *  object as follows: `json_obj["date_"].GetString()`.
   *  Use that as an function  argument for the mutator that you'll call.
   */

  /* TODO 2. Use the mutator/setter function for meal from the FoodWastageRecord
   *  class to set the meal in `record` object. You can get the meal from JSON
   *  object as follows: `json_obj["meal_"].GetString()`.
   *  Use that as an function  argument for the mutator that you'll call.
   */

  /* TODO 3. Use the mutator/setter function for food name from the
   * FoodWastageRecord class to set the food name in `record` object. You can
   * get the food name from JSON object as follows:
   * `json_obj["food_name_"].GetString()`. Use that as an function  argument for
   * the mutator that you'll call.
   */

  /* TODO 4. Use the mutator/setter function for quantity from the
   * FoodWastageRecord class to set the quantity in `record` object. You can get
   * the quantity from JSON object as follows:
   * `json_obj["qty_in_oz_"].GetDouble()`. Use that as an function  argument for
   * the mutator that you'll call.
   */

  /* TODO 5. Use the mutator/setter function for wastage reason from the
   * FoodWastageRecord class to set the wastage reason in `record` object. You
   * can get the wastage reason from JSON object as follows:
   * `json_obj["wastage_reason_"].GetString()`. Use that as an function argument
   * for the mutator that you'll call.
   */

  /* TODO 6. Use the mutator/setter function for disposal mechanism from the
   * FoodWastageRecord class to set the disposal mechanism in `record` object.
   * You can get the disposal mechanism from JSON object as follows:
   * `json_obj["disposal_mechanism_"].GetString()`. Use that as an function
   * argument for the mutator that you'll call.
   */

  /* TODO 7. Use the mutator/setter function for cost from the FoodWastageRecord
   *  class to set the cost in `record` object. You can get the cost from JSON
   *  object as follows: `json_obj["cost_"].GetDouble()`.
   *  Use that as an function  argument for the mutator that you'll call.
   */
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

// Util function to convert a FoodWastageRecord class object into a Crow JSON
// object.
crow::json::wvalue FoodWastageRecordToCrowJSON(
    const FoodWastageRecord &record) {
  crow::json::wvalue record_json({});

  std::string date = record.GetDate();
  // TODO 1. Use the accessor/getter function for date from the
  // FoodWastageRecord class object to get the date and store it in the date
  // string declared above.
  record_json["date"] = date;

  std::string meal = record.GetMeal();
  // TODO 2. Use the accessor/getter function for meal from the
  // FoodWastageRecord class object to get the meal and store it in the meal
  // string declared above.
  record_json["meal"] = meal;

  std::string food_name = record.GetFoodName();
  // TODO 3. Use the accessor/getter function for food name from the
  // FoodWastageRecord class object to get the food name and store it in the
  // food_name string declared above.
  record_json["food_name"] = food_name;

  double quantity = record.GetQuantityOz();
  std::string quantity_str = std::to_string(quantity);
  // TODO 4. Use the accessor/getter function for quantity from the
  // FoodWastageRecord class object to get the quantity and store it in the
  // quantity variable declared above.
  record_json["qty_in_oz"] = quantity_str;

  std::string wastage_reason = record.GetWastageReason();
  // TODO 5. Use the accessor/getter function for wastage reason from the
  // FoodWastageRecord class object to get the wastage reason and store it in
  // the wastage_reason string declared above.
  record_json["wastage_reason"] = wastage_reason;

  std::string disposal_mechanism = record.GetDisposalMechanism();
  // TODO 6. Use the accessor/getter function for disposal mechanism from the
  // FoodWastageRecord class object to get the disposal mechanism and store it
  // in the disposal_mechanism string declared above.
  record_json["disposal_mechanism"] = disposal_mechanism;

  double cost = record.GetCost();
  std::string cost_str = std::to_string(cost);
  // TODO 7. Use the accessor/getter function for cost from the
  // FoodWastageRecord class object to get the cost and store it in the cost
  // variable declared above.
  record_json["cost"] = cost_str;
  return record_json;
}

// Util function to convert a FoodWastageReport class object into a serialized
// JSON object.
crow::json::wvalue FoodWastageReportToCrowJSON(
    const FoodWastageReport &report) {
  crow::json::wvalue report_json({});

 
  // TODO 1: Call the member function of FoodWastageReport class that returns
  // all
  std::vector<std::string> most_common_disposal_mechanisms =
      report.CommonMechanisms();

  // the most common disposal mechanisms as a vector of strings. Store the
  // result in the vector declared above.
  report_json["most_common_disposal_mechanism_"] =
      most_common_disposal_mechanisms;

  std::vector<std::string> most_commonly_wasted_foods = report.CommonFoods();
  // TODO 2: Call the member function of FoodWastageReport class that returns
  // all the most commonly wasted foods as a vector of strings. Store the result
  // in the vector declared above.
  report_json["most_commonly_wasted_food_"] = most_commonly_wasted_foods;

std::vector<std::string> most_common_wastage_reasons = report.CommonReasons();
  // TODO 3: Call the member function of FoodWastageReport class that returns
  // all the most commonwastage reasons as a vector of strings. Store the result
  // in the vector declared above.
  report_json["most_common_wastage_reason_"] = most_common_wastage_reasons;

    std::vector<std::string> most_costly_waste_producing_meals =
      report.CostlyMeals();
  // TODO 4: Call the member function of FoodWastageReport class that returns
  // all the most costly waste producing meals as a vector of strings. Store the
  // result in the vector declared above.
  report_json["most_waste_producing_meal_"] = most_costly_waste_producing_meals;

   std::vector<std::string> suggested_strategies_to_reduce_waste =
      report.SuggestedStrategies();
  // TODO 5: Call the member function of FoodWastageReport class that returns
  // all the suggested strategies as a vector of strings. Store the result in
  // the vector declared above.
  report_json["suggested_strategies_to_reduce_waste_"] =
      suggested_strategies_to_reduce_waste;

  double total_cost_of_wastage = report.TotalCost();
  // TODO 6: Call the member function of FoodWastageReport class that returns
  // the total cost of wastage as a double. Store the result in the double
  // declared.
  report_json["total_cost_of_food_wasted_"] = total_cost_of_wastage;

  return report_json;
}

// Util function to convert a crow query string into a FoodWastageRecord class
// object.
FoodWastageRecord QueryStringToFoodWastageRecord(
    const crow::query_string &query_string) {
  FoodWastageRecord record;

  // TODO 1. Get the date from the query_string using query_string.get("date"),
  // and set it in the `record` object using the setter in FoodWastageRecord
  // class.
  std::string date = query_string.get("date");
  record.SetDate(date);

  // TODO 2. Get the meal from the query_string using query_string.get("meal"),
  // and set it in the `record` object using the setter in FoodWastageRecord
  // class.
  std::string meal = query_string.get("meal");
  record.SetMeal(meal);

  // TODO 3. Get the food name from the query_string using
  // query_string.get("food_name"), and set it in the `record` object using the
  // setter in FoodWastageRecord class.
  std::string food_name = query_string.get("food_name");
  record.SetFoodName(food_name);

  // TODO 4. Get the quantity from the query_string using
  // std::stod(query_string.get("qty_in_oz")), and set it in the `record` object
  // using the setter in FoodWastageRecord class.
  double quantity = std::stod(std::string(query_string.get("qty_in_oz")));
  record.SetQuantityOz(quantity);

  // TODO 5. Get the wastage reason from the query_string using
  // query_string.get("wastage_reason"), and set it in the `record` object using
  // the setter in FoodWastageRecord class.
  std::string wastage_reason = query_string.get("wastage_reason");
  record.SetWastageReason(wastage_reason);

  // TODO 6. Get the disposal mechanism from the query_string using
  // query_string.get("disposal_mechanism"), and set it in the `record` object
  // using the setter in FoodWastageRecord class.
  std::string disposal_mechanism = query_string.get("disposal_mechanism");
  record.SetDisposalMechanism(disposal_mechanism);

  // TODO 7. Get the cost from the query_string using
  // std::stod(query_string.get("cost")), and set it in the `record` object
  // using the setter in FoodWastageRecord class.
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
    // TODO: Call the member function in the FoodWastageTracker class, on the
    // member object that you added in food_wastage_tracker.h, that
    // adds a `record`.
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
 
  // TODO: Call the member function in the FoodWastageTracker class, on the
  // member object that you added in food_wastage_tracker.h, that returns all
  // the FoodWastageRecord objects. Store the returned records in the vector
  // declared above. Also change the data type of the records vector to `const
  // std::vector<FoodWastageRecord>&`.
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
  // TODO: Call the member function in the FoodWastageTracker class, on the
  // member object that you added in food_wastage_tracker.h, that adds a
  // `record` and returns the status of the add operation as a bool. Store the
  // returned value in the bool declared above.
  status["success"] = add_result;
  return status;
}

crow::json::wvalue FoodWastageTrackerBackend::DeleteRecord(
    const crow::query_string &query_string) {
  FoodWastageRecord record = QueryStringToFoodWastageRecord(query_string);
  crow::json::wvalue status;
  bool delete_result = food_wastage_tracker_.RemoveRecord(record);
  // TODO: Call the member function in the FoodWastageTracker class, on the
  // member object that you added in food_wastage_tracker.h, that deletes
  // `record` and returns the status of the delete operation as a bool. Store
  // the returned value in the bool declared above.
  status["success"] = delete_result;
  return status;
}

crow::json::wvalue FoodWastageTrackerBackend::GetRecords() const {
  const std::vector<FoodWastageRecord> &records =
      food_wastage_tracker_.GetRecords();
  // TODO: Call the member function in the FoodWastageTracker class, on the
  // member object that you added in food_wastage_tracker.h, that returns all
  // the FoodWastageRecord objects. Store the returned records in the vector
  // declared above. Also change the data type of the records vector to `const
  // std::vector<FoodWastageRecord>&`.
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
  // TODO: Call the member function in the FoodWastageTracker class, on the
  // member object that you added in food_wastage_tracker.h, that generates a
  // FoodWastageReport object using all the FoodWastageRecords and returns it.
  // Store the returned value in the `generated_report` object declared above.
  return FoodWastageReportToCrowJSON(generated_report);
}