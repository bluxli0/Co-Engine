#include "EditorUIHook.hpp"
#include "../ui/MainDashboardLayer.hpp"

bool PSMEditorUI::init(LevelEditorLayer* lel) {
    if (!EditorUI::init(lel)) return false;

    auto menu = this->getChildByID("button-menu");
    if (menu) {
        auto spr = CCSprite::createWithSpriteFrameName("PSM_Logo_Button.png"_spr);
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(PSMEditorUI::onOpenDashboard));
        
        btn->setID("psm-launcher-button"_spr);
        menu->addChild(btn);
        menu->updateLayout();
        log::info("Co Engine: UI launcher injected successfully.");
    }
    return true;
}

void PSMEditorUI::onOpenDashboard(CCObject* sender) {
    if (auto dashboard = MainDashboardLayer::create()) {
        dashboard->show();
    }
}
