#ifndef EditorUIHook_hpp
#define EditorUIHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class PSMEditorUI : public Modify<PSMEditorUI, EditorUI> {
public:
    // 2.2 requires the specific signature found in EditorUI.hpp
    bool init(LevelEditorLayer* lel) override;
    
    void onOpenDashboard(CCObject* sender);
    void updateDashboardButtonState();
};
#endif
