#ifndef MainDashboardLayer_hpp
#define MainDashboardLayer_hpp

#include <Geode/Geode.hpp>

using namespace geode::prelude;

// FLAlertLayer is the standard GD 2.2 alert/popup layer
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
