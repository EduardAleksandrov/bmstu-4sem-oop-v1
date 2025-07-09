# include <iostream>
# include <type_traits>
# include <tuple>

using namespace std;

namespace my
{
    const struct p_1_ { static const unsigned index = 0; } _1_;
    const struct p_2_ { static const unsigned index = 1; } _2_;
    const struct p_3_ { static const unsigned index = 2; } _3_;

    template <typename T>
    concept PlaceHolder = is_same_v<T, p_1_> || is_same_v<T, p_2_> || is_same_v<T, p_3_>;

    template <typename T>
    concept NotPlaceHolder = !PlaceHolder<T>;

    template <PlaceHolder BindArg, typename CallArgTuple>
    auto get_arg(BindArg, CallArgTuple&& call_args)
    {
        return std::get<BindArg::index>(forward<CallArgTuple>(call_args));
    }

    template <NotPlaceHolder BindArg, typename CallArgTuple>
    auto get_arg(BindArg arg, CallArgTuple&&)
    {
        return arg;
    }

    template <typename Func, typename... BindArgs>
    class binder
    {
    private:
        Func func;
        tuple<BindArgs...> bind_args;

    public:
        binder(const Func& f, BindArgs&& ...bindArgs)
            : func( f ), bind_args{ forward<BindArgs>(bindArgs)... }
        {}

        template <typename CallArgTuple, size_t... Indexes>
        auto call(std::index_sequence<Indexes...>, CallArgTuple&& call_args)
        {
            return func(
                get_arg( std::get<Indexes>(bind_args), forward<CallArgTuple>(call_args) )...
            );
        }

        template <typename... CallArgs>
        auto operator ()(CallArgs&& ...call_args)
        {
            return call(
                std::make_index_sequence<sizeof...(BindArgs)>(),
                std::make_tuple(forward<CallArgs>(call_args)...)
            );
        }
    };

    template <typename Func, typename... BindArgs>
    binder<Func, BindArgs...> bind(Func func, BindArgs&& ...bind_args)
    {
        return { func, forward<BindArgs>(bind_args)... };
    }
}

void foo(int a, int b)
{
    std::cout << a << " " << b << std::endl;
}

int main()
{
    auto f1 = my::bind(foo, 5, my::_1_);
    f1(8);

    auto f2 = my::bind(foo, my::_2_, my::_1_);
    f2(5, 8);

    auto f3 = my::bind(foo, 5, 8);
    f3();
}
