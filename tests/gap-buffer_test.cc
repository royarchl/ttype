#include "../src/gap-buffer.h"

#include <gtest/gtest.h>

#include <fstream>

class GapBufferTest : public ::testing::Test {
 protected:
  void SetUp() override {
    // Set up code here
    buffer_.TextInsert(test_string);
  }

  // void TearDown() override {
  // Clean up code here
  // }

  // Example member variables
  GapBuffer buffer_;
  std::string test_string = "The last thing";
};

/*
 * TEST(TestSuiteName, TestName)
 * A simple test that doesn't require any special setup
 *
 * TEST_F(TestFixtureClassName, TestName)
 * Used for a test that requires setup. Each one of these uses that same setup
 * although none of the changes/data from a test persist to the next test.
 */

TEST(GapBuffer, DefaultConstructorTest) {
  // Test default constructor behavior

  /*
   * Buffer should be empty (maybe check via pointer to first element)
   * Gap size should equal buffer size
   * Buffer should be of size kDefaultGapSize
   */
  GapBuffer buffer;
  EXPECT_EQ(buffer.GetBufferSize(), buffer.GetDefaultGapSize());
  EXPECT_EQ(buffer.GetGapSize(), buffer.GetBufferSize());
  EXPECT_EQ(buffer.GetBufferContent(), "");
}

TEST(GapBuffer, FileConstructorTest) {
  // Create a temporary file with some content
  const std::string filename = "test_file.txt";
  {
    std::ofstream out_file(filename);
    out_file << "Hello, GapBuffer!";
  }

  GapBuffer buffer(filename);

  // Verify the content is loaded properly (does it count '\n'?)
  EXPECT_EQ(buffer.GetBufferContent(), "Hello, GapBuffer!");

  // Clean up the file after test
  std::remove(filename.c_str());
}

/* Do I need a test for the destructor as well? */

/*
 * Not needed! because this is already tested in the default constructor.
 * TEST_F(GapBufferTest, TextInsertTest) {}
 */

TEST_F(GapBufferTest, CharacterInsertTest) {
  /*
   * Gap size should be one less
   * Gap end should be same but gap start one further
   * Text should have the new letter
   */
  std::size_t prev_gap_size = buffer_.GetGapSize();
  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  buffer_.CharacterInsert('w');

  EXPECT_EQ(buffer_.GetGapSize(), prev_gap_size - 1);
  EXPECT_TRUE(buffer_.GetGapOffsets().first == prev_gap_offsets.first + 1 &&
              buffer_.GetGapOffsets().second == prev_gap_offsets.second);
  EXPECT_EQ(buffer_.GetBufferContent(), test_string + 'w');
}

TEST_F(GapBufferTest, CharacterBackspaceTest) {
  std::size_t prev_gap_size = buffer_.GetGapSize();
  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();
  std::string expected_string = "The last thin";

  buffer_.CharacterBackspace();

  EXPECT_EQ(buffer_.GetGapSize(), prev_gap_size + 1);
  EXPECT_TRUE(buffer_.GetGapOffsets().first == prev_gap_offsets.first - 1 &&
              buffer_.GetGapOffsets().second == prev_gap_offsets.second);
  EXPECT_EQ(buffer_.GetBufferContent(), expected_string);
}

TEST_F(GapBufferTest, CharacterDeleteTest) {
  buffer_.MoveCharacterLeft();

  std::size_t prev_gap_size = buffer_.GetGapSize();
  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();
  std::string expected_string = "The last thin";

  buffer_.CharacterDelete();

  EXPECT_EQ(buffer_.GetGapSize(), prev_gap_size + 1);
  EXPECT_TRUE(buffer_.GetGapOffsets().first == prev_gap_offsets.first &&
              buffer_.GetGapOffsets().second == prev_gap_offsets.second + 1);
  EXPECT_EQ(buffer_.GetBufferContent(), expected_string);
}

TEST_F(GapBufferTest, MoveCharacterLeftTest) {
  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  buffer_.MoveCharacterLeft();

  EXPECT_TRUE(buffer_.GetGapOffsets().first == prev_gap_offsets.first - 1 &&
              buffer_.GetGapOffsets().second == prev_gap_offsets.second - 1);
  EXPECT_EQ(buffer_.GetBufferContent(), test_string);
}

TEST_F(GapBufferTest, MoveCharacterRightTest) {
  for (std::size_t i = 0; i < 7; ++i) {
    buffer_.MoveCharacterLeft();
  }

  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  buffer_.MoveCharacterRight();

  EXPECT_EQ(buffer_.GetGapOffsets().first, prev_gap_offsets.first + 1);
  EXPECT_EQ(buffer_.GetGapOffsets().second, prev_gap_offsets.second + 1);
  // EXPECT_TRUE(buffer_.GetGapOffsets().first == prev_gap_offsets.first + 1 &&
  //             buffer_.GetGapOffsets().second == prev_gap_offsets.second + 1);
  EXPECT_EQ(buffer_.GetBufferContent(), test_string);
}

TEST_F(GapBufferTest, MoveCharacterLeftAtBufferStartTest) {
  /* Move the buffer all the way left */
  for (std::size_t i = 0; i < 20; ++i) {
    buffer_.MoveCharacterLeft();
  }

  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  buffer_.MoveCharacterLeft();

  EXPECT_EQ(buffer_.GetGapOffsets(), prev_gap_offsets);
  EXPECT_EQ(buffer_.GetBufferContent(), test_string);

  /* Test that gap_start_ and buffer_start_ are equal */
}

TEST_F(GapBufferTest, MoveCharacterRightAtBufferEndTest) {
  /* Move the buffer all the way right */
  for (std::size_t i = 0; i < 20; ++i) {
    buffer_.MoveCharacterRight();
  }

  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  buffer_.MoveCharacterRight();

  EXPECT_EQ(buffer_.GetGapOffsets(), prev_gap_offsets);
  EXPECT_EQ(buffer_.GetBufferContent(), test_string);

  /* Test that gap_end_ and buffer_end_ are equal */
}

TEST_F(GapBufferTest, EnlargeBufferTest) {
  std::size_t prev_buffer_size = buffer_.GetBufferSize();
  std::string prev_buffer_content = buffer_.GetBufferContent();

  /* This is giving an error because the gap offsets are not updated after the
   * characters are inserted since the buffer resize happens immediately after
   * capacity is met. */

  for (std::size_t i = 0; i < 3; ++i) {
    buffer_.MoveCharacterLeft();
  }

  std::pair<std::size_t, std::size_t> prev_gap_offsets =
      buffer_.GetGapOffsets();

  /* Filling buffer's last two slots to make it resize */
  buffer_.CharacterInsert('l');
  buffer_.CharacterInsert('x');

  prev_gap_offsets.first = prev_gap_offsets.second;

  /* Test that the gap and buffer resized properly */
  EXPECT_EQ(buffer_.GetGapSize(), prev_buffer_size);
  EXPECT_EQ(buffer_.GetBufferSize(), (2 * prev_buffer_size));

  /* Test that the gap offsets are as expected */
  EXPECT_EQ(prev_gap_offsets.first, buffer_.GetGapOffsets().first);
  EXPECT_EQ(buffer_.GetGapOffsets().second,
            buffer_.GetGapOffsets().first + prev_buffer_size);

  /* Test that the buffer contains the same information */
  EXPECT_EQ(buffer_.GetBufferContent(), "The last thlxing");
}
