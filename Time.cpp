#include "Time.h"
#include <assert.h>
#include <iostream>
#include <iomanip>

Time::Time(const unsigned &hour, const unsigned &minute)
{
    assert(hour < 24);
    assert(minute < 60);

    this->hour = hour;
    this->minute = minute;
}

Time::Time(const unsigned &minutes) {
    this->hour = minutes / 60;
    this->minute = minutes % 60;
}

Time::Time()
{
    this->hour = 0;
    this->minute = 0;
}

bool Time::operator<(const Time &time) const
{
    return this->hour < time.hour || (this->hour == time.hour && this->minute < time.minute);
}

bool Time::operator>(const Time &time) const
{
    return this->hour > time.hour || (this->hour == time.hour && this->minute > time.minute);
}

bool Time::operator<=(const Time &time) const
{
    return *this == time || *this < time;
}

bool Time::operator>=(const Time &time) const
{
    return *this == time || *this > time;
}

bool Time::operator==(const Time &time) const
{
    return this->hour == time.hour && this->minute == time.minute;
}

bool Time::operator!=(const Time &time) const
{
    return this->hour != time.hour || this->minute != time.minute;
}

Time Time::operator+(unsigned minutes) const
{
    Time ret(*this);
    ret.minute += minutes;
    if (ret.minute >= 60)
    {
        ret.hour += ret.minute / 60;
        ret.minute %= 60;
        ret.hour %= 24;
    }
    return ret;
}

Time Time::operator-(unsigned minutes) const
{
    if (minutes >= this->hour * 60 + this->minute) //cant loop back to the day before. doesn't make sense on a day-by-day schedule.
        return Time();
    Time ret(*this);
    ret.hour -= minutes / 60;
    minutes %= 60;
    if (minutes > ret.minute)
    { //borrow an extra hour
        ret.hour--;
        ret.minute += 60;
    }
    ret.minute -= minutes;
    return ret;
}

Time Time::operator-(const Time &rhs) const
{
    Time ret(*this);
    return ret - rhs.getTotalMinutes();
}

unsigned Time::getHour() const
{
    return this->hour;
}

unsigned Time::getMinute() const
{
    return this->minute;
}

unsigned Time::getTotalMinutes() const
{
    return this->hour * 60 + this->minute;
}

std::string Time::to_string() const
{
    std::stringstream s;
    s << std::setw(2) << std::setfill('0') << this->hour << ":" << std::setw(2) << std::setfill('0') << this->minute;
    return s.str();
}

std::ostream &operator<<(std::ostream &os, const Time &time)
{
    os << time.to_string();
    return os;
}
