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
        obj->setOpacity(255);
        return obj;
    }

    auto obj = GameObject::createWithKey(objectID);
    editor->addSpecial(obj); // 2.2 compliant addition
    return obj;
}

void ObjectPoolManager::releaseObject(GameObject* obj) {
    if (!obj) return;

    obj->setVisible(false);
    obj->setPosition({-10000, -10000});
    obj->setOpacity(0);
    
    // Updated to m_objectID
    m_pools[obj->m_objectID].push_back(obj);
}

void ObjectPoolManager::clearAllPools() {
    for (auto& [id, pool] : m_pools) {
        for (auto obj : pool) {
            obj->removeMeAndCleanup();
        }
    }
    m_pools.clear();
}
