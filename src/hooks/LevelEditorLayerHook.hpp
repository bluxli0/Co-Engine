#ifndef LevelEditorLayerHook_hpp
#define LevelEditorLayerHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class PSMEditorLayer : public Modify<PSMEditorLayer, LevelEditorLayer> {
public:
    void update(float dt) override;
    void createObject(int id, CCPoint pos, bool p2) override;
    void destructor() override;

    // Advanced Engine Hooks
    void onEditorClosed();
    bool isOptimizationEnabled();
};
#endif
