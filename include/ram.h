#include <cstddef>
#include <filesystem>
#include <iterator>
#include <vector>

#ifndef TESTCASE1_RAM_H
#define TESTCASE1_RAM_H

namespace tape {
  template <typename T>
  class IRam {
  public:
    virtual ~IRam() = default;

    virtual T read(std::size_t) = 0;
    virtual void write(std::size_t, T) = 0;
    virtual std::size_t size() = 0;
    virtual std::size_t totalOperationTime() = 0;
  };

  template <typename T>
  class VectorRam : public IRam<T> {
  public:
    VectorRam(const std::vector<T>& data) : data_(data) {};

    ~VectorRam() override = default;

    T read(std::size_t index) override {
      return data_[index];
    };

    void write(std::size_t index, T value) override {
      data_[index] = value;
    };

    std::size_t size() override {
      return data_.size();
    };

    std::size_t totalOperationTime() override { return 0; };

  private:
    std::vector<T> data_;
  };
};

#endif //TESTCASE1_RAM_H