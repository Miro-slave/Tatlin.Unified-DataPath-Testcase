//
// Created by YF on 12.05.2026.
//

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <iostream>
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
    FileTape(String&& file_name) : file_name_(file_name),
                                   current_index_(0)
    {
      std::ifstream ifs(file_name_);

      std::istream_iterator<T> ifs_it(ifs);

      for (; ifs_it != std::istream_iterator<T>(); ++ifs_it) {
        data_.push_back(*ifs_it);
        ifs.ignore(1, ',');
      }
    };

    ~FileTape() override {
      std::ofstream ofs(file_name_, std::ios::trunc);

      std::ostream_iterator<int> ofs_it(ofs, ",");

      for (T element : data_) {
        *ofs_it = element;
        ++ofs_it;
      }
    };

    void moveToBegin() override {
      current_index_ = 0;
    };

    void moveToEnd() override {
      current_index_ = data_.size() - 1;
    };

    void moveRight() override {
      if (current_index_ < data_.size() - 1) {
        ++current_index_;
      }
    };

    void moveLeft() override {
      if (current_index_) {
        current_index_--;
      }
    };


    T read() override {
      return data_[current_index_];
    };

    void write(T value) override {
      data_[current_index_] = value;
    };

    std::size_t size() override {
      return data_.size();
    };

    virtual std::size_t totalOperationTime() override { return 0; };

  private:
    std::string file_name_;
    std::vector<T> data_;
    std::size_t current_index_;
  };
};

#endif //TESTCASE1_TAPE_H