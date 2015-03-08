// Copyright Benoit Blanchon 2014-2015
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson

#include <gtest/gtest.h>
#include <ArduinoJson.h>

class JsonArray_Container_Tests : public ::testing::Test {
 protected:
  JsonArray_Container_Tests() : _array(_jsonBuffer.createArray()) {}

  template <typename T>
  void firstMustEqual(T expected) {
    itemMustEqual(0, expected);
  }

  template <typename T>
  void secondMustEqual(T expected) {
    itemMustEqual(1, expected);
  }

  template <typename T>
  void firstMustReference(const T& expected) {
    itemMustReference(0, expected);
  }

  template <typename T>
  void secondMustReference(const T& expected) {
    itemMustReference(1, expected);
  }

  void sizeMustBe(int expected) { EXPECT_EQ(expected, _array.size()); }

  DynamicJsonBuffer _jsonBuffer;
  JsonArray& _array;

 private:
  template <typename T>
  void itemMustEqual(int index, T expected) {
    EXPECT_EQ(expected, _array[index].as<T>());
  }

  template <typename T>
  void itemMustReference(int index, const T& expected) {
    EXPECT_EQ(&expected, &_array[index].as<T&>());
  }
};

TEST_F(JsonArray_Container_Tests, SuccessIsTrue) {
  EXPECT_TRUE(_array.success());
}

TEST_F(JsonArray_Container_Tests, InitialSizeIsZero) { sizeMustBe(0); }

TEST_F(JsonArray_Container_Tests, Grow_WhenValuesAreAdded) {
  _array.add("hello");
  sizeMustBe(1);

  _array.add("world");
  sizeMustBe(2);
}

TEST_F(JsonArray_Container_Tests, CanStoreIntegers) {
  _array.add(123);
  _array.add(456);

  firstMustEqual(123);
  secondMustEqual(456);
}

TEST_F(JsonArray_Container_Tests, CanStoreDoubles) {
  _array.add(123.45);
  _array.add(456.78);

  firstMustEqual(123.45);
  secondMustEqual(456.78);
}

TEST_F(JsonArray_Container_Tests, CanStoreBooleans) {
  _array.add(true);
  _array.add(false);

  firstMustEqual(true);
  secondMustEqual(false);
}

TEST_F(JsonArray_Container_Tests, CanStoreCharPtrs) {
  const char* firstString = "h3110";
  const char* secondString = "w0r1d";

  _array.add(firstString);
  _array.add(secondString);

  firstMustEqual(firstString);
  secondMustEqual(secondString);
}

TEST_F(JsonArray_Container_Tests, CanStoreStrings) {
  const String firstString = "h3110";
  const String secondString = "w0r1d";

  _array.add(firstString);
  _array.add() = secondString;

  firstMustEqual(firstString);
  secondMustEqual(secondString);
}

TEST_F(JsonArray_Container_Tests, CanStoreNestedArrays) {
  JsonArray& inner_array1 = _jsonBuffer.createArray();
  JsonArray& inner_array2 = _jsonBuffer.createArray();

  _array.add(inner_array1);
  _array.add(inner_array2);

  firstMustReference(inner_array1);
  secondMustReference(inner_array2);
}

TEST_F(JsonArray_Container_Tests, CanStoreNestedObjects) {
  JsonObject& innerObject1 = _jsonBuffer.createObject();
  JsonObject& innerObject2 = _jsonBuffer.createObject();

  _array.add(innerObject1);
  _array.add(innerObject2);

  firstMustReference(innerObject1);
  secondMustReference(innerObject2);
}

TEST_F(JsonArray_Container_Tests, CanCreateNestedArrays) {
  JsonArray& inner_array1 = _array.createNestedArray();
  JsonArray& inner_array2 = _array.createNestedArray();

  firstMustReference(inner_array1);
  secondMustReference(inner_array2);
}

TEST_F(JsonArray_Container_Tests, CanCreateNestedObjects) {
  JsonObject& innerObject1 = _array.createNestedObject();
  JsonObject& innerObject2 = _array.createNestedObject();

  firstMustReference(innerObject1);
  secondMustReference(innerObject2);
}
