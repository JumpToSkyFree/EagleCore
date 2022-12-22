/**
 * MIT License
 *
 * Copyright (c) 2022 JumpToSkyFree
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Posix/TimePosix.hh"

namespace Eagle::Core {
    inline const char* DaysStringsCapital[] = {
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday",
        "Sunday"
    };

    inline const char* DaysStringsLowercase[] = {
        "monday",
        "tuesday",
        "wednesday",
        "thursday",
        "friday",
        "saturday",
        "sunday"
    };

    inline const char* DaysStringsUppercase[] = {
        "MONDAY",
        "TUESDAY",
        "WEDNESDAY",
        "THURSDAY",
        "FRIDAY",
        "SATURDAY",
        "SUNDAY"
    };

    inline const char* MonthsStringsCapital[] = {
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    inline const char* MonthsStringsLowercase[] = {
        "january",
        "february",
        "march",
        "april",
        "may",
        "june",
        "july",
        "august",
        "september",
        "october",
        "november",
        "december"
    };

    inline const char* MonthsStringsUppercase[] = {
        "JANUARY",
        "FEBRARY",
        "MARCH",
        "APRIL",
        "MAY",
        "JUNE",
        "JULY",
        "AUGUST",
        "SEPTEMBER",
        "OCTOBER",
        "NOVEMBER",
        "DECEMBER"
    };

    ITime::~ITime() noexcept = default;

    std::string ITime::getDayAsStringCapital(std::uint32_t day) {
        if(day < 7)
            return {DaysStringsCapital[day]};
        return {};
    }

    std::string ITime::getDayAsStringLowercase(std::uint32_t day) {
        if(day < 7)
            return {DaysStringsLowercase[day]};
        return {};
    }

    std::string ITime::getDayAsStringUppercase(std::uint32_t day) {
        if(day < 7)
            return {DaysStringsUppercase[day]};
        return {};
    }

    std::string ITime::getMonthAsStringCapital(std::uint32_t month) {
        if(month < 12)
            return {MonthsStringsCapital[month]};
        return {};
    }

    std::string ITime::getMonthAsStringLowercase(std::uint32_t month) {
        if(month < 12)
            return {MonthsStringsLowercase[month]};
        return {};
    }

    std::string ITime::getMonthAsStringUppercase(std::uint32_t month) {
        if(month < 12)
            return {MonthsStringsUppercase[month]};
        return {};
    }

    GMTime::GMTime()
        : impl{std::make_unique<GMTime::GMTimeImpl>()}
    {}

    GMTime::GMTime(GMTime&&) noexcept = default;
    GMTime& GMTime::operator=(GMTime&&) = default;
    GMTime::~GMTime() noexcept = default;

    void GMTime::updateTime() {
        this->impl->update();
    }

    std::uint32_t GMTime::second() const {
        return this->impl->_gtime.tm_sec;
    }

    std::uint32_t GMTime::minute() const {
        return this->impl->_gtime.tm_min;
    }
    std::uint32_t GMTime::hour() const {
        return this->impl->_gtime.tm_hour;
    }

    std::uint32_t GMTime::day() const {
        return this->impl->_gtime.tm_mday;
    }

    std::uint32_t GMTime::month() const {
        return this->impl->_gtime.tm_mon;
    }

    std::uint32_t GMTime::dayOfWeek() const {
        return this->impl->_gtime.tm_wday;
    }

    std::uint32_t GMTime::dayOfYear() const {
        return this->impl->_gtime.tm_yday;
    }

    LocalTime::LocalTime()
        : impl{std::make_unique<LocalTime::LocalTimeImpl>()}
    {}

    LocalTime::LocalTime(LocalTime&&) noexcept = default;
    LocalTime& LocalTime::operator=(LocalTime&&) = default;
    LocalTime::~LocalTime() noexcept = default;

    void LocalTime::updateTime() {
        return this->impl->update();
    }


    std::uint32_t LocalTime::second() const {
        return this->impl->_ltime.tm_sec;
    }

    std::uint32_t LocalTime::minute() const {
        return this->impl->_ltime.tm_min;
    }
    std::uint32_t LocalTime::hour() const {
        return this->impl->_ltime.tm_hour;
    }

    std::uint32_t LocalTime::day() const {
        return this->impl->_ltime.tm_mday;
    }

    std::uint32_t LocalTime::month() const {
        return this->impl->_ltime.tm_mon;
    }

    std::uint32_t LocalTime::dayOfWeek() const {
        return this->impl->_ltime.tm_wday;
    }

    std::uint32_t LocalTime::dayOfYear() const {
        return this->impl->_ltime.tm_yday;
    }
}
