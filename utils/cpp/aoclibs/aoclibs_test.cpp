#include "aoclibs.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using ::testing::HasSubstr;
using ::testing::Return;

TEST(InputReaderTest, testReadingFromStream) {
  std::stringstream source;
  source << "Read stream";
  EXPECT_EQ("Read stream", aoclibs::readInput(source));
}

TEST(InputReaderTest, testReadingMultiLineStream) {
  std::stringstream source;
  source << "Line1\n" << "Line2";
  auto result = aoclibs::readInput(source);
  EXPECT_THAT(result, HasSubstr("Line1"));
  EXPECT_THAT(result, HasSubstr("Line2"));
}

class Solution {
 public:
  virtual ~Solution() {};
  virtual std::string solveProblem1(std::string_view) = 0;
  virtual std::string solveProblem2(std::string_view) = 0;
};

class MockSolution : public Solution {
 public:
  MOCK_METHOD1(solveProblem1, aoclibs::str_t(std::string_view));
  MOCK_METHOD1(solveProblem2, aoclibs::str_t(std::string_view));
};

using ::testing::StrictMock;
using ::testing::Test;

class RunSolutionTest : public Test {
 public:
  RunSolutionTest()
    : m_mockSolution(std::make_unique<StrictMock<MockSolution>>()) {}

 protected:
  std::unique_ptr<MockSolution> m_mockSolution;
};

TEST_F(RunSolutionTest, verifyThatOnlyOneFunctionIsCalled) {
  constexpr auto expectedInput{"Input1"};
  EXPECT_CALL(*m_mockSolution, solveProblem1(expectedInput)).WillOnce(Return("value"));

  aoclibs::runSolution(expectedInput, [&](std::string_view input) {
    return m_mockSolution->solveProblem1(input);
  });
}
