#ifndef TimelineTrackEditor_hpp
#define TimelineTrackEditor_hpp

#include <Geode/Geode.hpp>
#include <vector>
#include <string>
#include <map>

using namespace geode::prelude;

// Represents a single procedural event on the timeline
struct TimelineEvent {
    float timestamp;      // When the event triggers (seconds)
    int eventType;        // Type of procedural logic (e.g., GenerateWave)
    float paramDensity;   // Intensity of the generation
};

/**
 * TimelineTrackEditor manages the non-linear editing of procedural events.
 * Inherits from FLAlertLayer to get m_mainLayer, setTitle, and CCNode scheduling methods.
 */
class TimelineTrackEditor : public FLAlertLayer {
protected:
    bool init() override;

    // --- Timeline Interaction ---
    void onPlay(CCObject* sender);
    void onAddKeyframe(CCObject* sender);
    void onDeleteKeyframe(CCObject* sender);
    void onSliderMove(CCObject* sender);

    // --- Rendering Helpers ---
    void renderTracks();
    void updateKeyframeVisuals();
    void update(float dt) override;  // CCNode scheduling

public:
    static TimelineTrackEditor* create();

    // The data set for the timeline
    std::vector<TimelineEvent> m_events;
    
    // UI State
    float m_zoomLevel = 1.0f;
    float m_currentTime = 0.0f;
    bool m_isPlaying = false;

private:
    // Drawing node for high-performance track visualization
    CCDrawNode* m_trackDrawer;
    
    // Helper to calculate x-coordinate on screen based on time
    float timeToPixel(float time);
    float pixelToTime(float x);
};

#endif /* TimelineTrackEditor_hpp */
