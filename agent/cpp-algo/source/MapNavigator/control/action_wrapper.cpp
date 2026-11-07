#include <MaaUtils/Logger.h>

#include "../Backend/backend.h"
#include "../sensing/sensitivity_observer.h"
#include "action_wrapper.h"

namespace mapnavigator
{

ActionWrapper::ActionWrapper(MaaContext* context)
    : backend_(OpenInputBackend(MaaTaskerGetController(MaaContextGetTasker(context))))
{
}

ActionWrapper::~ActionWrapper()
{
    CloseInputBackend(&backend_);
}

MaaController* ActionWrapper::getCtrl() const
{
    return backend_.ctrl;
}

const char* ActionWrapper::controllerType() const
{
    return backend_.controller_type.c_str();
}

bool ActionWrapper::usesTouchBackend() const
{
    return UsesTouchBackend(backend_);
}

bool ActionWrapper::isSupported() const
{
    return IsInputBackendSupported(backend_);
}

const char* ActionWrapper::unsupportedReason() const
{
    return backend_.unsupported_reason.c_str();
}

double ActionWrapper::defaultTurnUnitsPerDegree() const
{
    // 灵敏度校正系数只在这里和下面的俯仰处乘
    return backend_.default_turn_units_per_degree * sensitivity::TurnUnitsScale();
}

double ActionWrapper::defaultPitchUnitsPerDegree() const
{
    // 游戏视角灵敏度两轴共用, 偏航测出的倍率俯仰照乘
    return backend_.default_pitch_units_per_degree * sensitivity::TurnUnitsScale();
}

SteeringTransportProfile ActionWrapper::steeringProfile() const
{
    return SteeringProfileOf(backend_);
}

bool ActionWrapper::supportsSprint() const
{
    return true;
}

bool ActionWrapper::supportsWalkToggle() const
{
    return true;
}

void ActionWrapper::setMovementStateSync(MovementState state, int delay_millis)
{
    SetMovementStateSync(&backend_, state, delay_millis);
}

void ActionWrapper::triggerJumpSync(int hold_millis)
{
    TriggerJumpSync(&backend_, hold_millis);
}

void ActionWrapper::triggerInteractSync(int hold_millis)
{
    TriggerInteractSync(&backend_, hold_millis);
}

void ActionWrapper::pulseForwardSync(int hold_millis)
{
    PulseForwardSync(&backend_, hold_millis);
}

void ActionWrapper::triggerSprintSync()
{
    TriggerSprintSync(&backend_);
}

void ActionWrapper::toggleWalkModeSync()
{
    ToggleWalkModeSync(&backend_);
}

void ActionWrapper::resetForwardWalkSync(int release_millis)
{
    ResetForwardWalkSync(&backend_, release_millis);
}

void ActionWrapper::clickMouseLeftSync()
{
    ClickMouseLeftSync(&backend_);
}

void ActionWrapper::triggerZiplineLaunchSync()
{
    TriggerZiplineLaunchSync(&backend_);
}

void ActionWrapper::triggerZiplineDismountSync(int hold_millis)
{
    TriggerZiplineDismountSync(&backend_, hold_millis);
}

bool ActionWrapper::sendViewDeltaSync(int dx, int dy)
{
    const bool sent = SendViewDeltaSync(backend_, dx, dy);
    const double units_per_degree = defaultTurnUnitsPerDegree();
    if (sent && dx != 0 && units_per_degree > 0.0) {
        sensitivity::NoteTurnIssued(static_cast<double>(dx) / units_per_degree);
    }
    // 送失败的拖拽也可能已动了视角, 照样记一次
    if (dx != 0) {
        noteHeadingDisturbed();
    }
    return sent;
}

} // namespace mapnavigator
