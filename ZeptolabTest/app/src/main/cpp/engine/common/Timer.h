//
// Created by Josep on 31/08/2018.
//

#ifndef ZEPTOLABTEST_TIMER_H
#define ZEPTOLABTEST_TIMER_H

#include <chrono>
namespace utils
{
    class Timer
    {
    public:
        /**
         * Constructor
         */
        Timer();

        /**
        * Non-copyable, non-moveable class.
        */
        Timer(const Timer& aOther) = delete;
        Timer(Timer&& aOther) = delete;
        Timer& operator=(const Timer& aOther) = delete;
        Timer& operator=(Timer&& aOther) = delete;

        /**
         * Update the timer.
         */
        void Update();

        /**
         * Starts the timer.
         */
        void Start();

        /**
         * Stops the timer.
         */
        void Stop();

        /**
         * Gets the elapsed time since start, in seconds.
         * @return double
         */
        double ElapsedTimeSeconds() const;

        /**
         * Gets the elapsed time since start, in milliseconds.
         * @return
         */
        double ElapsedTimeMillis() const;

        /**
         * Gets the elapsed time since last frame, in seconds.
         * @return
         */
        double ElapsedTimeLastFrameSeconds() const;

        /**
         * Gets the elapsed time since last frame, in milliseconds.
         * @return
         */
        double ElapsedTimeLastFrameMillis() const;

    private:
        // Start time.
        std::chrono::time_point<std::chrono::system_clock> mStart;
        // Last frame time.
        std::chrono::time_point<std::chrono::system_clock> mTimeLastFrame;
        // Current frame time.
        std::chrono::time_point<std::chrono::system_clock> mTimeCurrentFrame;

    };
}
#endif //ZEPTOLABTEST_TIMER_H
