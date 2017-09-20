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

#include "inplace_string/inplace_string.h"
#include <gtest/gtest.h>

// explicit instantiation needed to make code coverage metrics work correctly
template class mp::basic_inplace_string<char, 16, std::char_traits<char>>;

using namespace mp;

TEST(inPlaceString, CompileTime) { static_assert(sizeof(inplace_string<8>) == sizeof("01234567"), ""); }

TEST(inPlaceString, DefaultConstructor)
{
  inplace_string<16> str;
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPos1)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 0};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPos2)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 2};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPos3)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 8};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPos4)
{
  inplace_string<8> txt{"abcdefgh"};
  EXPECT_THROW(inplace_string<16> str(txt, 9), std::out_of_range);
}

TEST(inPlaceString, UserConstructorPosN1)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 3};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("abc", str.c_str());
  EXPECT_STREQ("abc", str.data());
  EXPECT_EQ("abc", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPosN2)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 8};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPosN3)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 10};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPosN4)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 0};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPosN5)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 2, 8};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPosN6)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 2, 2};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(2u, str.size());
  EXPECT_EQ(2u, str.length());
  EXPECT_STREQ("cd", str.c_str());
  EXPECT_STREQ("cd", str.data());
  EXPECT_EQ("cd", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(2, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPosN7)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 8, 8};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPosN8)
{
  inplace_string<8> txt{"abcdefgh"};
  EXPECT_THROW(inplace_string<16> str(txt, 9, 3), std::out_of_range);
}

TEST(inPlaceString, UserConstructorTPosN1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 3};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("abc", str.c_str());
  EXPECT_STREQ("abc", str.data());
  EXPECT_EQ("abc", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorTPosN2)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 8};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorTPosN3)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 10};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorTPosN4)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 0, 0};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorTPosN5)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 2, 8};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorTPosN6)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 2, 2};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(2u, str.size());
  EXPECT_EQ(2u, str.length());
  EXPECT_STREQ("cd", str.c_str());
  EXPECT_STREQ("cd", str.data());
  EXPECT_EQ("cd", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(2, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorTPosN7)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{txt, 8, 8};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorTPosN8)
{
  std::string txt{"abcdefgh"};
  EXPECT_THROW(inplace_string<16> str(txt, 9, 3), std::out_of_range);
}

