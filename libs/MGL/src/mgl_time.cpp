#include "../include/mgl_time.hpp"

MGL_Timing::MGL_Timing(int tick_rate) : tick_rate_(tick_rate) {
    tick_duration_microseconds_ = static_cast<int64_t>(1000000 / tick_rate_);
}

void MGL_Timing::startFrameRenderTimer() {
    frame_beginning_ = std::chrono::steady_clock::now();
}

void MGL_Timing::endFrameRenderTimer() {
    int64_t new_frame_duration = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - frame_beginning_)).count();
    if (new_frame_duration > largest_frame_duration_) {
        largest_frame_duration_ = new_frame_duration;
        largest_frame_life_counter_ = 0;
    }
    if (30 <= largest_frame_life_counter_) {
        largest_frame_duration_ = new_frame_duration;
        largest_frame_life_counter_ = 0;
    }
    largest_frame_life_counter_++;
}

bool MGL_Timing::computeNextLogic() {
    int64_t duration = (std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - logic_beginning_)).count();
    if (tick_duration_microseconds_ > (duration + largest_frame_duration_)) {return false;}
    logic_beginning_ = std::chrono::steady_clock::now();
    return true;
}



MGL_SchedulerMs::MGL_SchedulerMs(int64_t sheduler_length_ms) : sheduler_length_ms_(sheduler_length_ms) {}

bool MGL_SchedulerMs::executeOnSchedule() {
    int64_t duration = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - beginning_)).count();
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