#include "LevelEditorLayerHook.hpp"
#include "../core/LevelOptimizer.hpp"
#include "../core/TaskScheduler.hpp"
#include "../core/ObjectPoolManager.hpp"

void PSMEditorLayer::update(float dt) {
    LevelEditorLayer::update(dt);
    TaskScheduler::shared()->update(dt);
}

void PSMEditorLayer::createObject(int id, CCPoint pos, bool p2) {
    LevelEditorLayer::createObject(id, pos, p2);
    if (this->isOptimizationEnabled()) {
        LevelOptimizer::sharedState()->runOptimizationPass(this);
    }
}

// Correct Destructor implementation
PSMEditorLayer::~PSMEditorLayer() {
    log::info("Co Engine: Cleaning up editor resources.");
    ObjectPoolManager::shared()->clearAllPools();
}

bool PSMEditorLayer::isOptimizationEnabled() {
    return Mod::get()->getSettingValue<bool>("auto-optimize");
}
