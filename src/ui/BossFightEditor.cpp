#include "BossFightEditor.hpp"
#include "../core/ProceduralGenerator.hpp"
#include "../core/UndoManager.hpp"
#include "../core/LevelOptimizer.hpp"

bool BossFightEditor::init() {
    // Standard Geode Popup Setup
    if (!FLAlertLayer::init(nullptr, "Boss Fight Pro Engine", "Close", nullptr, 450.f, false)) return false;

    // Use a layout-aware container
    auto container = CCNode::create();
    container->setContentSize({400.f, 200.f});
    container->setLayout(RowLayout::create()->setGap(10.f)->setAxisAlignment(AxisAlignment::Center));
    
    // 1. Generate Button
    auto genBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Spawn Boss Path", "goldFont.fnt", "GJ_button_01.png"),
        this, menu_selector(BossFightEditor::onGenerateBoss)
    );
    
    // 2. Undo Button
    auto undoBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Undo", "goldFont.fnt", "GJ_button_03.png"),
        this, menu_selector(BossFightEditor::onUndo)
    );

    // 3. Optimize Button
    auto optBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Optimize", "goldFont.fnt", "GJ_button_02.png"),
        this, menu_selector(BossFightEditor::onOptimize)
    );

    auto menu = CCMenu::create();
    menu->addChild(genBtn);
    menu->addChild(undoBtn);
    menu->addChild(optBtn);
    menu->updateLayout();
    
    this->m_mainLayer->addChild(menu);
    return true;
}

void BossFightEditor::onGenerateBoss(CCObject* sender) {
    auto editor = LevelEditorLayer::get();
    GenerationSettings settings = { 2.5f, true, 888, 5555 }; // High difficulty boss settings
    
    // Triggers the engine
    ProceduralGenerator::shared()->generateProceduralArea(editor, "FractalSpikes", 200.0f, 1000.0f, settings);
    
    Notification::create("Boss Path Generated!", NotificationIcon::Success)->show();
}

void BossFightEditor::onUndo(CCObject* sender) {
    UndoManager::shared()->undoLastAction(LevelEditorLayer::get());
}

void BossFightEditor::onOptimize(CCObject* sender) {
    LevelOptimizer::sharedState()->runOptimizationPass(LevelEditorLayer::get());
    Notification::create("Level Optimized.", NotificationIcon::Info)->show();
}

BossFightEditor* BossFightEditor::create() {
    auto ret = new BossFightEditor();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
