//
// Created by marvd on 01.06.2021.
//

#ifndef FIBONACCI_MEMOIZE_H
#define FIBONACCI_MEMOIZE_H

#include <map>

enum class Cache : unsigned int {
    NO_RECLAIM, RECLAIM
};

template<typename Sig, Sig funcptr>
struct static_memoizer;

template<typename ReturnType, typename... Args>
std::function<ReturnType(Args...)>
memoize(ReturnType (*func)(Args...)) {
    auto cache = std::make_shared<std::map<std::tuple<Args...>, ReturnType>>();
    return ([=](Args... args) mutable {
        std::tuple<Args...> t(args...);
        if (cache->find(t) == cache->end())
            (*cache)[t] = func(args...);
        return (*cache)[t];
    });
}


template<typename F_ret, typename... F_args, F_ret (*func)(F_args...)>
struct static_memoizer<F_ret (*)(F_args...), func> {
    static
    std::function<F_ret(F_args...)> &
    get(Cache c = Cache::NO_RECLAIM) {
        static std::function<F_ret(F_args...)> mfunc(memoize(func));

        if (Cache::RECLAIM == c)
            mfunc = memoize(func);

        return mfunc;
    }
};


#define STATIC_MEMOIZER(func) static_memoizer<decltype(&func), &func>::get()

#endif //FIBONACCI_MEMOIZE_H
