#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do
                           // this in one cpp file
#include <iostream>
#include <stdexcept>
#include <string>

#include "catch.hpp"
#include "listString.h"
#include "memoryPool.h"
using namespace std;

TEST_CASE("Testing Add", "[!throws]") {
  ListString::setPool(new MemoryPool());
  ListString words[10];
  string one = "hello";
  string two = "what's";
  string three = "going";
  string four = "on";
  words[1] = ListString{one};
  words[2] = ListString{two};
  words[3] = ListString{three};
  words[4] = ListString{four};
  CHECK(words[1].getWord().compare(one) == 0);
  CHECK(words[2].getWord().compare(two) == 0);
  CHECK(words[3].getWord().compare(three) == 0);
  CHECK(words[4].getWord().compare(four) == 0);
}

TEST_CASE("Testing Remove", "[!throws]") {
  try {
    ListString::setPool(new MemoryPool());
  } catch (logic_error const&) {
  }
  ListString words[10];
  string one = "hello";
  string two = "what's";
  words[1] = ListString{one};
  words[2] = ListString{};
  CHECK_THROWS(words[2].getWord());
  CHECK(words[1].getWord().compare(one) == 0);
}

TEST_CASE("Testing Pig Latin", "[!throws]") {
  try {
    ListString::setPool(new MemoryPool());
  } catch (logic_error const&) {
  }
  ListString words[10];

  string one = "hello";
  string four = "on";
  string onePig = "ellohay";
  string fourPig = "onway";

  words[5] = ListString{one};
  words[6] = ListString{four};
  words[5].igpayAtinlay();
  words[6].igpayAtinlay();
  CHECK(words[5].getWord().compare(onePig) == 0);
  CHECK(words[6].getWord().compare(fourPig) == 0);
}
