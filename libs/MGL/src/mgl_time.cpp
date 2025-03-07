#include "../include/mgl_time.hpp"

MGL_Timing::MGL_Timing(int tick_rate) : tick_rate_(tick_rate) {
    tick_duration_microseconds_ = 1000000 / tick_rate_;
}

void MGL_Timing::startFrameRenderTimer() {
    frame_beginning_ = std::chrono::steady_clock::now();
}

void MGL_Timing::endFrameRenderTimer() {
    int new_duration = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - frame_beginning_)).count();
    int oldest_frame_duration = last_10_frame_render_durations_[circular_ptr_];
    last_10_frame_render_durations_[circular_ptr_] = new_duration;
    circular_ptr_ += 1;
    if (circular_ptr_ > 9) {circular_ptr_ = 0;}
    last_10_frame_render_duration_sum_ += new_duration;
    last_10_frame_render_duration_sum_ -= oldest_frame_duration;
}

bool MGL_Timing::computeNextLogic() {
    int duration = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - logic_beginning_)).count();
    int average_last_10_frame_render_microsecond_duration = (int)(last_10_frame_render_duration_sum_ * average_denominator_);
    if (tick_duration_microseconds_ > (duration + average_last_10_frame_render_microsecond_duration)) {return false;}
    logic_beginning_ = std::chrono::steady_clock::now();
    return true;
}



MGL_SchedulerMs::MGL_SchedulerMs(int sheduler_length_ms) : sheduler_length_ms_(sheduler_length_ms) {}

bool MGL_SchedulerMs::executeOnSchedule() {
    int duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginning_)).count();
    if (sheduler_length_ms_ > duration) {return false;}
    beginning_ = std::chrono::steady_clock::now();
    return true;
}



void MGL_Timer::startOrRestartTimer() {
    beginning_ = std::chrono::steady_clock::now();
}

const std::array<int, 4> & MGL_Timer::elapsedTime() {

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginning_);

    auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
    duration -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    duration -= seconds;

    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    elapsed_hour_minute_second_milli_[0] = hours.count();
    elapsed_hour_minute_second_milli_[1] = minutes.count();
    elapsed_hour_minute_second_milli_[2] = seconds.count();
    elapsed_hour_minute_second_milli_[3] = milliseconds.count();

    return elapsed_hour_minute_second_milli_;
}