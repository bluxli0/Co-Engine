#include "ObjectPoolManager.hpp"

ObjectPoolManager* ObjectPoolManager::shared() {
    static ObjectPoolManager* instance = new ObjectPoolManager();
    return instance;
}

GameObject* ObjectPoolManager::acquireObject(int objectID, LevelEditorLayer* editor) {
    auto& pool = m_pools[objectID];

    if (!pool.empty()) {
        auto obj = pool.back();
        pool.pop_back();
        obj->setVisible(true);
        // Re-enable interactions
        obj->setOpacity(255);
        return obj;
    }

    // Cache miss: Create new instance and return
    auto obj = GameObject::createWithKey(objectID);
    editor->addObject(obj); // Ensure it's in the editor's child list
    return obj;
}

void ObjectPoolManager::releaseObject(GameObject* obj) {
    if (!obj) return;

    // Reset properties for next use
    obj->setVisible(false);
    obj->setPosition({-10000, -10000}); // Safe-space
    obj->setOpacity(0);
    
    // Push to the correct pool based on itemID
    m_pools[obj->m_itemID].push_back(obj);
}

void ObjectPoolManager::clearAllPools() {
    for (auto& [id, pool] : m_pools) {
        for (auto obj : pool) {
            obj->removeMeAndCleanup(); // Properly delete objects in memory
        }
    }
    m_pools.clear();
}
