#include "../ProcessTerminationImpl.hh"
#include <algorithm>
#include <signal.h>

namespace Eagle::Core{
    struct ProcessTerminationExecutor::ProcessTerminationExecutorPlatform{
        inline static ProcessTerminationExecutorImpl* self;
        ProcessTerminationExecutorPlatform(ProcessTerminationExecutorImpl* impl){
            // Storing an instance of the private implementation as a static member, since
            // a static function that is passed to the signal function
            // do not have access to public members (this pointer is not passed) of the private implementation.
            self = impl;
        }
        ProcessTerminationExecutorPlatform(const ProcessTerminationExecutorPlatform&) = delete;
        ProcessTerminationExecutorPlatform(ProcessTerminationExecutorPlatform&&) = delete;
        ProcessTerminationExecutorPlatform& operator=(const ProcessTerminationExecutorPlatform&) = delete;
        ProcessTerminationExecutorPlatform& operator=(ProcessTerminationExecutorPlatform&&) = delete;
        
        void registerSignal() noexcept{
            // handle SIGTERM, SIGINT, SIGQUIT with ProcessTerminationExecutorPlatform::handleSignal
            // static function member.
            ::signal(SIGTERM, ProcessTerminationExecutorPlatform::handleSignal);
            ::signal(SIGINT, ProcessTerminationExecutorPlatform::handleSignal);
            ::signal(SIGABRT, ProcessTerminationExecutorPlatform::handleSignal);
        }
        static void handleSignal(int signal){
            if(signal == SIGTERM or signal == SIGINT or signal == SIGABRT) {
                // Execute the termination signal handlers.
                if(self)
                    self->executeTerminationHandlers();
            }
        }

    };
    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::ProcessTerminationExecutorImpl(bool shouldExit)
        :  _shouldExit{shouldExit}, platform{std::make_unique<ProcessTerminationExecutorPlatform>(this)}
    {
        platform->registerSignal();
    }

    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::~ProcessTerminationExecutorImpl() = default;

    ProcessTerminationExecutor::ProcessTerminationExecutorImpl::ProcessTerminationExecutorImpl(const std::vector<std::shared_ptr<IProcessTerminationTaskHandler>>&& handlers, bool shouldExit)
        : _shouldExit{shouldExit}, platform{std::make_unique<ProcessTerminationExecutorPlatform>(this)}, handlers{std::move(handlers)}
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
