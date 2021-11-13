#pragma once
#include <ostream>

/**
 * @brief Time container with minutes and hours
 */
class Time
{
private:
    unsigned hour, minute;

public:
    /**
     * @brief Construct a new Time object
     *
     * @param hour
     * @param minute
     */
    Time(const unsigned &hour, const unsigned &minute);
    /**
     * @brief Construct a new Time object
     *
     * @param minutes - number of minutes
     */
    Time(const unsigned &minutes);
    /**
     * @brief Construct a new Time object
     *
     * \note sets the time to 0 hours and 0 minutes
     */
    Time();

    bool operator<(const Time &time) const;
    bool operator>(const Time &time) const;
    bool operator<=(const Time &time) const;
    bool operator>=(const Time &time) const;
    bool operator==(const Time &time) const;
    bool operator!=(const Time &time) const;

    /**
     * @brief Adds time to one timer constructing a new object and returning it
     *
     * @param minutes minutes to add
     * @return Time return time
     */
    Time operator+(unsigned minutes) const;

    /**
     * @brief Reduces time to one timer contructing a new object and returning it
     *
     * @param minutes minutes to reduce
     * @return Time return time
     */
    Time operator-(unsigned minutes) const;

    /**
     * @brief Subtracts 2 times
     *
     * @param rhs right hand side time
     * @return Time Subtraction between \p this and \p rhs
     */
    Time operator-(const Time &rhs) const;

    /**
     * @brief Get the Hour object
     *
     * @return unsigned hour
     */
    unsigned getHour() const;

    /**
     * @brief Get the Minute object
     *
     * @return unsigned minute
     */
    unsigned getMinute() const;

    /**
     * @brief Get the Total Minutes object
     *
     * @return unsigned hour * 60 + minutes
     */
    unsigned getTotalMinutes() const;

    /**
     * @brief Sends to an output stream the information of a Time object
     *
     * @param os output stream
     * @param time time object
     * @return std::ostream& return the output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const Time &time);

    /**
     * @brief Converts the time object to a formated string
     *
     * @return std::string formated string
     */
    std::string to_string() const;
};
