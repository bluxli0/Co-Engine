#ifndef EditorUIHook_hpp
#define EditorUIHook_hpp

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class PSMEditorUI : public Modify<PSMEditorUI, EditorUI> {
public:
    bool init(LevelEditorLayer* lel); 
    void onOpenDashboard(CCObject* sender);
    void updateDashboardButtonState();
};
#endif
