#include "LevelEditorLayerHook.hpp"
#include "../core/LevelOptimizer.hpp"
#include "../core/TaskScheduler.hpp"
#include "../core/ObjectPoolManager.hpp"

void PSMEditorLayer::update(float dt) {
    LevelEditorLayer::update(dt);
    // Pulse the TaskScheduler to process pending procedural generation frames[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span)
    TaskScheduler::shared()->update(dt);
}

void PSMEditorLayer::createObject(int id, CCPoint pos, bool p2) {
    LevelEditorLayer::createObject(id, pos, p2);
    
    // Real-time optimization pass to maintain performance[span_6](start_span)[span_6](end_span)[span_7](start_span)[span_7](end_span)
    if (this->isOptimizationEnabled()) {
        LevelOptimizer::sharedState()->runOptimizationPass(this);
    }
}

void PSMEditorLayer::destructor() {
    log::info("Co Engine: Cleaning up editor resources.");
    ObjectPoolManager::shared()->clearAllPools(); // Prevent memory leaks[span_8](start_span)[span_8](end_span)
    LevelEditorLayer::destructor();
}

bool PSMEditorLayer::isOptimizationEnabled() {
    // Logic to fetch user preference from mod settings[span_9](start_span)[span_9](end_span)
    return Mod::get()->getSettingValue<bool>("auto-optimize");
}
