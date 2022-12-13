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

#include "ProcessTerminationImpl.hh"

namespace Eagle::Core {
    ProcessTerminationExecutor::ProcessTerminationExecutor(bool shouldExit)
        : impl{std::make_unique<ProcessTerminationExecutorImpl>(shouldExit)}
    {}

    ProcessTerminationExecutor::ProcessTerminationExecutor(const std::vector<std::shared_ptr<IProcessTerminationTaskHandler>>&& terminationTasks, bool shouldExit)
        : impl{std::make_unique<ProcessTerminationExecutorImpl>(std::move(terminationTasks), shouldExit)}
    {}

    ProcessTerminationExecutor::ProcessTerminationExecutor(ProcessTerminationExecutor&&) = default;
    ProcessTerminationExecutor& ProcessTerminationExecutor::operator=(ProcessTerminationExecutor&&) = default;

    void ProcessTerminationExecutor::registerTerminationTask(std::shared_ptr<IProcessTerminationTaskHandler> handler) {
        if(this->impl)
            this->impl->handlers.push_back(handler);
    }

    ProcessTerminationExecutor::~ProcessTerminationExecutor() {
        if(this->impl and this->impl->_shouldExit)
            this->impl->exitProcess();
    }
}