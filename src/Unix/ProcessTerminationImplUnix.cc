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

#include "../ProcessTerminationImpl.hh"
#include <algorithm>
#include <memory>
#include <sys/signal.h>

namespace Eagle::Core {
    struct ProcessTerminationExecutor::ProcessTerminationExecutorPlatform {
        inline static ProcessTerminationExecutorImpl* self;
        ProcessTerminationExecutorPlatform(ProcessTerminationExecutorImpl* _self) noexcept
        {
            // Storing an instance of the private implementation as a static member, since
            // a static function that is passed to the signal function
            // do not have access to public members (this pointer is not passed) of the private implementation.
            self = _self;
        }

        ProcessTerminationExecutorPlatform(const ProcessTerminationExecutorPlatform&) = delete;
        ProcessTerminationExecutorPlatform(ProcessTerminationExecutorPlatform&&) = delete;
        ProcessTerminationExecutorPlatform& operator=(const ProcessTerminationExecutorPlatform&) = delete;
        ProcessTerminationExecutorPlatform& operator=(ProcessTerminationExecutorPlatform&&) = delete;

        void registerSignal() noexcept {
            // handle SIGTERM, SIGINT, SIGQUIT with ProcessTerminationExecutorPlatform::handleSignal
            // static function member.
            ::signal(SIGTERM, ProcessTerminationExecutorPlatform::handleSignal);
            ::signal(SIGINT, ProcessTerminationExecutorPlatform::handleSignal);
            ::signal(SIGQUIT, ProcessTerminationExecutorPlatform::handleSignal);
        }

        static void handleSignal(int signal) {
            if(signal == SIGTERM or signal == SIGINT or signal == SIGQUIT) {
                // Execute the termination signal handlers.
                if(self)
                    self->executeTerminationHandlers();
            }

        }
    };

    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::ProcessTerminationExecutorImpl(bool shouldExit)
        : platform{std::make_unique<ProcessTerminationExecutorPlatform>(this)}, _shouldExit{shouldExit}
    {
        platform->registerSignal();
    }

    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::~ProcessTerminationExecutorImpl() = default;

    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::ProcessTerminationExecutorImpl(const std::vector<std::shared_ptr<IProcessTerminationTaskHandler>>&& handlers, bool shouldExit)
        : handlers{std::move(handlers)}, platform{std::make_unique<ProcessTerminationExecutorPlatform>(this)}, _shouldExit{shouldExit}
    {
        platform->registerSignal();
    }

    void ProcessTerminationExecutor::ProcessTerminationExecutorImpl::executeTerminationHandlers() {
        std::for_each(handlers.begin(), handlers.end(), [](std::shared_ptr<IProcessTerminationTaskHandler>& handler) {
            // If the termination task is executed successfully
            if(handler->executeTerminationTask()) {
                // execute a success callback and pass the task handler.
                handler->terminationTaskSuccess(handler);
                } else {
                // or execute a failure callback and pass the task handler.
                handler->terminationTaskFail(handler);
            }
        });
    }

    void ProcessTerminationExecutor::ProcessTerminationExecutorImpl::exitProcess() {
        // after finishing the execution of all the tasks the process can exit.
        ::exit(EXIT_SUCCESS);
    }
}
