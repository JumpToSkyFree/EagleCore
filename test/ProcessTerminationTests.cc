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

#include <gtest/gtest.h>
#include <EagleCore/ProcessTermination.hh>
#include <memory>
#include <csignal>

using namespace Eagle::Core;

class ThreadsTerminationTask : public IProcessTerminationTaskHandler {
    bool _done{false};
public:
    virtual bool executeTerminationTask() {
        return true;
    }

    virtual void terminationTaskFail(std::shared_ptr<IProcessTerminationTaskHandler> handler) {}
    virtual void terminationTaskSuccess(std::shared_ptr<IProcessTerminationTaskHandler> handler) {
        _done = true;
    }
    inline bool done() const { return _done; }
};

TEST(ProcessTermination, ProcessTerminationExecutorNoSignalReceived) {
    ProcessTerminationExecutor executor(false);

    std::shared_ptr<ThreadsTerminationTask> task1 = std::make_shared<ThreadsTerminationTask>();
    std::shared_ptr<ThreadsTerminationTask> task2 = std::make_shared<ThreadsTerminationTask>();

    executor.registerTerminationTask(task1);
    executor.registerTerminationTask(task2);
    ASSERT_FALSE(task1->done());
    ASSERT_FALSE(task2->done());
}

TEST(ProcessTermination, ProcessTerminationExecutorSignalReceived) {
    ProcessTerminationExecutor executor(false);

    std::shared_ptr<ThreadsTerminationTask> task1 = std::make_shared<ThreadsTerminationTask>();
    std::shared_ptr<ThreadsTerminationTask> task2 = std::make_shared<ThreadsTerminationTask>();

    executor.registerTerminationTask(task1);
    executor.registerTerminationTask(task2);

    std::raise(SIGTERM);
    ASSERT_TRUE(task1->done());
    ASSERT_TRUE(task2->done());
}

TEST(ProcessTerminationVectorInitializer, ProcessTerminationExecutorSignalReceived) {
    std::vector<std::shared_ptr<IProcessTerminationTaskHandler>> v;

    std::shared_ptr<ThreadsTerminationTask> task1 = std::make_shared<ThreadsTerminationTask>();
    std::shared_ptr<ThreadsTerminationTask> task2 = std::make_shared<ThreadsTerminationTask>();

    v.push_back(task1);
    v.push_back(task2);

    ProcessTerminationExecutor executor(std::move(v), false);

    std::raise(SIGTERM);
    ASSERT_TRUE(task1->done());
    ASSERT_TRUE(task2->done());
}