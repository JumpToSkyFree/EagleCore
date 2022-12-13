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

#ifndef EALGE_CORE_PROCESS_TERMINATION_HH
#define EALGE_CORE_PROCESS_TERMINATION_HH

#include <memory>
#include <vector>

namespace Eagle::Core {
    class IProcessTerminationTaskHandler {
    public:
        virtual ~IProcessTerminationTaskHandler() = default;

        /**
         * Execute termination tasks, tasks responsible on doing anything after receiving a signal for the process
         * to stop.
         * 
         * @return Return true if termination tasks executed successfully otherwise false.
         */
        virtual bool executeTerminationTask() = 0;

        /**
         * The termination task failure callback.
         * 
         * @param handler The process termination task handler instance.
         */
        virtual void terminationTaskFail(std::shared_ptr<IProcessTerminationTaskHandler> handler) = 0;

        /**
         * The termination task success callback.
         * 
         * @param handler The process termination task handler instance.
         */
        virtual void terminationTaskSuccess(std::shared_ptr<IProcessTerminationTaskHandler> handler) = 0;
    };

    class ProcessTerminationExecutor {
    private:
        /**
         * The type of structure that contains the private implementation of ProcessTerminationExecutor.
         */
        struct ProcessTerminationExecutorImpl;
        std::unique_ptr<ProcessTerminationExecutorImpl> impl;

        /**
         * A type that handles platform specific defined properties for ProcessTerminationExecutor.
         */
        struct ProcessTerminationExecutorPlatform;

    public:
        ProcessTerminationExecutor(const ProcessTerminationExecutor&) = delete;
        ProcessTerminationExecutor(ProcessTerminationExecutor&&);
        ProcessTerminationExecutor& operator=(const ProcessTerminationExecutor&) = delete;
        ProcessTerminationExecutor& operator=(ProcessTerminationExecutor&&);

    public:
        ProcessTerminationExecutor(bool shouldExit = true);
        ProcessTerminationExecutor(const std::vector<std::shared_ptr<IProcessTerminationTaskHandler>>&& terminationHandlers, bool shouldExit = true);
        virtual ~ProcessTerminationExecutor();

        /**
         * Register a termination task when receiving a signal will be called to do the termination task.
         * 
         * @param handler The termination task handler.
         */
        virtual void registerTerminationTask(std::shared_ptr<IProcessTerminationTaskHandler> handler);
    };
}

#endif
