#pragma once

namespace mapnavigator
{

class MotionController;
struct InputBackend;

void ExecuteSprint(MotionController* motion_controller);
void ExecuteJump(InputBackend* input_backend, MotionController* motion_controller);
void ExecuteInteract(InputBackend* input_backend, MotionController* motion_controller);
void ExecuteFight(InputBackend* input_backend, MotionController* motion_controller);

} // namespace mapnavigator
