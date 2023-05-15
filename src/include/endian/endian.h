#pragma once

#include <bit>


namespace maniscalco
{
    
    template <typename, std::endian> class endian;

} // namespace maniscalco


#include "./byte_swap.h"
#include "./endian_swap.h"

#include <concepts>
#include <type_traits>
#include <string>
#include <ostream>


namespace maniscalco
{

    //==============================================================================
    template <typename data_type, std::endian endian_type>
    class endian
    {
    public:

        using underlying_type = data_type;
        static auto constexpr type = endian_type;

        template <typename, std::endian> friend class endian;

        endian();

        endian
        (
            endian const &
        );

        endian
        (
            endian &&
        );

        endian
        (
            underlying_type const &
        );

        endian & operator =
        (
            endian const &
        );

        endian & operator =
        (
            endian &&
        );

        endian & operator =
        (
            underlying_type const &
        );

        operator underlying_type() const;

        underlying_type get() const;

        auto operator <=> 
        (
            endian const &
        ) const;

        auto operator <=> 
        (
            underlying_type
        ) const;

    private:

        underlying_type  value_;
    }; // class endian


    template <typename data_type> using big_endian = endian<data_type, std::endian::big>;
    template <typename data_type> using little_endian = endian<data_type, std::endian::little>;
    template <typename data_type> using network_order = endian<data_type, std::endian::big>;
    template <typename data_type> using host_order = endian<data_type, std::endian::native>;

    template <typename T>
    concept endian_concept = std::is_same_v<T, endian<typename T::underlying_type, T::type>>;


    template <endian_concept T>
    static std::string to_string
    (
        T const & source
    )
    {
        return to_string(source.get());
    }

} // namespace maniscalco


//==============================================================================
template <typename data_type, std::endian endian_type>
maniscalco::endian<data_type, endian_type>::endian
(
):
    value_()
{
}


//==============================================================================
template <typename data_type, std::endian endian_type>
maniscalco::endian<data_type, endian_type>::endian
(
    endian && input
):
    value_(input.value_)
{
}


//==============================================================================
template <typename data_type, std::endian endian_type>
maniscalco::endian<data_type, endian_type>::endian
(
    endian const & input
):
    value_(input.value_)
{
}


//==============================================================================
template <typename data_type, std::endian endian_type>
maniscalco::endian<data_type, endian_type>::endian
(
    data_type const & input
):
    value_(endian_swap<std::endian::native, endian_type>(input))
{
}


//==============================================================================
template <typename data_type, std::endian endian_type>
auto maniscalco::endian<data_type, endian_type>::operator =
(
    endian const & input
) -> endian &
{
    value_ = input.value_;
    return *this;
}


//==============================================================================
template <typename data_type, std::endian endian_type>
auto maniscalco::endian<data_type, endian_type>::operator =
(
    endian && input
) -> endian &
{
    value_ = input.value_;
    return *this;
}


//==============================================================================
template <typename data_type, std::endian endian_type>
auto maniscalco::endian<data_type, endian_type>::operator =
(
    data_type const & input
) -> endian &
{
    value_ = endian_swap<std::endian::native, endian_type>(input);
    return *this;
}


//==============================================================================
template <typename data_type, std::endian endian_type>
maniscalco::endian<data_type, endian_type>::operator underlying_type
(
) const
{
    return endian_swap<endian_type, std::endian::native>(value_);
}


//==============================================================================
template <typename data_type, std::endian endian_type>
auto maniscalco::endian<data_type, endian_type>::get
(
) const -> underlying_type
{
    return endian_swap<endian_type, std::endian::native>(value_);
}


//=============================================================================
template <maniscalco::endian_concept T>
static std::ostream & operator <<
(
    std::ostream & stream,
    T const & source
)
{
    return stream << source.get();
}


//=============================================================================
template <maniscalco::endian_concept T>
auto maniscalco::endian<data_type, endian_type>::operator <=> 
(
    endian const & other
) const
{
    return (get() <=> other.get());
}


//=============================================================================
template <maniscalco::endian_concept T>
auto maniscalco::endian<data_type, endian_type>::operator <=> 
(
    underlying_type other
) const
{
    return (get() <=> other);
}
