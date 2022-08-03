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

        template <typename, std::endian>
        friend class endian;

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
            underlying_type
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
            underlying_type
        );

        operator underlying_type() const;

        underlying_type get() const;

    protected:

    private:

        underlying_type  value_;

    };

    template <typename data_type> using big_endian = endian<data_type, std::endian::big>;
    template <typename data_type> using little_endian = endian<data_type, std::endian::little>;
    template <typename data_type> using network_order = endian<data_type, std::endian::big>;
    template <typename data_type> using host_order = endian<data_type, std::endian::native>;

    // global operator overloads involving endian types
    template <typename input_type, typename data_type, std::endian endian_type> inline static bool operator < (input_type a, endian<data_type, endian_type> b){return (a < (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator < (endian<data_type, endian_type> a, data_type b){return ((data_type)a < b);}
    template <typename data_type, std::endian endian_type> inline static bool operator <= (data_type a, endian<data_type, endian_type> b){return (a <= (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator <= (endian<data_type, endian_type> a, data_type b){return ((data_type)a <= b);}
    template <typename data_type, std::endian endian_type> inline static bool operator == (data_type a, endian<data_type, endian_type> b){return (a == (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator == (endian<data_type, endian_type> a, data_type b){return ((data_type)a == b);}
    template <typename data_type, std::endian endian_type> inline static bool operator >= (data_type a, endian<data_type, endian_type> b){return (a >= (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator >= (endian<data_type, endian_type> a, data_type b){return ((data_type)a >= b);}
    template <typename data_type, std::endian endian_type> inline static bool operator > (data_type a, endian<data_type, endian_type> b){return (a > (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator > (endian<data_type, endian_type> a, data_type b){return ((data_type)a > b);}
    template <typename data_type, std::endian endian_type> inline static bool operator != (data_type a, endian<data_type, endian_type> b){return (a != (data_type)b);}
    template <typename data_type, std::endian endian_type> inline static bool operator != (endian<data_type, endian_type> a, data_type b){return ((data_type)a != b);}


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

}


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
    data_type input
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
    data_type input
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
