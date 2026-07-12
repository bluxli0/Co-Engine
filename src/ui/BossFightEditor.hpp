#ifndef BossFightEditor_hpp
#define BossFightEditor_hpp

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class BossFightEditor : public FLAlertLayer {
public:
    static BossFightEditor* create();
    bool init() override;
    
    // UI Callbacks
    void onGenerateBoss(CCObject* sender);
    void onUndo(CCObject* sender);
    void onOptimize(CCObject* sender);
};

#endif
