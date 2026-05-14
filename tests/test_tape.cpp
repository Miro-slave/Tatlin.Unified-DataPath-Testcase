#include "tape.h"
#include "duration_counter.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

using namespace tape;

namespace {

  const std::string test_file_path = "test_tape.csv";

  void write_file(const std::string& fileName, const std::string& content) {
    std::ofstream ofs(fileName, std::ios::trunc);
    ofs << content;
  }

  std::string read_file(const std::string& fileName) {
    std::ifstream ifs(fileName);
    return std::string(
        std::istream_iterator<char>(ifs),
        std::istream_iterator<char>());
  }

}

TEST(ReadDataTest, ReadsInitialDataCorrectly) {
  write_file(test_file_path, "1,2,3,4,");

  FileTape<std::int32_t> tape(test_file_path);

  EXPECT_EQ(tape.read(), 1);

  tape.moveRight();
  EXPECT_EQ(tape.read(), 2);

  tape.moveRight();
  EXPECT_EQ(tape.read(), 3);

  tape.moveRight();
  EXPECT_EQ(tape.read(), 4);

  tape.moveLeft();
  EXPECT_EQ(tape.read(), 3);

  tape.moveLeft();
  EXPECT_EQ(tape.read(), 2);

  tape.moveLeft();
  EXPECT_EQ(tape.read(), 1);
}

TEST(MoveToBeginTest, MoveToBeginMovesCursorToStart) {
  write_file(test_file_path, "10,20,30,");

  FileTape<std::int32_t> tape(test_file_path);

  tape.moveRight();
  tape.moveRight();

  EXPECT_EQ(tape.read(), 30);

  tape.moveToBegin();

  EXPECT_EQ(tape.read(), 10);
}

TEST(MoveToEndTest, MoveToEndMovesCursorToLastElement) {
  write_file(test_file_path, "7,8,9,");

  FileTape<std::int32_t> tape(test_file_path);

  tape.moveToEnd();

  EXPECT_EQ(tape.read(), 9);
}

TEST(OutOfBoundsRightTest, MoveRightDoesNotGoOutOfBounds) {
  write_file(test_file_path, "1,2,");

  FileTape<std::int32_t> tape(test_file_path);

  tape.moveRight();
  EXPECT_EQ(tape.read(), 2);

  tape.moveRight();

  EXPECT_EQ(tape.read(), 2);
}

TEST(OutOfBoundsLeftTest, MoveLeftDoesNotGoOutOfBounds) {
  write_file(test_file_path, "5,6,");

  FileTape<std::int32_t> tape(test_file_path);

  EXPECT_EQ(tape.read(), 5);

  tape.moveLeft();

  EXPECT_EQ(tape.read(), 5);
}

TEST(WriteTest, WriteChangesCurrentElement) {
  write_file(test_file_path, "1,2,3,");

  FileTape<std::int32_t> tape(test_file_path);

  tape.moveRight();
  tape.write(42);

  EXPECT_EQ(tape.read(), 42);

  tape.moveLeft();
  EXPECT_EQ(tape.read(), 1);

  tape.moveRight();
  EXPECT_EQ(tape.read(), 42);
}

TEST(SizeTest, SizeReturnsCorrectNumberOfElements) {
  write_file(test_file_path, "1,2,3,4,");

  FileTape<std::int32_t> tape(test_file_path);

  EXPECT_EQ(tape.size(), 4);
}

TEST(RewriteFileTest, DestructorRewritesFileWhenEnabled) {
  write_file(test_file_path, "1,2,3,");

  {
    FileTape<std::int32_t> tape(test_file_path, true);

    tape.moveRight();
    tape.write(99);
  }

  EXPECT_EQ(read_file(test_file_path), "1,99,3,");
}

TEST(NotRewriteFileTest, DestructorDoesNotRewriteFileWhenDisabled) {
  write_file(test_file_path, "1,2,3,");

  {
    FileTape<std::int32_t> tape(test_file_path, false);

    tape.moveRight();
    tape.write(99);
  }

  EXPECT_EQ(read_file(test_file_path), "1,2,3,");
}

TEST(CannotAccessFileConstructorExceptionTest, ThrowsWhenFileDoesNotExist) {
  std::shared_ptr<IDurationCounter> counter = std::make_shared<DummyCounter>();

  EXPECT_THROW(
    FileTape<std::int32_t>("missing_file.csv", false),
    std::runtime_error
  );

  EXPECT_THROW(
    FileTape<std::int32_t>("missing_file.csv", true),
    std::runtime_error
  );

  EXPECT_THROW(
    FileTape<std::int32_t>("missing_file.csv", counter, false),
    std::runtime_error
  );

  EXPECT_THROW(
    FileTape<std::int32_t>("missing_file.csv", counter, true),
    std::runtime_error
  );
}

TEST(DurationTimeTest, TracksOperationTime) {
  write_file(test_file_path, "1,2,3,");

  std::shared_ptr<IDurationCounter> counter = std::make_shared<DummyCounter>();

  FileTape<std::int32_t> tape(test_file_path, counter);

  tape.read();
  tape.moveRight();
  tape.read();
  tape.write(10);
  tape.size();

  EXPECT_EQ(tape.totalOperationTime(), 5);
}
