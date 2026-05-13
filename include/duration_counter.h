#include <nlohmann/json.hpp>

#include <cstddef>
#include <fstream>
#include <string>

#ifndef TAPE_DURATION_COUNTER_H
#define TAPE_DURATION_COUNTER_H

using json = nlohmann::json;

namespace tape {
  class IDurationCounter {
   public:
    virtual ~IDurationCounter() = default;

    virtual std::size_t moveToBegin() = 0;
    virtual std::size_t moveToEnd() = 0;
    virtual std::size_t moveRight() = 0;
    virtual std::size_t moveLeft() = 0;
    virtual std::size_t read() = 0;
    virtual std::size_t write() = 0;
    virtual std::size_t size() = 0;
    virtual std::size_t totalOperationTime() = 0;
  };

  class DurationCounter : public IDurationCounter {
   public:
    template <typename String>
    DurationCounter(String&& file_name) : file_name_(file_name),
                                          total_oepration_time_(0)
    {
      std::ifstream ifs(file_name_);

      if (!ifs.is_open()) {
        throw std::runtime_error("Cannot access the " + file_name_ + " file");
      }

      data_ = json::parse(ifs);
    }

    ~DurationCounter() override = default;

    std::size_t moveToBegin() override {
      std::size_t operation_time = data_["move_to_begin"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t moveToEnd() override {
      std::size_t operation_time = data_["move_to_end"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t moveRight() override {
      std::size_t operation_time = data_["move_right"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t moveLeft() override {
      std::size_t operation_time = data_["move_left"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t read() override {
      std::size_t operation_time = data_["read"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t write() override {
      std::size_t operation_time = data_["write"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t size() override {
      std::size_t operation_time = data_["size"].get<std::size_t>();
      total_oepration_time_ += operation_time;

      return operation_time;
    };

    std::size_t totalOperationTime() override {
      return total_oepration_time_;
    }

   private:
     std::string file_name_;
     json data_;
     std::size_t total_oepration_time_;
  };

  class DummyCounter : public IDurationCounter {
   public:
    DummyCounter() : total_oepration_time_(0) {};

    ~DummyCounter() override = default;

    std::size_t moveToBegin() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t moveToEnd() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t moveRight() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t moveLeft() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t read() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t write() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t size() override {
      total_oepration_time_++;

      return 1;
    };

    std::size_t totalOperationTime() override {
      return total_oepration_time_;
    }

   private:
    std::size_t total_oepration_time_;
  };

};

#endif //TAPE_DURATION_COUNTER_H