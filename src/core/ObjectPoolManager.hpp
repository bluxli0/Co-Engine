#ifndef ObjectPoolManager_hpp
#define ObjectPoolManager_hpp

#include <Geode/Geode.hpp>
#include <vector>
#include <map>

using namespace geode::prelude;

class ObjectPoolManager {
public:
    static ObjectPoolManager* shared();

    // Acquire an object specific to the ID
    GameObject* acquireObject(int objectID, LevelEditorLayer* editor);
    
    // Release and recycle
    void releaseObject(GameObject* obj);
    
    // Clear the pool (Call this when closing the editor/level to free memory)
    void clearAllPools();

private:
    ObjectPoolManager() {}
    // Map objectID to a stack of available instances
    std::map<int, std::vector<GameObject*>> m_pools;
};

#endif
