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

#include <array>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <limits>
#include <string>

#ifdef _MSC_VER
#include <string_view>
#define STRING_VIEW_NAMESPACE ::std
#else
#include <experimental/string_view>
#define STRING_VIEW_NAMESPACE ::std::experimental
#endif

namespace mp {

  namespace detail {
    template<typename... Args>
    using Requires = std::enable_if_t<std::conjunction<Args...>::value, bool>;

    template<size_t Size>
    using impl_size_type_helper =
        std::conditional_t<Size == 1, std::uint8_t, std::conditional_t<Size == 2, std::uint16_t, std::uint32_t>>;
  }

  template<typename CharT, std::size_t MaxSize, typename Traits = std::char_traits<std::decay_t<CharT>>>
  class basic_inplace_string {
    using impl_size_type = ::mp::detail::impl_size_type_helper<sizeof(CharT)>;
    static_assert(MaxSize <= std::numeric_limits<impl_size_type>::max(),
                  "impl_size_type type too small to store MaxSize characters");

  public:
    using traits_type = Traits;
    using value_type = CharT;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;

#if defined(_MSC_VER) && (_ITERATOR_DEBUG_LEVEL != 0)
    using iterator = stdext::checked_array_iterator<value_type*>;
    using const_iterator = stdext::checked_array_iterator<const value_type*>;
#else
    using iterator = value_type*;
    using const_iterator = const value_type*;
#endif
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    static constexpr size_type npos = static_cast<size_type>(-1);

    // constructors
    constexpr basic_inplace_string() noexcept { clear(); }
    basic_inplace_string(const basic_inplace_string&) = default;
    template<std::size_t OtherMaxSize>
    constexpr basic_inplace_string(const basic_inplace_string<CharT, OtherMaxSize, Traits>& str, size_type pos)
        : basic_inplace_string{STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>{str}.substr(pos)}
    {
    }
    template<std::size_t OtherMaxSize>
    constexpr basic_inplace_string(const basic_inplace_string<CharT, OtherMaxSize, Traits>& str, size_type pos,
                                   size_type n)
        : basic_inplace_string{STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>{str}.substr(pos, n)}
    {
    }
    template<
        class T,
        detail::Requires<std::is_convertible<const T&, STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>>> = true>
    constexpr basic_inplace_string(const T& t, size_type pos, size_type n)
        : basic_inplace_string{STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>{t}.substr(pos, n)}
    {
    }
    constexpr explicit basic_inplace_string(STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits> sv)
        : basic_inplace_string{sv.data(), sv.size()}
    {
    }
    constexpr basic_inplace_string(const_pointer s, size_type count) noexcept { assign(s, count); }
    constexpr basic_inplace_string(const_pointer s) noexcept : basic_inplace_string{s, traits_type::length(s)} {}
    constexpr basic_inplace_string(size_type n, value_type c) { assign(n, c); }
    template<class InputIterator>
    constexpr basic_inplace_string(InputIterator begin, InputIterator end)
    {
      assign(begin, end);
    }
    constexpr basic_inplace_string(std::initializer_list<CharT> ilist) { assign(ilist.begin(), ilist.size()); }

    // assignment
    basic_inplace_string& operator=(const basic_inplace_string&) = default;
    constexpr basic_inplace_string& operator=(STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits> sv)
    {
      return assign(sv);
    }
    constexpr basic_inplace_string& operator=(const_pointer s) noexcept { return assign(s); }
    constexpr basic_inplace_string& operator=(value_type c) noexcept { return assign(1, c); }
    constexpr basic_inplace_string& operator=(std::initializer_list<CharT> ilist)
    {
      return assign(ilist.begin(), ilist.size());
    }

// iterators
#if defined(_MSC_VER) && (_ITERATOR_DEBUG_LEVEL != 0)
    constexpr iterator begin() { return iterator{data(), size()}; }
    constexpr const_iterator begin() const { return const_iterator{data(), size()}; }
#else
    constexpr iterator begin() { return data(); }
    constexpr const_iterator begin() const { return data(); }
#endif
    constexpr iterator end() { return begin() + size(); }
    constexpr const_iterator end() const { return begin() + size(); }

    constexpr reverse_iterator rbegin() { return reverse_iterator{end()}; }
    constexpr const_reverse_iterator rbegin() const { return const_reverse_iterator{end()}; }
    constexpr reverse_iterator rend() { return reverse_iterator(begin()); }
    constexpr const_reverse_iterator rend() const { return const_reverse_iterator{begin()}; }

#if defined(_MSC_VER) && (_ITERATOR_DEBUG_LEVEL != 0)
    constexpr const_iterator cbegin() const { return const_iterator{data(), size()}; }
#else
    constexpr const_iterator cbegin() const { return data(); }
#endif
    constexpr const_iterator cend() const { return begin() + size(); }
    constexpr const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; }
    constexpr const_reverse_iterator crend() const { return const_reverse_iterator{cbegin()}; }

    // capacity
    constexpr size_type size() const { return max_size() - static_cast<impl_size_type>(chars_.back()); }
    constexpr size_type length() const { return size(); }
    constexpr size_type max_size() const { return MaxSize; }
    constexpr void clear() { size(0); }
    constexpr bool empty() const { return size() == 0; }

