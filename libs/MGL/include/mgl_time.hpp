#ifndef MGL_TIME_HPP
#define MGL_TIME_HPP

#include <chrono>
#include <array>

class MGL_Timing {
    public:
        MGL_Timing(int tick_rate = 64);
        void startFrameRenderTimer();
        void endFrameRenderTimer();
        bool computeNextLogic();
    private:
        const int tick_rate_;
        int tick_duration_microseconds_;
        std::chrono::steady_clock::time_point frame_beginning_;
        std::array<int, 10> last_10_frame_render_durations_ = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int circular_ptr_ = 0;
        const float average_denominator_ = 0.1f;
        int last_10_frame_render_duration_sum_;
        std::chrono::steady_clock::time_point logic_beginning_;
};

class MGL_SchedulerMs {
    public:
        MGL_SchedulerMs(int sheduler_length_ms);
        bool executeOnSchedule();
    private:
        std::chrono::steady_clock::time_point beginning_;
        int sheduler_length_ms_;
};

class MGL_Timer {
    public:
        void startOrRestartTimer();
        const std::array<int, 4> & elapsedTime();
    private:
        std::chrono::steady_clock::time_point beginning_;
        std::array<int, 4> elapsed_hour_minute_second_milli_;
};

#endif