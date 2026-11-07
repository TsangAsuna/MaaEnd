#include <MaaUtils/Logger.h>

#include "../Backend/backend.h"
#include "../control/motion_controller.h"
#include "../navi_config.h"
#include "../navi_time.h"
#include "action_executor.h"

namespace mapnavigator
{

void ExecuteSprint(MotionController* motion_controller)
{
    if (motion_controller->triggerSprint()) {
        LogInfo << "Action: SPRINT triggered.";
    }
    else {
        LogInfo << "Action: SPRINT skipped.";
    }
}

void ExecuteJump(InputBackend* input_backend, MotionController* motion_controller)
{
    motion_controller->setForwardState(false);
    TriggerJumpSync(input_backend, kActionJumpHoldMs);
    LogInfo << "Action: JUMP triggered.";
    SleepFor(kActionJumpSettleMs);
}

void ExecuteInteract(InputBackend* input_backend, MotionController* motion_controller)
{
    motion_controller->setForwardState(false);
    for (int i = 0; i < kActionInteractAttempts; ++i) {
        TriggerInteractSync(input_backend, kActionInteractHoldMs);
    }
    LogInfo << "Action: INTERACT completed.";
}

void ExecuteFight(InputBackend* input_backend, MotionController* motion_controller)
{
    motion_controller->setForwardState(false);
    ClickMouseLeftSync(input_backend);
    LogInfo << "Action: FIGHT triggered.";
}

} // namespace mapnavigator
