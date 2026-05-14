#include "duration_counter.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <vector>
#include <memory>

#ifndef TESTCASE1_TAPE_H
#define TESTCASE1_TAPE_H

namespace tape {
  template <typename T>
  class ITape {
  public:
    virtual ~ITape() = default;

    virtual void moveToBegin() = 0;
    virtual void moveToEnd() = 0;
    virtual void moveRight() = 0;
    virtual void moveLeft() = 0;
    virtual T read() = 0;
    virtual void write(T) = 0;
    virtual std::size_t size() = 0;
    virtual std::size_t totalOperationTime() = 0;
  };

  template <typename T>
  class FileTape : public ITape<T> {
  public:
    template <typename String>
    FileTape(String&& file_name,
             bool rewrite_file = false) : file_name_(file_name),
                                          current_index_(0),
                                          rewrite_file_(rewrite_file)
    {
      std::ifstream ifs(file_name_);

      std::istream_iterator<T> ifs_it(ifs);

      for (; ifs_it != std::istream_iterator<T>(); ++ifs_it) {
        data_.push_back(*ifs_it);
        ifs.ignore(1, ',');
      }

      duration_counter_ = std::make_shared<DummyCounter>();
    };

    template <typename String>
    FileTape(String&& file_name,
             std::shared_ptr<IDurationCounter>& duration_counter,
             bool rewrite_file = false) : file_name_(file_name),
                                          current_index_(0),
                                          duration_counter_(duration_counter),
                                          rewrite_file_(rewrite_file)
    {
      std::ifstream ifs(file_name_);

      if (!ifs.is_open()) {
        throw std::runtime_error("Cannot access the " + file_name_ + " file");
      }

      std::istream_iterator<T> ifs_it(ifs);

      for (; ifs_it != std::istream_iterator<T>(); ++ifs_it) {
        data_.push_back(*ifs_it);
        ifs.ignore(1, ',');
      }
    };

    ~FileTape() override {
      if (rewrite_file_) {
        std::ofstream ofs(file_name_, std::ios::trunc);

        if (!ofs.is_open()) {
          throw std::runtime_error("Cannot access the " + file_name_ + " file");
        }

        std::ostream_iterator<int> ofs_it(ofs, ",");

        for (T element : data_) {
          *ofs_it = element;
          ++ofs_it;
        }
      }
    };

    void moveToBegin() override {
      current_index_ = 0;
      duration_counter_->moveToBegin();
    };

    void moveToEnd() override {
      current_index_ = data_.size() - 1;
      duration_counter_->moveToEnd();
    };

    void moveRight() override {
      if (current_index_ < data_.size() - 1) {
        ++current_index_;
      }

      duration_counter_->moveRight();
    };

    void moveLeft() override {
      if (current_index_) {
        current_index_--;
      }

      duration_counter_->moveLeft();
    };


    T read() override {
      duration_counter_->read();

      return data_[current_index_];
    };

    void write(T value) override {
      data_[current_index_] = value;
      duration_counter_->write();
    };

    std::size_t size() override {
      duration_counter_->size();

      return data_.size();
    };

    std::size_t totalOperationTime() override {
      return duration_counter_->totalOperationTime();
    };

  private:
    std::string file_name_;
    std::vector<T> data_;
    std::size_t current_index_;
    std::shared_ptr<IDurationCounter> duration_counter_;
    bool rewrite_file_;
  };
};

#endif //TESTCASE1_TAPE_H