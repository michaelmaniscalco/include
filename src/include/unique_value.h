#pragma once

#include <limits>
#include <concepts>
#include <cstdint>
#include <atomic>


namespace maniscalco
{

    template <typename T0, std::integral T1 = std::uint32_t>
    class unique_value
    {
    public:

        using tag_type = T0;
        using value_type = T1;

        unique_value() = default;

        unique_value(unique_value const &) = default;

        unique_value & operator = (unique_value const &) = default;

        unique_value(unique_value &&) = default;

        unique_value & operator = (unique_value &&) = default;

        value_type get_id() const{return id_;}

    protected:

        value_type id_{next_++};

    private:

        static std::atomic<value_type> next_;
    };

    template <typename T0, std::integral T1> std::atomic<T1> unique_value<T0, T1>::next_{std::numeric_limits<T1>::min()};

} // namespace maniscalco
