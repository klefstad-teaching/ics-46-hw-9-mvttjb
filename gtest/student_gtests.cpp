#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

// ladder tests

const set<string> predefined_word_list = {
    "cat", "bat", "rat", "mat", "hat", "hot", "dot", "dog",
    "code", "cade", "cate", "date", "data",
    "marty", "party", "parts", "carts", "cards", "curds", "curls",
    "car", "cat", "chat", "cheat",
    "work", "worn", "worm", "form", "foam", "flam", "flay", "play"
};

// setup word list for all ladder tests
class LadderTest : public ::testing::Test {
protected:
  set<string> word_list;

  void SetUp() override {
    word_list = predefined_word_list; // use predefined test word list
  }
};

// Test is_adjacent() function
TEST_F(LadderTest, IsAdjacentTest) {
  EXPECT_TRUE(is_adjacent("cat", "bat"));
  EXPECT_TRUE(is_adjacent("chat", "hat"));
  EXPECT_TRUE(is_adjacent("cat", "coat"));
  EXPECT_FALSE(is_adjacent("cat", "dog"));
  EXPECT_FALSE(is_adjacent("apple", "applesauce"));
}

// Test generate_word_ladder() function
TEST_F(LadderTest, WordLadderBasicTest) {
  vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
  EXPECT_FALSE(ladder.empty());
  EXPECT_EQ(ladder.front(), "cat");
  EXPECT_EQ(ladder.back(), "dog");
}

TEST_F(LadderTest, WordLadderComplexTest) {
  vector<string> ladder = generate_word_ladder("code", "data", word_list);
  EXPECT_FALSE(ladder.empty());
  EXPECT_EQ(ladder.front(), "code");
  EXPECT_EQ(ladder.back(), "data");
}

TEST_F(LadderTest, WordLadderWithInsertDelete) {
  vector<string> ladder = generate_word_ladder("car", "cheat", word_list);
  EXPECT_FALSE(ladder.empty());
  EXPECT_EQ(ladder.front(), "car");
  EXPECT_EQ(ladder.back(), "cheat");
}

TEST_F(LadderTest, WordLadderNoPath) {
  vector<string> ladder = generate_word_ladder("xyz", "apple", word_list);
  EXPECT_TRUE(ladder.empty());  // No valid path expected
}

TEST_F(LadderTest, WordLadderSameWord) {
  vector<string> ladder = generate_word_ladder("xyz", "apple", word_list);
  EXPECT_TRUE(ladder.empty());  // No valid path expected
}
