#ifndef FOOD_WASTAGE_TRACKER_BACKEND_H_
#define FOOD_WASTAGE_TRACKER_BACKEND_H_

#include <string>

#include "food_wastage_tracker.h"
#include "server_utils/crow_all.h"


class FoodWastageTrackerBackend {
 public:
  FoodWastageTrackerBackend(const std::string &food_wastage_records_filepath)
      : food_wastage_records_filepath_{food_wastage_records_filepath} {}


  bool LoadRecordsFromJSONFile();


  bool WriteRecordsToJSONFile() const;


  crow::json::wvalue AddRecord(const crow::query_string &query_string);


  crow::json::wvalue DeleteRecord(const crow::query_string &query_string);


  crow::json::wvalue GetRecords() const;

  crow::json::wvalue GetFoodWastageReport() const;

 private:

  const std::string &food_wastage_records_filepath_;

  FoodWastageTracker food_wastage_tracker_;

};
#endif