#include "LevelOptimizer.hpp"

LevelOptimizer* LevelOptimizer::sharedState() {
    static LevelOptimizer* instance = new LevelOptimizer();
    return instance;
}

void LevelOptimizer::runOptimizationPass(LevelEditorLayer* editor) {
    auto objects = editor->getAllObjects();
    if (!objects) return;

    m_lastRemovedCount = 0;

    for (int i = objects->count() - 1; i >= 0; --i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        if (obj->getPositionX() < -1000.0f || obj->getPositionX() > 100000.0f) {
            editor->removeObject(obj, true);
            m_lastRemovedCount++;
            continue;
        }

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
    auto objects = editor->getAllObjects();
    for (int i = 0; i < objects->count(); ++i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        if (isObjectDecorative(obj)) {
            // FIX: Use m_lowDetailMode property instead of setObjectLowDetail()
            // This is the correct GD 2.2 API for marking objects as low detail
            obj->m_lowDetailMode = true;
        }
    }
}

int LevelOptimizer::calculateAreaDensity(LevelEditorLayer* editor, CCPoint center, float radius) {
    auto objects = editor->getAllObjects();
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
    auto objects = editor->getAllObjects();
    for (int i = objects->count() - 1; i >= 0; --i) {
        auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
        
        if (obj->m_isTrigger && obj->m_objectID == 0) {
            editor->removeObject(obj, true);
        }
    }
}

bool LevelOptimizer::isObjectDecorative(GameObject* obj) {
    int id = obj->m_objectID;
    return (id > 1000 && id < 2000) || (id > 3000);
}
