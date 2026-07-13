#ifndef LevelEditorLayerHook_hpp
#define LevelEditorLayerHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>

using namespace geode::prelude;

class PSMEditorLayer : public Modify<PSMEditorLayer, LevelEditorLayer> {
public:
    void update(float dt) override;
    void createObject(int id, CCPoint pos, bool p2) override;
    // 2.2 bindings use ~LevelEditorLayer() for destructor hooks
    void destructor() override; 

    void onEditorClosed();
    bool isOptimizationEnabled();
};
#endif
