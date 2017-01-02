# `in_place_string<CharT, MaxSize, Traits>`

`in_place_string<CharT, MaxSize, Traits>` is a `std::string`-like class template with the difference
that the text content is always stored in-place inside the class (like in SSO case in `std::string`).