    // element access
    constexpr const_reference operator[](size_type pos) const { return *(begin() + pos); }
    constexpr reference operator[](size_type pos) { return *(begin() + pos); }
    constexpr const_reference at(size_type pos) const
    {
      if(pos >= size()) throw std::out_of_range("inplace_string::at: 'pos' out of range");
      return (*this)[pos];
    }
    constexpr reference at(size_type pos)
    {
      if(pos >= size()) throw std::out_of_range("inplace_string::at: 'pos' out of range");
      return (*this)[pos];
    }
    constexpr reference front() { return (*this)[0]; }
    constexpr const_reference front() const { return (*this)[0]; }
    constexpr reference back() { return (*this)[size() - 1]; }
    constexpr const_reference back() const { return (*this)[size() - 1]; }

    // modifiers
    template<std::size_t OtherMaxSize>
    constexpr basic_inplace_string& assign(const basic_inplace_string<CharT, OtherMaxSize, Traits>& str)
    {
      return assign(str.data(), str.size());
    }
    template<std::size_t OtherMaxSize>
    constexpr basic_inplace_string& assign(const basic_inplace_string<CharT, OtherMaxSize, Traits>& str, size_type pos,
                                           size_type count = npos)
    {
      return assign(STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>{str}.substr(pos, count));
    }
    constexpr basic_inplace_string& assign(STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits> sv)
    {
      return assign(sv.data(), sv.size());
    }
    template<class T,
             detail::Requires<std::is_convertible<const T&, STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>>,
                              std::negation<std::is_convertible<const T&, const CharT*>>> = true>
    constexpr basic_inplace_string& assign(const T& t, size_type pos, size_type count = npos)
    {
      return assign(STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>{t}.substr(pos, count));
    }
    constexpr basic_inplace_string& assign(const_pointer s, size_type count) noexcept
    {
      assert(count <= MaxSize);
      traits_type::copy(data(), s, count);
      size(count);
      return *this;
    }
    constexpr basic_inplace_string& assign(const_pointer s) noexcept { return assign(s, traits_type::length(s)); };
    constexpr basic_inplace_string& assign(std::initializer_list<CharT> ilist)
    {
      return assign(ilist.begin(), ilist.size());
    }
    constexpr basic_inplace_string& assign(size_type count, CharT ch)
    {
      assert(count <= MaxSize);
      traits_type::assign(data(), count, ch);
      size(count);
      return *this;
    }
    template<class InputIt>
    constexpr basic_inplace_string& assign(InputIt first, InputIt last)
    {
      assert(std::distance(first, last) <= static_cast<std::ptrdiff_t>(MaxSize));
      const auto count = std::copy(first, last, chars_.begin()) - chars_.begin();
      size(count);
      return *this;
    }

    // string operations
    constexpr const_pointer c_str() const { return data(); }
    constexpr pointer data() { return chars_.data(); }
    constexpr const_pointer data() const { return chars_.data(); }
    constexpr operator STRING_VIEW_NAMESPACE::basic_string_view<CharT, Traits>() const noexcept
    {
      return {data(), size()};
    }

    // modifiers
    constexpr void swap(basic_inplace_string& other) { std::swap(chars_, other.chars_); }

  private:
    std::array<value_type, MaxSize + 1> chars_;  // size is stored as max_size() - size() on the last byte

    constexpr void size(size_type s) noexcept
    {
      chars_[s] = '\0';
      chars_.back() = static_cast<impl_size_type>(max_size() - s);
    }
  };

  // relational operators
  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator==(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                            const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return std::equal(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator!=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                            const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                           const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return std::lexicographical_compare(std::begin(lhs), std::end(lhs), std::begin(rhs), std::end(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                            const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(rhs < lhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                           const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return rhs < lhs;
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs,
                            const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(lhs < rhs);
  }

  // comparison with c-style string
  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator==(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return std::equal(lhs, lhs + Traits::length(lhs), std::begin(rhs), std::end(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator==(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return std::equal(std::begin(lhs), std::end(lhs), rhs, rhs + Traits::length(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator!=(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(lhs == rhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator!=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return !(lhs == rhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return std::lexicographical_compare(lhs, lhs + Traits::length(lhs), std::begin(rhs), std::end(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return std::lexicographical_compare(std::begin(lhs), std::end(lhs), rhs, rhs + Traits::length(rhs));
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<=(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(rhs < lhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator<=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return !(rhs < lhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return rhs < lhs;
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return rhs < lhs;
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>=(const CharT* lhs, const basic_inplace_string<CharT, MaxSize, Traits>& rhs)
  {
    return !(lhs < rhs);
  }

  template<typename CharT, std::size_t MaxSize, class Traits>
  constexpr bool operator>=(const basic_inplace_string<CharT, MaxSize, Traits>& lhs, const CharT* rhs)
  {
    return !(lhs < rhs);
  }

  // input/output
  template<typename CharT, std::size_t MaxSize, class Traits>
  inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                       const basic_inplace_string<CharT, MaxSize, Traits>& v)
  {
    return os << v.data();
  }

  // conversions
  template<typename CharT, std::size_t MaxSize, class Traits>
  inline std::basic_string<CharT, Traits> to_string(const basic_inplace_string<CharT, MaxSize, Traits>& v)
  {
    return {v.data(), v.size()};
  }

  // aliases
  template<std::size_t MaxSize>
  using inplace_string = basic_inplace_string<char, MaxSize>;
  template<std::size_t MaxSize>
  using inplace_wstring = basic_inplace_string<wchar_t, MaxSize>;
  //  template<std::size_t MaxSize>
  //  using inplace_u16string = basic_inplace_string<char16_t, MaxSize>;
  //  template<std::size_t MaxSize>
  //  using inplace_u32string = basic_inplace_string<char32_t, MaxSize>;
}
