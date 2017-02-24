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

#pragma once

#include <string>
#include <array>
#include <iterator>
#include <cstdint>
#include <limits>
#include <cassert>

template<typename CharT, std::size_t MaxSize, typename Traits = std::char_traits<CharT>>
class basic_in_place_string {
public:
  using traits_type = Traits;
  using value_type = CharT;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::uint8_t;
  using difference_type = std::ptrdiff_t;

  using iterator = value_type*;
  using const_iterator = const value_type*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  static_assert(MaxSize <= std::numeric_limits<size_type>::max(), "size_type type does not allow MaxSize characters");

  constexpr basic_in_place_string() { front() = '\0'; size(0); }
  constexpr basic_in_place_string(const_pointer s, size_type count)
  {
    assign(s, count);
  }
  constexpr basic_in_place_string(const_pointer s) : basic_in_place_string(s, traits_type::length(s)) {}
  constexpr basic_in_place_string(const basic_in_place_string&) = default;
  constexpr basic_in_place_string& operator=(const basic_in_place_string&) = default;
  constexpr basic_in_place_string& operator=(const_pointer s)
  {
    return assign(s, traits_type::length(s));
  }

  constexpr basic_in_place_string& assign(const_pointer s, size_type count)
  {
    assert(count <= MaxSize);
    traits_type::copy(begin(), s, count);
    (*this)[count] = '\0';
    size(count);
    return *this;
  }
  constexpr basic_in_place_string& assign(const_pointer s)  { return assign(s, traits_type::length(s)); };

  // iterators
  constexpr iterator begin()                                { return data(); }
  constexpr const_iterator begin() const                    { return data(); }
  constexpr const_iterator cbegin() const                   { return data(); }
  constexpr iterator end()                                  { return begin() + size(); }
  constexpr const_iterator end() const                      { return begin() + size(); }
  constexpr const_iterator cend() const                     { return begin() + size(); }

  constexpr reverse_iterator rbegin()                       { return reverse_iterator(end()); }
  constexpr const_reverse_iterator rbegin() const           { return const_reverse_iterator(end()); }
  constexpr const_reverse_iterator crbegin() const          { return const_reverse_iterator(cend()); }
  constexpr reverse_iterator rend()                         { return reverse_iterator(begin()); }
  constexpr const_reverse_iterator rend() const             { return const_reverse_iterator(begin()); }
  constexpr const_reverse_iterator crend() const            { return const_reverse_iterator(cbegin()); }

  // element access
  constexpr reference operator[](size_type pos)             { return *(begin() + pos); }
  constexpr const_reference operator[](size_type pos) const { return *(begin() + pos); }
  constexpr reference at(size_type pos)                     { return chars_.at(pos); }
  constexpr const_reference at(size_type pos) const         { return chars_.at(pos); }
  constexpr reference front()                               { return (*this)[0]; }
  constexpr const_reference front() const                   { return (*this)[0]; }
  constexpr reference back()                                { return (*this)[size() - 1]; }
  constexpr const_reference back() const                    { return (*this)[size() - 1]; }
  constexpr pointer data()                                  { return chars_.data(); }
  constexpr const_pointer data() const                      { return chars_.data(); }
  constexpr const_pointer c_str() const                     { return data(); }

  // capacity
  constexpr size_type size() const      { return max_size() - static_cast<size_type>(chars_.back()); }
  constexpr size_type length() const    { return size(); }
  constexpr size_type max_size() const  { return MaxSize; }
  constexpr bool empty() const          { return size() == 0; }

  // modifiers
  constexpr void swap(basic_in_place_string& other) { std::swap(chars_, other.chars_); }

private:
  std::array<value_type, MaxSize + 1> chars_; // size is stored as max_size() - size() on the last byte
  void size(size_type s) { chars_.back() = max_size() - static_cast<value_type>(s); }
};


template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator==(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator!=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(lhs == rhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                         const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return std::lexicographical_compare(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(rhs < lhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                         const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return rhs < lhs; }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(lhs < rhs); }


template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator==(const CharT* lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return std::equal(lhs, lhs + Traits::length(lhs), std::begin(rhs), std::end(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator==(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const CharT* rhs)
{ return std::equal(std::begin(lhs), std::end(lhs), rhs, rhs + Traits::length(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator!=(const CharT* lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(lhs == rhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator!=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const CharT* rhs)
{ return !(lhs == rhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<(const CharT* lhs,
                         const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return std::lexicographical_compare(lhs, lhs + Traits::length(lhs), std::begin(rhs), std::end(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                         const CharT* rhs)
{ return std::lexicographical_compare(std::begin(lhs), std::end(lhs), rhs, rhs + Traits::length(rhs)); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<=(const CharT* lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(rhs < lhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator<=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const CharT* rhs)
{ return !(rhs < lhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>(const CharT* lhs,
                         const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return rhs < lhs; }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                         const CharT* rhs)
{ return rhs < lhs; }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>=(const CharT* lhs,
                          const basic_in_place_string<CharT, MaxSize, Traits>& rhs)
{ return !(lhs < rhs); }

template<typename CharT, std::size_t MaxSize, class Traits>
constexpr bool operator>=(const basic_in_place_string<CharT, MaxSize, Traits>& lhs,
                          const CharT* rhs)
{ return !(lhs < rhs); }


template<typename CharT, std::size_t MaxSize, class Traits>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                              const basic_in_place_string<CharT, MaxSize, Traits>& v)
{
  return os << v.data();
}

template<std::size_t MaxSize> using in_place_string    = basic_in_place_string<char,     MaxSize>;
template<std::size_t MaxSize> using in_place_wstring   = basic_in_place_string<wchar_t,  MaxSize>;
template<std::size_t MaxSize> using in_place_u16string = basic_in_place_string<char16_t, MaxSize>;
template<std::size_t MaxSize> using in_place_u32string = basic_in_place_string<char32_t, MaxSize>;
