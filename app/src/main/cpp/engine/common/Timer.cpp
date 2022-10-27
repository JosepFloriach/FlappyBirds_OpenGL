//
// Created by Josep on 31/08/2018.
//

#include "Timer.h"
namespace utils
{
    Timer::Timer()
        : mTimeLastFrame (std::chrono::system_clock::now())
        , mTimeCurrentFrame(std::chrono::system_clock::now())
    {
    }

    void Timer::Start()
    {
        mStart = std::chrono::system_clock::now();
    }

    void Timer::Update()
    {
        mTimeLastFrame = mTimeCurrentFrame;
        mTimeCurrentFrame = std::chrono::system_clock::now();
    }

    double Timer::ElapsedTimeMillis() const
    {
        std::chrono::time_point<std::chrono::system_clock> Now = std::chrono::system_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(Now - mStart).count();
    }

    double Timer::ElapsedTimeSeconds() const
    {
        return ElapsedTimeMillis() / 1000.f;
    }

    double Timer::ElapsedTimeLastFrameMillis() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(mTimeCurrentFrame - mTimeLastFrame).count();
    }

    double Timer::ElapsedTimeLastFrameSeconds() const
    {
        return ElapsedTimeLastFrameMillis() / 1000.f;
    }
}