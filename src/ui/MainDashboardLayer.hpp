#ifndef MainDashboardLayer_hpp
#define MainDashboardLayer_hpp

#include <Geode/Geode.hpp>
#include <Geode/ui/Popup.hpp> // Essential include

using namespace geode::prelude;

class MainDashboardLayer : public geode::Popup<> {
protected:
    bool setup() override;

    void onGenerateWave(CCObject* sender);
    void onUndo(CCObject* sender); // Added missing declaration
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
