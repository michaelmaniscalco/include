#pragma once

#include <cstdint>
#include <type_traits>
#include <concepts>
#include <string_view>
#include <algorithm>


namespace maniscalco
{


    template <std::size_t N>
    struct constexpr_string
    {
        using element_type = char;
        static auto constexpr size = N;
        using value_type = element_type[size];

        constexpr constexpr_string
        (
            element_type const (&value)[N]
        ) noexcept
        {
            std::copy_n(value, size, value_);
        }

        constexpr value_type const & get() const noexcept;

        constexpr operator value_type const & () const noexcept;

        constexpr operator std::string_view const() const noexcept;

        value_type value_;
    };


    //=========================================================================
    template <typename T>
    concept constexpr_string_concept = std::is_same_v<T, constexpr_string<T::size>>;


    //=========================================================================
    static constexpr std::string_view const to_string
    (
        constexpr_string_concept auto const & source
    ) noexcept
    {
        return source;
    }

} // namespace maniscalco


//=============================================================================
template <std::size_t N>
constexpr auto maniscalco::constexpr_string<N>::get
(
) const noexcept -> value_type const & 
{
    return value_;
}


//=============================================================================
template <std::size_t N>
constexpr maniscalco::constexpr_string<N>::operator value_type const & 
(
) const noexcept
{
    return value_;
}


//=============================================================================
template <std::size_t N>
constexpr maniscalco::constexpr_string<N>::operator std::string_view const
(
) const noexcept
{
    return value_;
}


//=============================================================================
static constexpr auto operator <=>
(
    maniscalco::constexpr_string_concept auto const & first,
    maniscalco::constexpr_string_concept auto const & second
) noexcept
{
    return (std::string_view(first) <=> std::string_view(second));
}


//=============================================================================
static constexpr auto operator ==
(
    maniscalco::constexpr_string_concept auto const & first,
    maniscalco::constexpr_string_concept auto const & second
) noexcept
{
    return (std::string_view(first) == std::string_view(second));
}