#include "walk_mode.h"

#include <MaaUtils/Logger.h>

#include "../Backend/backend.h"

namespace mapnavigator::walkmode
{

namespace
{
// 游戏的走路切换状态跨导航保留, 所以放在进程级
bool g_walking = false;
}

bool Engaged()
{
    return g_walking;
}

void NoteSprintTriggered()
{
    if (!g_walking) {
        return;
    }
    g_walking = false;
    LogInfo << "Walk mode cleared by sprint (the game leaves walking on its own).";
}

Toggle::Toggle(InputBackend* input_backend)
    : input_backend_(input_backend)
{
    if (g_walking) {
        LogWarn << "Walk mode belief survived the previous run; restoring jogging before navigating.";
        request(false);
    }
}

Toggle::~Toggle()
{
    request(false);
}

void Toggle::request(bool walk)
{
    if (walk == g_walking) {
        return;
    }
    if (input_backend_ == nullptr || !SupportsWalkToggle(*input_backend_)) {
        return;
    }

    ToggleWalkModeSync(input_backend_);
    g_walking = walk;
    LogInfo << (walk ? "Walk mode engaged (game walking speed)." : "Walk mode released (back to jogging).");
}

} // namespace mapnavigator::walkmode
