#ifndef MainDashboardLayer_hpp
#define MainDashboardLayer_hpp

#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Changed from geode::Popup<> to FLAlertLayer (like BossFightEditor)
// FLAlertLayer is more stable and has better API support
class MainDashboardLayer : public FLAlertLayer {
protected:
    bool init() override;

    void onGenerateWave(CCObject* sender);
    void onUndo(CCObject* sender);
    void onOptimizeLevel(CCObject* sender);
    void onToggleAdvancedMode(CCObject* sender);

    bool m_isAdvancedMode = false;
    float m_currentDifficulty = 1.0f;
    std::string m_selectedPattern = "WavePath";

public:
    static MainDashboardLayer* create();
    void updateMenuDisplay();
};

#endif
