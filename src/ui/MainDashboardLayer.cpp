#include "MainDashboardLayer.hpp"
#include "../core/ProceduralGenerator.hpp"
#include "../core/LevelOptimizer.hpp"
#include "../core/UndoManager.hpp"

bool MainDashboardLayer::init() {
    // FLAlertLayer::init only takes opacity parameter
    // We'll set up the popup with default settings and customize via setTitle
    if (!FLAlertLayer::init(0)) {
        return false;
    }
    
    this->setTitle("Co Engine Pro Dashboard");

    auto menu = CCMenu::create();
    
    // 1. Generate Wave Button
    auto waveBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Generate Wave", "goldFont.fnt", "GJ_button_01.png"),
        ButtonSprite::create("Generate Wave", "goldFont.fnt", "GJ_button_01.png"),
        this,
        menu_selector(MainDashboardLayer::onGenerateWave)
    );
    waveBtn->setPosition({-80, 40});
    menu->addChild(waveBtn);

    // 2. Undo Button
    auto undoBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Undo", "goldFont.fnt", "GJ_button_03.png"),
        ButtonSprite::create("Undo", "goldFont.fnt", "GJ_button_03.png"),
        this,
        menu_selector(MainDashboardLayer::onUndo)
    );
    undoBtn->setPosition({80, 40});
    menu->addChild(undoBtn);

    // 3. Optimizer Button
    auto optBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Optimize Level", "goldFont.fnt", "GJ_button_02.png"),
        ButtonSprite::create("Optimize Level", "goldFont.fnt", "GJ_button_02.png"),
        this,
        menu_selector(MainDashboardLayer::onOptimizeLevel)
    );
    optBtn->setPosition({0, 0});
    menu->addChild(optBtn);

    // 4. Advanced Toggle
    auto advBtn = CCMenuItemToggler::create(
        ButtonSprite::create("Basic"),
        ButtonSprite::create("Advanced"),
        this,
        menu_selector(MainDashboardLayer::onToggleAdvancedMode)
    );
    advBtn->setPosition({0, -50});
    menu->addChild(advBtn);

    this->m_mainLayer->addChild(menu);
    return true;
}

void MainDashboardLayer::onGenerateWave(CCObject* sender) {
    auto editor = LevelEditorLayer::get();
    if (!editor) {
        log::warn("LevelEditorLayer not available");
        return;
    }
    
    GenerationSettings settings = { 1.0f, true, 500, 12345 };
    ProceduralGenerator::shared()->generateProceduralArea(editor, "SinuousPath", 100.0f, 500.0f, settings);
    Notification::create("Generated SinuousPath", NotificationIcon::Success)->show();
}

void MainDashboardLayer::onUndo(CCObject* sender) {
    auto editor = LevelEditorLayer::get();
    if (!editor) return;
    
    UndoManager::shared()->undoLastAction(editor);
    Notification::create("Undo successful", NotificationIcon::Info)->show();
}

void MainDashboardLayer::onOptimizeLevel(CCObject* sender) {
    auto editor = LevelEditorLayer::get();
    if (!editor) return;
    
    LevelOptimizer::sharedState()->runOptimizationPass(editor);
    this->updateMenuDisplay();
}

void MainDashboardLayer::onToggleAdvancedMode(CCObject* sender) {
    m_isAdvancedMode = !m_isAdvancedMode;
    this->updateMenuDisplay();
}

void MainDashboardLayer::updateMenuDisplay() {
    log::info("UI State Updated: Advanced Mode = {}", m_isAdvancedMode ? "ON" : "OFF");
}

MainDashboardLayer* MainDashboardLayer::create() {
    auto ret = new MainDashboardLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
