#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>


template<typename Func>
class Timer
{
    public:
        Timer( Func func, int times = 1);
        double duration() const;

    private:
        double m_duration;
};
//////////////////////////////////////////////////
//////////////////////////////////////////////////


template<typename Func>
Timer<Func>::Timer(Func func, int times)
{
    auto tstart = std::chrono::steady_clock::now();
    for( int i = 0; i < times; ++i)
    {
        func();
    }
    auto tend   = std::chrono::steady_clock::now();

    m_duration = std::chrono::duration<double,std::milli>( tend - tstart).count();
}

template<typename Func>
double Timer<Func>::duration() const 
{
    return m_duration;
}



#endif /* TIMER_HPP */