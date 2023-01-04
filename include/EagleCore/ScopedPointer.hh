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

#include <utility>

namespace Eagle::Core {
    template <typename T>
    struct DefaultScopedPointerDeleter {
        using type = T;
        using pointer = T*;
        void operator()(pointer ptr) const noexcept {
            delete ptr;
        }
    };

    template <typename T, typename D = DefaultScopedPointerDeleter<T>>
    class ScopedPointer {
    public:
        using type = T;
        using pointer = T*;
        using deleterType = D;

    private:
        T* ptr{nullptr};
        deleterType deleter{D()};

        void reset() {
            if(ptr != nullptr) {
                deleter(ptr);
                this->ptr = nullptr;
            }
        }

    public:
        ScopedPointer() = default;

        ScopedPointer(pointer ptr) noexcept : ptr{ptr}  {}
        ScopedPointer(pointer ptr, D&& deleter) noexcept : ptr{ptr}, deleter(std::move(deleter)) {}

        template <typename U>
        ScopedPointer(U* ptr) noexcept
            : ptr{ptr}
        {}

        inline D getDeleter() const noexcept {
            return deleter;
        }

        ScopedPointer(const ScopedPointer&) = delete;
        ScopedPointer(ScopedPointer&&) = delete;
        ScopedPointer& operator=(ScopedPointer&&) = delete;
        ScopedPointer& operator=(const ScopedPointer&) = delete;

        ~ScopedPointer() {
            reset();
        }

        pointer get() const noexcept {
            return ptr;
        }

        pointer operator->() const noexcept {
            return ptr;
        }

        type& operator*() const noexcept {
            return *ptr;
        }

        [[nodiscard]] pointer release() noexcept {
            pointer ret = ptr;
            this->ptr = nullptr;
            return ret;
        }
    };
}