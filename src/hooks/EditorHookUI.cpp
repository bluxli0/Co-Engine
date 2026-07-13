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
    }
    return true;
}

void PSMEditorUI::onOpenDashboard(CCObject* sender) {
    // 2.2+ popups use the open() method
    MainDashboardLayer::create()->open();
}