TEST(inPlaceString, UserConstructorSV1)
{
  STRING_VIEW_NAMESPACE::string_view txt{"abcdefgh"};
  inplace_string<16> str{txt};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize1)
{
  inplace_string<16> str{"", 0};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPtrSize2)
{
  inplace_string<16> str{"test", 4};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize3)
{
  inplace_string<4> str{"test", 4};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize4)
{
  inplace_string<4> str{"test_test", 4};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtrSize5)
{
  const char s[] = {'t', '\0', 'e', '\0', 's', '\0', 't', '\0'};
  inplace_string<16> str{s, sizeof(s)};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  //  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr1)
{
  inplace_string<16> str{""};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorPtr2)
{
  inplace_string<16> str{"test"};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr3)
{
  inplace_string<4> str{"test"};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorPtr4)
{
  const char s[] = {'t', '\0', 'e', '\0', 's', '\0', 't', '\0'};
  inplace_string<16> str{s};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorNC1)
{
  inplace_string<16> str(1u, 'x');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("x", str.c_str());
  EXPECT_STREQ("x", str.data());
  EXPECT_EQ("x", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorNC2)
{
  inplace_string<16> str(3u, 'x');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("xxx", str.c_str());
  EXPECT_STREQ("xxx", str.data());
  EXPECT_EQ("xxx", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorNC3)
{
  inplace_string<16> str(0u, 'x');
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorIter1)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str{txt, txt + 8};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorIter2)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str{txt + 2, txt + 5};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("cde", str.c_str());
  EXPECT_STREQ("cde", str.data());
  EXPECT_EQ("cde", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorIter3)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str{txt, txt};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, UserConstructorIter4)
{
  inplace_string<16> str(7u, 36u);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(7u, str.size());
  EXPECT_EQ(7u, str.length());
  EXPECT_STREQ("$$$$$$$", str.c_str());
  EXPECT_STREQ("$$$$$$$", str.data());
  EXPECT_EQ("$$$$$$$", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(7, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, UserConstructorIlist1)
{
  inplace_string<16> str{'t', 'e', 's', 't'};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, CopyAssignment1)
{
  inplace_string<16> str;
  str = inplace_string<16>{"abcdefgh"};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentSV1)
{
  STRING_VIEW_NAMESPACE::string_view txt{"abcdefgh"};
  inplace_string<16> str;
  str = txt;
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentPtr1)
{
  inplace_string<16> str{"abcd"};
  str = "";
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignmentPtr2)
{
  inplace_string<16> str;
  str = "test";
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentPtr3)
{
  inplace_string<4> str;
  str = "test";
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentPtr4)
{
  const char s[] = {'t', '\0', 'e', '\0', 's', '\0', 't', '\0'};
  inplace_string<16> str;
  str = s;
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentC1)
{
  inplace_string<16> str;
  str = 't';
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  EXPECT_EQ("t", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignmentIlist1)
{
  inplace_string<16> str;
  str = {'t', 'e', 's', 't'};
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd2)
{
  std::string txt{""};
  inplace_string<16> str{""};
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd3)
{
  std::string txt;
  inplace_string<16> str;
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd4)
{
  const std::string txt{"abcdefgh"};
  const inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd5)
{
  const std::string txt{""};
  const inplace_string<16> str{""};
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, BeginEnd6)
{
  const std::string txt;
  const inplace_string<16> str;
  EXPECT_EQ(std::distance(std::begin(txt), std::end(txt)), std::distance(std::begin(str), std::end(str)));
  EXPECT_TRUE(std::equal(std::begin(txt), std::end(txt), std::begin(str), std::end(str)));
}

TEST(inPlaceString, RBeginREnd1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, RBeginREnd2)
{
  std::string txt{""};
  inplace_string<16> str{""};
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, RBeginREnd3)
{
  std::string txt;
  inplace_string<16> str;
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, RBeginREnd4)
{
  const std::string txt{"abcdefgh"};
  const inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, RBeginREnd5)
{
  const std::string txt{""};
  const inplace_string<16> str{""};
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, RBeginREnd6)
{
  const std::string txt;
  const inplace_string<16> str;
  EXPECT_EQ(std::distance(std::rbegin(txt), std::rend(txt)), std::distance(std::rbegin(str), std::rend(str)));
  EXPECT_TRUE(std::equal(std::rbegin(txt), std::rend(txt), std::rbegin(str), std::rend(str)));
}

TEST(inPlaceString, CBeginCEnd1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(txt.cbegin(), txt.cend()), std::distance(str.cbegin(), str.cend()));
  EXPECT_TRUE(std::equal(txt.cbegin(), txt.cend(), str.cbegin(), str.cend()));
}

TEST(inPlaceString, CBeginCEnd2)
{
  std::string txt{""};
  inplace_string<16> str{""};
  EXPECT_EQ(std::distance(txt.cbegin(), txt.cend()), std::distance(str.cbegin(), str.cend()));
  EXPECT_TRUE(std::equal(txt.cbegin(), txt.cend(), str.cbegin(), str.cend()));
}

TEST(inPlaceString, CBeginCEnd3)
{
  std::string txt;
  inplace_string<16> str;
  EXPECT_EQ(std::distance(txt.cbegin(), txt.cend()), std::distance(str.cbegin(), str.cend()));
  EXPECT_TRUE(std::equal(txt.cbegin(), txt.cend(), str.cbegin(), str.cend()));
}

TEST(inPlaceString, CRBeginCREnd1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(std::distance(txt.crbegin(), txt.crend()), std::distance(str.crbegin(), str.crend()));
  EXPECT_TRUE(std::equal(txt.crbegin(), txt.crend(), str.crbegin(), str.crend()));
}

TEST(inPlaceString, CRBeginCREnd2)
{
  std::string txt{""};
  inplace_string<16> str{""};
  EXPECT_EQ(std::distance(txt.crbegin(), txt.crend()), std::distance(str.crbegin(), str.crend()));
  EXPECT_TRUE(std::equal(txt.crbegin(), txt.crend(), str.crbegin(), str.crend()));
}

TEST(inPlaceString, CRBeginCREnd3)
{
  std::string txt;
  inplace_string<16> str;
  EXPECT_EQ(std::distance(txt.crbegin(), txt.crend()), std::distance(str.crbegin(), str.crend()));
  EXPECT_TRUE(std::equal(txt.crbegin(), txt.crend(), str.crbegin(), str.crend()));
}

TEST(inPlaceString, MaxSize1)
{
  EXPECT_EQ(0u, inplace_string<0>{}.max_size());
  EXPECT_EQ(1u, inplace_string<1>{}.max_size());
  EXPECT_EQ(16u, inplace_string<16>{}.max_size());
  EXPECT_EQ(255u, inplace_string<255>{}.max_size());
}

TEST(inPlaceString, MaxSize2)
{
  EXPECT_EQ(16u, inplace_string<16>{"test"}.max_size());
  EXPECT_EQ(255u, inplace_string<255>{"test"}.max_size());
}

TEST(inPlaceString, MaxSize3)
{
  {
    inplace_string<16> str{"test"};
    str = "abcdefgh";
    EXPECT_EQ(16u, str.max_size());
  }
  {
    inplace_string<255> str{"test"};
    str = "abcdefgh";
    EXPECT_EQ(255u, str.max_size());
  }
}

TEST(inPlaceString, ResizeNC1)
{
  inplace_string<16> str;
  EXPECT_TRUE(str.empty());
  str.resize(5, '$');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_STREQ("$$$$$", str.c_str());
  EXPECT_STREQ("$$$$$", str.data());
  EXPECT_EQ("$$$$$", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(5, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, ResizeNC2)
{
  inplace_string<16> str{"abc"};
  EXPECT_EQ(3u, str.size());
  str.resize(5, '$');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_STREQ("abc$$", str.c_str());
  EXPECT_STREQ("abc$$", str.data());
  EXPECT_EQ("abc$$", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(5, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, ResizeNC3)
{
  inplace_string<16> str{"abcde"};
  EXPECT_EQ(5u, str.size());
  str.resize(5, '$');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_STREQ("abcde", str.c_str());
  EXPECT_STREQ("abcde", str.data());
  EXPECT_EQ("abcde", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(5, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, ResizeNC4)
{
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ(8u, str.size());
  str.resize(5, '$');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_STREQ("abcde", str.c_str());
  EXPECT_STREQ("abcde", str.data());
  EXPECT_EQ("abcde", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(5, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, ResizeN1)
{
  inplace_string<16> str{"abc"};
  EXPECT_EQ(3u, str.size());
  str.resize(5);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(5u, str.size());
  EXPECT_EQ(5u, str.length());
  EXPECT_STREQ("abc", str.c_str());
  EXPECT_STREQ("abc", str.data());
  EXPECT_EQ('\0', str[3]);
  EXPECT_EQ('\0', str[4]);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(5, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, Clear1)
{
  inplace_string<16> str{"test"};
  str.clear();
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, Clear2)
{
  inplace_string<16> str{"test"};
  str.clear();
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, IndexOperator1)
{
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ('a', str[0]);
  EXPECT_EQ('c', str[2]);
  EXPECT_EQ('e', str[4]);
  EXPECT_EQ('h', str[7]);
}

TEST(inPlaceString, IndexOperator2)
{
  const inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ('a', str[0]);
  EXPECT_EQ('c', str[2]);
  EXPECT_EQ('e', str[4]);
  EXPECT_EQ('h', str[7]);
}

TEST(inPlaceString, At1)
{
  inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ('a', str.at(0));
  EXPECT_EQ('c', str.at(2));
  EXPECT_EQ('e', str.at(4));
  EXPECT_EQ('h', str.at(7));
  EXPECT_THROW(str.at(8), std::out_of_range);
  EXPECT_THROW(str.at(255), std::out_of_range);
}

TEST(inPlaceString, At2)
{
  const inplace_string<16> str{"abcdefgh"};
  EXPECT_EQ('a', str.at(0));
  EXPECT_EQ('c', str.at(2));
  EXPECT_EQ('e', str.at(4));
  EXPECT_EQ('h', str.at(7));
  EXPECT_THROW(str.at(8), std::out_of_range);
  EXPECT_THROW(str.at(255), std::out_of_range);
}

TEST(inPlaceString, Front1)
{
  {
    inplace_string<16> str{"abcdefgh"};
    EXPECT_EQ('a', str.front());
  }
  {
    inplace_string<3> str{"abc"};
    EXPECT_EQ('a', str.front());
  }
  {
    inplace_string<1> str{"x"};
    EXPECT_EQ('x', str.front());
  }
}

TEST(inPlaceString, Front2)
{
  {
    const inplace_string<16> str{"abcdefgh"};
    EXPECT_EQ('a', str.front());
  }
  {
    const inplace_string<3> str{"abc"};
    EXPECT_EQ('a', str.front());
  }
  {
    const inplace_string<1> str{"x"};
    EXPECT_EQ('x', str.front());
  }
}

TEST(inPlaceString, Back1)
{
  {
    inplace_string<16> str{"abcdefgh"};
    EXPECT_EQ('h', str.back());
  }
  {
    inplace_string<3> str{"abc"};
    EXPECT_EQ('c', str.back());
  }
  {
    inplace_string<1> str{"x"};
    EXPECT_EQ('x', str.back());
  }
}

TEST(inPlaceString, Back2)
{
  {
    const inplace_string<16> str{"abcdefgh"};
    EXPECT_EQ('h', str.back());
  }
  {
    const inplace_string<3> str{"abc"};
    EXPECT_EQ('c', str.back());
  }
  {
    const inplace_string<1> str{"x"};
    EXPECT_EQ('x', str.back());
  }
}

TEST(inPlaceString, AppendOther1)
{
  inplace_string<8> txt{"def"};
  inplace_string<16> str;
  str.append(inplace_string<3>{"abc"}).append(txt);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("abcdef", str.c_str());
  EXPECT_STREQ("abcdef", str.data());
  EXPECT_EQ("abcdef", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AppendOther2)
{
  inplace_string<8> txt{"def"};
  inplace_string<16> str{"abc"};
  str.append(txt).append(inplace_string<3>{"gh"});
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AppendOtherPosN1)
{
  inplace_string<8> txt{"def"};
  inplace_string<16> str;
  str.append(inplace_string<3>{"abc"}).append(txt);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("abcdef", str.c_str());
  EXPECT_STREQ("abcdef", str.data());
  EXPECT_EQ("abcdef", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AppendOtherPosN2)
{
  inplace_string<8> txt{"def"};
  inplace_string<16> str{"abc"};
  str.append(txt).append(inplace_string<3>{"gh"});
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}



TEST(inPlaceString, AssignOther1)
{
  inplace_string<16> str;
  str.assign(inplace_string<8>{"abcdefgh"});
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOther2)
{
  inplace_string<16> str{"abcdefgh"};
  str.assign(inplace_string<8>{});
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignOtherPos1)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPos2)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 2);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPos3)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 8);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignOtherPos4)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  EXPECT_THROW(str.assign(txt, 9), std::out_of_range);
}

TEST(inPlaceString, AssignOtherPosN1)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 3);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("abc", str.c_str());
  EXPECT_STREQ("abc", str.data());
  EXPECT_EQ("abc", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPosN2)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 8);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPosN3)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 10);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPosN4)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 0);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignOtherPosN5)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 2, 8);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPosN6)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 2, 2);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(2u, str.size());
  EXPECT_EQ(2u, str.length());
  EXPECT_STREQ("cd", str.c_str());
  EXPECT_STREQ("cd", str.data());
  EXPECT_EQ("cd", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(2, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignOtherPosN7)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str{txt, 8, 8};
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignOtherPosN8)
{
  inplace_string<8> txt{"abcdefgh"};
  inplace_string<16> str;
  EXPECT_THROW(str.assign(txt, 9, 3), std::out_of_range);
}

