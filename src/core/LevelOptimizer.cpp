#include "LevelOptimizer.hpp"

LevelOptimizer* LevelOptimizer::sharedState() {
    static LevelOptimizer* instance = new LevelOptimizer();
    return instance;
}

void LevelOptimizer::runOptimizationPass(LevelEditorLayer* editor) {
    auto objects = editor->m_objects;
    if (!objects) return;

    m_lastRemovedCount = 0;

    // Iterate backwards to safely remove objects
    for (int i = objects->count() - 1; i >= 0; --i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        // 1. Cull objects out of bounds
        if (obj->getPositionX() < -1000.0f || obj->getPositionX() > 100000.0f) {
            editor->removeObject(obj, true);
            m_lastRemovedCount++;
            continue;
        }

        // 2. Remove identical duplicates (Z-fighting prevention)
        for (int j = i - 1; j >= 0; --j) {
            auto other = static_cast<GameObject*>(objects->objectAtIndex(j));
            if (obj->getPosition().equals(other->getPosition()) && obj->m_objectID == other->m_objectID) {
                editor->removeObject(obj, true);
                m_lastRemovedCount++;
                break;
            }
        }
    }
}

void LevelOptimizer::compileLDMPreset(LevelEditorLayer* editor) {
    auto objects = editor->m_objects;
    for (int i = 0; i < objects->count(); ++i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        // If object is decoration, force it into the LDM system
        if (isObjectDecorative(obj)) {
            obj->setHighDetail(false); // GD 2.2 native LDM toggle
        }
    }
}

int LevelOptimizer::calculateAreaDensity(LevelEditorLayer* editor, CCPoint center, float radius) {
    auto objects = editor->m_objects;
    int count = 0;
    for (int i = 0; i < objects->count(); ++i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        if (obj->getPosition().getDistance(center) < radius) {
            count++;
        }
    }
    return count;
}

void LevelOptimizer::purgeBrokenTriggers(LevelEditorLayer* editor) {
    auto objects = editor->m_objects;
    for (int i = objects->count() - 1; i >= 0; --i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        // Example: Triggers with invalid IDs (usually 0 or error states)
        if (obj->m_isTrigger && obj->m_objectID == 0) {
            editor->removeObject(obj, true);
        }
    }
}

bool LevelOptimizer::isObjectDecorative(GameObject* obj) {
    // Logic: IDs for glow, particles, or common decoration objects
    int id = obj->m_objectID;
    // Returns true if ID falls in "Decoration" ranges (example range)
    return (id > 1000 && id < 2000) || (id > 3000);
}
