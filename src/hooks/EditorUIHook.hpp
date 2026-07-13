#ifndef LevelEditorLayerHook_hpp
#define LevelEditorLayerHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class PSMEditorLayer : public Modify<PSMEditorLayer, LevelEditorLayer> {
public:
    void update(float dt); // Removed override
    void createObject(int id, CCPoint pos, bool p2); // Removed override
    ~PSMEditorLayer(); // Destructors are handled differently in 2.2

    void onEditorClosed();
    bool isOptimizationEnabled();
};
#endif
