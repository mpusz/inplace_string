// The MIT License (MIT)
//
// Copyright (c) 2016 Mateusz Pusz
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "in_place_string.h"
#include <gtest/gtest.h>

// explicit instantiation needed to make code coverage metrics work correctly
template class basic_in_place_string<char, 16, std::char_traits<char>>;

TEST(inPlaceString, CompileTime)
{
}

TEST(inPlaceString, DefaultConstructor)
{
  in_place_string<16> str;
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPtrSize1)
{
  in_place_string<16> str{"", 0};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPtrSize2)
{
  in_place_string<16> str{"test", 4};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize3)
{
  in_place_string<4> str{"test", 4};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize4)
{
  const char s[] = { 't', '\0', 'e', '\0', 's', '\0', 't', '\0' };
  in_place_string<16> str{s, sizeof(s)};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
//  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr1)
{
  in_place_string<16> str{""};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPtr2)
{
  in_place_string<16> str{"test"};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr3)
{
  in_place_string<4> str{"test"};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr4)
{
  const char s[] = { 't', '\0', 'e', '\0', 's', '\0', 't', '\0' };
  in_place_string<16> str{s};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}