TEST(inPlaceString, AssignSV1)
{
  STRING_VIEW_NAMESPACE::string_view txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN1)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 3);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("abc", str.c_str());
  EXPECT_STREQ("abc", str.data());
  EXPECT_EQ("abc", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN2)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 8);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN3)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 10);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN4)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 0, 0);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignTPosN5)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 2, 8);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(6u, str.size());
  EXPECT_EQ(6u, str.length());
  EXPECT_STREQ("cdefgh", str.c_str());
  EXPECT_STREQ("cdefgh", str.data());
  EXPECT_EQ("cdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(6, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN6)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 2, 2);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(2u, str.size());
  EXPECT_EQ(2u, str.length());
  EXPECT_STREQ("cd", str.c_str());
  EXPECT_STREQ("cd", str.data());
  EXPECT_EQ("cd", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(2, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignTPosN7)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  str.assign(txt, 8, 8);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_NE(str.data(), nullptr);
  EXPECT_STREQ("", str.c_str());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignTPosN8)
{
  std::string txt{"abcdefgh"};
  inplace_string<16> str;
  EXPECT_THROW(str.assign(txt, 9, 3), std::out_of_range);
}

TEST(inPlaceString, AssignPtrSize1)
{
  inplace_string<16> str;
  str.assign("", 0);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignPtrSize2)
{
  inplace_string<16> str;
  str.assign("test", 4);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtrSize3)
{
  inplace_string<4> str;
  str.assign("test", 4);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtrSize4)
{
  inplace_string<4> str;
  str.assign("test_test", 4);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtrSize5)
{
  const char s[] = {'t', '\0', 'e', '\0', 's', '\0', 't', '\0'};
  inplace_string<16> str;
  str.assign(s, sizeof(s));
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  //  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtr1)
{
  inplace_string<16> str;
  str.assign("");
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignPtr2)
{
  inplace_string<16> str;
  str.assign("test");
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtr3)
{
  inplace_string<4> str;
  str.assign("test");
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignPtr4)
{
  const char s[] = {'t', '\0', 'e', '\0', 's', '\0', 't', '\0'};
  inplace_string<16> str;
  str.assign(s);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("t", str.c_str());
  EXPECT_STREQ("t", str.data());
  EXPECT_EQ(s, str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignIlist1)
{
  inplace_string<16> str;
  str.assign({'t', 'e', 's', 't'});
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(4u, str.size());
  EXPECT_EQ(4u, str.length());
  EXPECT_STREQ("test", str.c_str());
  EXPECT_STREQ("test", str.data());
  EXPECT_EQ("test", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(4, std::distance(std::begin(str), std::end(str)));
}


TEST(inPlaceString, AssignNC1)
{
  inplace_string<16> str;
  str.assign(1u, 'x');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(1u, str.size());
  EXPECT_EQ(1u, str.length());
  EXPECT_STREQ("x", str.c_str());
  EXPECT_STREQ("x", str.data());
  EXPECT_EQ("x", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(1, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignNC2)
{
  inplace_string<16> str;
  str.assign(3u, 'x');
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("xxx", str.c_str());
  EXPECT_STREQ("xxx", str.data());
  EXPECT_EQ("xxx", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignNC3)
{
  inplace_string<16> str;
  str.assign(0u, 'x');
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}

TEST(inPlaceString, AssignIter1)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str;
  str.assign(txt, txt + 8);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(8u, str.size());
  EXPECT_EQ(8u, str.length());
  EXPECT_STREQ("abcdefgh", str.c_str());
  EXPECT_STREQ("abcdefgh", str.data());
  EXPECT_EQ("abcdefgh", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(8, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignIter2)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str;
  str.assign(txt + 2, txt + 5);
  EXPECT_FALSE(str.empty());
  EXPECT_EQ(3u, str.size());
  EXPECT_EQ(3u, str.length());
  EXPECT_STREQ("cde", str.c_str());
  EXPECT_STREQ("cde", str.data());
  EXPECT_EQ("cde", str);
  EXPECT_NE(std::begin(str), std::end(str));
  EXPECT_EQ(3, std::distance(std::begin(str), std::end(str)));
}

TEST(inPlaceString, AssignIter3)
{
  const char txt[] = "abcdefgh";
  inplace_string<16> str;
  str.assign(txt, txt);
  EXPECT_TRUE(str.empty());
  EXPECT_EQ(0u, str.size());
  EXPECT_EQ(0u, str.length());
  EXPECT_STREQ("", str.c_str());
  EXPECT_STREQ("", str.data());
  EXPECT_EQ("", str);
  EXPECT_EQ(std::begin(str), std::end(str));
}
