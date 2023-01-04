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

#include <EagleCore/ScopedPointer.hh>
#include <gtest/gtest.h>

struct ScopedPointerTestingType {
    int a;
    float b;

    virtual int getA() {
        return a;
    }

    virtual std::string sayHello() {
        return {"Hello world"};
    }
};

struct ScopedPointerTestingTypeDerived : public ScopedPointerTestingType {
    std::string sayHello() override {
        return {"Hello world from derived"};
    }
};

TEST(ScopedPointer, ScopedPointerInitialization) {
    Eagle::Core::ScopedPointer<int> ptr{new int()};
    ASSERT_NE(ptr.get(), nullptr);
}

TEST(ScopedPointer, ScopedPointerTestingTypeDerived) {
    Eagle::Core::ScopedPointer<ScopedPointerTestingTypeDerived> ptr{new ScopedPointerTestingTypeDerived()};
    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_STREQ(ptr->sayHello().c_str(), "Hello world from derived");
}

TEST(ScopedPointer, ScopedPointerTestingType) {
    Eagle::Core::ScopedPointer<ScopedPointerTestingType> ptr(
        new ScopedPointerTestingTypeDerived()
    );

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_STREQ(ptr->sayHello().c_str(), "Hello world from derived");
    ASSERT_EQ(ptr->getA(), 0);
}

TEST(ScopedPointer, ScopedPointerRelease) {
    Eagle::Core::ScopedPointer<ScopedPointerTestingType> ptr(
        new ScopedPointerTestingTypeDerived()
    );

    ASSERT_NE(ptr.get(), nullptr);
    ScopedPointerTestingType* data = ptr.release();
    ASSERT_EQ(ptr.get(), nullptr);
    delete data;
}