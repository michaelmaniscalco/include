#pragma once


namespace maniscalco
{

    struct non_movable
    {
        non_movable() noexcept = default;
        ~non_movable() noexcept = default;
        non_movable(non_movable &&) = delete;
        non_movable & operator = (non_movable &&) = delete;
    }; // struct non_movable

} // namespace maniscalco
