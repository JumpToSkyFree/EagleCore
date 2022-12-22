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

#ifndef EALGE_CORE_TIME_HH
#define EALGE_CORE_TIME_HH

#include <memory>
#include <string>

namespace Eagle::Core {
    class ITime {
    public:
        virtual ~ITime() noexcept;

        virtual void updateTime() = 0;

        virtual std::uint32_t second() const = 0;
        virtual std::uint32_t minute() const = 0;
        virtual std::uint32_t hour() const = 0;
        virtual std::uint32_t day() const = 0;
        virtual std::uint32_t month() const = 0;
        virtual std::uint32_t dayOfWeek() const = 0;
        virtual std::uint32_t dayOfYear() const = 0;

        static std::string getDayAsStringCapital(std::uint32_t day);
        static std::string getDayAsStringLowercase(std::uint32_t day);
        static std::string getDayAsStringUppercase(std::uint32_t day);

        static std::string getMonthAsStringCapital(std::uint32_t month);
        static std::string getMonthAsStringLowercase(std::uint32_t month);
        static std::string getMonthAsStringUppercase(std::uint32_t month);
    };


    class GMTime : public ITime {
        struct GMTimeImpl;
        std::unique_ptr<GMTimeImpl> impl;

    public:

        ~GMTime() noexcept;
        GMTime(const GMTime&) = delete;
        GMTime(GMTime&&) noexcept;
        GMTime& operator=(const GMTime&) = delete;
        GMTime& operator=(GMTime&&);

    public:
        GMTime();

        void updateTime();

        virtual std::uint32_t second() const;
        virtual std::uint32_t minute() const;
        virtual std::uint32_t hour() const;
        virtual std::uint32_t day() const;
        virtual std::uint32_t month() const;
        virtual std::uint32_t dayOfWeek() const;
        virtual std::uint32_t dayOfYear() const;

    };


    class LocalTime : public ITime {
        struct LocalTimeImpl;
        std::unique_ptr<LocalTimeImpl> impl;

    public:
        ~LocalTime() noexcept;
        LocalTime(const LocalTime&) = delete;
        LocalTime(LocalTime&&) noexcept;
        LocalTime& operator=(const LocalTime&) = delete;
        LocalTime& operator=(LocalTime&&);

    public:
        LocalTime();

        void updateTime();

        virtual std::uint32_t second() const;
        virtual std::uint32_t minute() const;
        virtual std::uint32_t hour() const;
        virtual std::uint32_t day() const;
        virtual std::uint32_t month() const;
        virtual std::uint32_t dayOfWeek() const;
        virtual std::uint32_t dayOfYear() const;
    };
}

#endif
