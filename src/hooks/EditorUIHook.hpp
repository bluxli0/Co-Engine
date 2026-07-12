#ifndef EditorUIHook_hpp
#define EditorUIHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class PSMEditorUI : public Modify<PSMEditorUI, EditorUI> {
public:
    bool init(LevelEditorLayer* lel) override;
    void onOpenDashboard(CCObject* sender);
    
    // Extended functionality for UI state management
    void updateDashboardButtonState();
};
#endif
