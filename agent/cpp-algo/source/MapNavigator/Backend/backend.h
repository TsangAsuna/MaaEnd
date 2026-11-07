#pragma once

#include <string>

#include <MaaFramework/MaaAPI.h>

#include "Adb/adb_input_backend.h"
#include "Desktop/desktop_input_backend.h"
#include "backend_types.h"

namespace mapnavigator
{

struct InputBackend
{
    BackendKind kind = BackendKind::Desktop;
    MaaController* ctrl = nullptr;
    std::string controller_type;
    std::string unsupported_reason;
    double default_turn_units_per_degree = 0.0;
    double default_pitch_units_per_degree = 0.0;
    backend::desktop::DesktopBackend desktop;
    backend::adb::AdbBackend adb;
};

InputBackend OpenInputBackend(MaaController* ctrl);
void CloseInputBackend(InputBackend* backend);

bool UsesTouchBackend(const InputBackend& backend);
bool IsInputBackendSupported(const InputBackend& backend);
SteeringTransportProfile SteeringProfileOf(const InputBackend& backend);

void SetMovementStateSync(InputBackend* backend, MovementState state, int delay_millis);
void TriggerJumpSync(InputBackend* backend, int hold_millis);
void TriggerInteractSync(InputBackend* backend, int hold_millis);
void PulseForwardSync(InputBackend* backend, int hold_millis);
void TriggerSprintSync(InputBackend* backend);
void ToggleWalkModeSync(InputBackend* backend);
void ResetForwardWalkSync(InputBackend* backend, int release_millis);
void ClickMouseLeftSync(InputBackend* backend);
void TriggerZiplineLaunchSync(InputBackend* backend);
void TriggerZiplineDismountSync(InputBackend* backend, int hold_millis);
bool SendViewDeltaSync(const InputBackend& backend, int dx, int dy);

} // namespace mapnavigator
