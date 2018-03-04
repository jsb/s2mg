#pragma once

#include <random>

namespace s2mg {

class random_number_generator
{
public:
    using engine = std::mt19937;
    using device = std::random_device;

public:
    //! Construct with seed from device entropy
    random_number_generator() :
        engine_{}
    {
        seed();
    }

    //! Construct with explicit seed value
    random_number_generator(engine::result_type _seed) :
        engine_{_seed}
    {
    }

    //! Seed with explicit value
    void seed(engine::result_type _seed)
    {
        engine_.seed(_seed);
    }

    //! Seed from device entropy
    void seed()
    {
        device d;
        engine_.seed(d());
    }

    //! Random integer from the interval [_a, _b]
    template<typename Int = int>
    Int integer(Int _a, Int _b)
    {
        std::uniform_int_distribution<Int> d{_a, _b};
        return d(engine_);
    }

    //! Random integer from the interval [0, _a)
    template<typename Int = int>
    Int integer(Int _a)
    {
        std::uniform_int_distribution<Int> d{Int(0), _a - Int(1)};
        return d(engine_);
    }

    //! Random real number from the interval [_a, _b]
    template<typename Real = double>
    Real real(Real _a, Real _b)
    {
        std::uniform_real_distribution<Real> d{_a, _b};
        return d(engine_);
    }

    //! Random real number from the interval [0, _a]
    template<typename Real = double>
    Real real(Real _a)
    {
        std::uniform_real_distribution<Real> d{Real(0), _a};
        return d(engine_);
    }

    //! Random real number from the interval [0, 1]
    template<typename Real = double>
    Real real()
    {
        std::uniform_real_distribution<Real> d{Real(0), Real(1)};
        return d(engine_);
    }

    //! Uniform choice from a list of arguments
    template<typename T>
    T choice(std::initializer_list<T> _items)
    {
        return *std::next(_items.begin(), integer(_items.size()));
    }

private:
    engine engine_;
};

#ifdef __APPLE__
// TODO: find proper workaround to make this thread-local
static random_number_generator random;
#else
static thread_local random_number_generator random;
#endif

}
