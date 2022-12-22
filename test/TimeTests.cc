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

#include <EagleCore/Time.hh>
#include <gtest/gtest.h>
#include <memory>

using namespace Eagle::Core;

TEST(GMTime, testTime) {
    std::unique_ptr<GMTime> ctime = std::make_unique<GMTime>();

    ASSERT_EQ(ctime->dayOfYear(), 355); // Sun 22 Dec
    ASSERT_EQ(ctime->month() + 1, 12); // Dec
}

TEST(LocalTime, testTime) {
    std::unique_ptr<LocalTime> ltime = std::make_unique<LocalTime>();

    ASSERT_EQ(ltime->dayOfYear(), 355); // Sun 22 Dec
    ASSERT_EQ(ltime->month() + 1, 12); // Dec
}

TEST(GMTime, testTimeDayString) {
    std::unique_ptr<GMTime> ctime = std::make_unique<GMTime>();

    ASSERT_STREQ(ITime::getDayAsStringCapital(ctime->dayOfWeek()-1).c_str(), "Thursday");
    ASSERT_STREQ(ITime::getDayAsStringUppercase(ctime->dayOfWeek()-1).c_str(), "THURSDAY");
    ASSERT_STREQ(ITime::getDayAsStringLowercase(ctime->dayOfWeek()-1).c_str(), "thursday");
}

TEST(GMTime, testTimeMonthString) {
    std::unique_ptr<GMTime> ctime = std::make_unique<GMTime>();

    ASSERT_STREQ(ITime::getMonthAsStringCapital(ctime->month()).c_str(), "December");
    ASSERT_STREQ(ITime::getMonthAsStringUppercase(ctime->month()).c_str(), "DECEMBER");
    ASSERT_STREQ(ITime::getMonthAsStringLowercase(ctime->month()).c_str(), "december");
}
