#ifndef MainDashboardLayer_hpp
#define MainDashboardLayer_hpp

#include <Geode/Geode.hpp>
#include <vector>
#include <string>

using namespace geode::prelude;

/**
 * MainDashboardLayer provides the control surface for Co Engine.
 * It manages user inputs for procedural generation and level optimization.
 */
class MainDashboardLayer : public Popup<> {
protected:
    // Required by Popup class
    bool setup() override;

    // --- UI Logic Methods ---
    void onGenerateWave(CCObject* sender);
    void onOptimizeLevel(CCObject* sender);
    void onToggleAdvancedMode(CCObject* sender);
    void onSliderUpdate(CCObject* sender); // For controlling pattern density/length

    // --- State Management ---
    bool m_isAdvancedMode = false;
    float m_currentDifficulty = 1.0f;
    std::string m_selectedPattern = "WavePath";

public:
    // Factory method to create the layer
    static MainDashboardLayer* create();

private:
    // Helper to refresh UI components if toggles are pressed
    void updateMenuDisplay();
    
    // UI layout constants
    const float POPUP_WIDTH = 320.0f;
    const float POPUP_HEIGHT = 240.0f;
};

#endif /* MainDashboardLayer_hpp */
