#pragma once

#include <cstdint>
#include <concepts>
#include <type_traits>
#include <tuple>


namespace maniscalco
{

    // TODO: (YAGNI) version_traits can be abstracted to support versioning methods other than major/minor/letter

    //=========================================================================
    template <std::size_t T0, std::size_t T1, char T2>
    struct version_traits
    {
        static auto constexpr major_version = T0;
        static auto constexpr minor_version = T1;
        static auto constexpr letter_version = T2;
    };

    template <typename T>
    concept version_traits_concept = std::is_same_v<T, version_traits<T::major_version, T::minor_version, T::letter_version>>;


    //=========================================================================
    struct version
    {
        version() = default;

        version(std::size_t, std::size_t, char);

        template <version_traits_concept T>
        version(T const &);

        version & operator = (version const &);

        template <version_traits_concept T>
        version & operator = (T const &);

        auto get() const;

        auto get_major() const;
        auto get_minor() const;
        auto get_letter() const;

        bool operator == (version const &) const;
        bool operator < (version const &) const;

        template <version_traits_concept T>
        bool operator == (T const &) const;

        template <version_traits_concept T>
        bool operator < (T const &) const;

    private:

        std::size_t major_;
        std::size_t minor_;
        char        letter_;
    };


    // TODO: to_string and from_string to read from configuration files

} // namespace maniscalco


//=============================================================================
inline maniscalco::version::version
(
    std::size_t major,
    std::size_t minor,
    char letter
):
    major_(major),
    minor_(minor),
    letter_(letter)
{
}


//=============================================================================
template <maniscalco::version_traits_concept T>
inline maniscalco::version::version
(
    // construct from compile time traits
    T const &
):
    major_(T::major_version),
    minor_(T::minor_version),
    letter_(T::letter_version)
{
}


//=============================================================================
inline auto maniscalco::version::operator = 
(
    version const & other
) -> version &
{
    major_ = other.major_;
    minor_ = other.minor_;
    letter_ = other.letter_;
    return *this;
}


//=============================================================================
template <maniscalco::version_traits_concept T>
inline auto maniscalco::version::operator = 
(
    T const &
) -> version &
{
    major_ = T::major_version;
    minor_ = T::minor_version;
    letter_ = T::letter_version;
    return *this;
}


//=============================================================================
inline auto maniscalco::version::get
(
    // return all fields as tuple
) const
{
    return std::tuple{major_, minor_, letter_};
}
        

//=============================================================================
inline auto maniscalco::version::get_major
(
) const
{
    return major_;
}


//=============================================================================
inline auto maniscalco::version::get_minor
(
) const
{
    return minor_;
}


//=============================================================================
inline auto maniscalco::version::get_letter
(
) const
{
    return letter_;
}


//=============================================================================
inline bool maniscalco::version::operator == 
(
    version const & other
) const
{
    return (get() == other.get());
}


//=============================================================================
inline bool maniscalco::version::operator < 
(
    version const & other
) const
{
    return (get() < other.get());
}


//=============================================================================
template <maniscalco::version_traits_concept T>
inline bool maniscalco::version::operator == 
(
    T const & versionTraits
) const
{
    return (*this == version(versionTraits));
}


//=============================================================================
template <maniscalco::version_traits_concept T>
inline bool maniscalco::version::operator < 
(
    T const & versionTraits
) const
{
    return (*this < version(versionTraits));
}
