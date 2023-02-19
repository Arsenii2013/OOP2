#ifndef VARIANT_VARIANT_HPP
#define VARIANT_VARIANT_HPP

#include <functional>

inline constexpr size_t Variant_npos = -1;
template<typename T>
struct In_place_type_t final{};

template<std::size_t n>
struct In_place_index_t final{};

template<typename T>
constexpr In_place_type_t<T> In_place_type{};

template<std::size_t n>
constexpr In_place_index_t<n> In_place_index{};

namespace {
    template<typename ... Types>
    struct n_by_type_t;

    template<typename T, typename First,  typename ... Other>
    struct n_by_type_t<T, First, Other...>{
        static constexpr std::size_t n = n_by_type_t<T, Other...>::n + 1;
    };

    template<typename T,  typename ... Other>
    struct n_by_type_t<T, T, Other...>{
        static constexpr std::size_t n = 0;
    };

    template<typename T>
    struct n_by_type_t<T>{
        static constexpr std::size_t n = Variant_npos;
    };

    template< typename ... Types>
    constexpr std::size_t n_by_type_v = n_by_type_t<Types...>::n;

    template<typename ... Unions>
    union Variadic_union;

    template<typename T, typename ... Other>
    union Variadic_union<T, Other...> {
        T head;
        Variadic_union<Other...> base;

        Variadic_union() : base() {}

        template<std::size_t n, typename... Args>
        Variadic_union(In_place_index_t<n>, Args &&... __args)
                : base(In_place_index<n - 1>, std::forward<Args>(__args)...) {}

        template<typename... Args>
        Variadic_union(In_place_index_t<0>, Args &&... __args)
                : head(std::forward<Args>(__args)...) {}

        void destroy(std::size_t n){
            if(n == 0){
                head.~T();
            }else {
                base.destroy(n - 1);
            }
        }

        ~Variadic_union(){}
    };

    template<>
    union Variadic_union<> {
        void destroy(std::size_t n){}
    };


    template<std::size_t n, typename Union>
    auto& get_n(Union&& u){
        if constexpr (n == 0){
            return u.head;
        }else {
            return get_n<n - 1>(u.base);
        }
    }
}

template<typename ... Variants> class Variant{
private:
    using Union_t = Variadic_union<Variants...>;
    Union_t u;
    std::size_t active_index = Variant_npos;

    template<std::size_t n, typename ... _Variants>
    friend decltype(auto) Get(Variant<_Variants...> &v);

    template<typename T, typename ... _Variants>
    friend decltype(auto) Get(Variant<_Variants...> &v);
public:
    Variant() = default;
    Variant(const Variant& __rhs) = default;
    Variant(Variant&&) = default;
    Variant& operator=(const Variant&) = default;
    Variant& operator=(Variant&&) = default;
    ~Variant() = default;

    template<typename T>
    Variant(T&& t){
        //static_assert(n_by_type_v<T, Variants...> == 1000);
        active_index = n_by_type_v<T, Variants...>;
        new(&u) Union_t(In_place_index<n_by_type_v<T, Variants...>>, t);
    }

    template<std::size_t n, typename ... Args>
    Variant(In_place_index_t<n>, Args&&... args ){
        active_index = n;
        new(&u) Union_t(In_place_index<n>, args...);
    }

    template<typename T, typename ... Args>
    Variant(In_place_type_t<T>, Args&&... args ){
        active_index = n_by_type_v<T, Variants...>;
        new(&u) Union_t(In_place_index<n_by_type_v<T, Variants...>>, args...);
    }

    template<typename T>
    Variant& operator=(T&& t){
        if (active_index != Variant_npos) {
            u.destroy(active_index);
        }
        active_index = n_by_type_v<T, Variants...>;
        get_n<n_by_type_v<T, Variants...>>(u) = std::forward<T>(t);
        return *this;
    }

    template <std::size_t n, class... Args>
    decltype(auto) emplace( Args&&... args ){
        if (active_index != Variant_npos) {
            u.destroy(active_index);
        }
        active_index = n;
        new(&get_n<n>(u)) std::remove_reference_t<decltype(get_n<n>(u))>( args...);// type_by_n
        return get_n<n>(u);
    }

    template <class T, class... Args>
    T& emplace(Args&&... args){
        return emplace<n_by_type_v<T, Variants...>>(args...);
    }

    constexpr size_t index() const noexcept
    {
        return active_index;
    }


    bool operator==(const Variant& v){
        return index() == v.index() && Get<v.index()>(*this) == Get<v.index()>(v);
    }

    //TODO valuless_by_exception
    //TODO initialaizer_lists
    //TODO swap
};

template<std::size_t n, typename ... Variants>
decltype(auto) Get(Variant<Variants...> &v) {
    return get_n<n>(v.u);
}

template<typename T, typename ... Variants>
decltype(auto) Get(Variant<Variants...> &v) {
    return get_n<n_by_type_v<T, Variants...>>(v.u);
}

/*
template <typename Visitor, typename ... Variants>
decltype(auto) Visit( Visitor&& vis, Variants&&... vars){
    std::invoke(std::forward<Visitor>(vis), std::get<is>(std::forward<VariantBases>(vars))...)
    std::invoke(std::forward<Visitor>(vis),std::get<is>(std::forward<Variant>(v)))
}*/

#endif //VARIANT_VARIANT_HPP
