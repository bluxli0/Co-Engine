#include "TimelineTrackEditor.hpp"

bool TimelineTrackEditor::setup() {
    this->setTitle("Timeline Track Editor");
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // 1. Setup the track drawing area
    m_trackDrawer = CCDrawNode::create();
    this->m_mainLayer->addChild(m_trackDrawer);

    // 2. Playback Button
    auto playBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Play"), this, menu_selector(TimelineTrackEditor::onPlay)
    );
    auto menu = CCMenu::create();
    menu->addChild(playBtn);
    menu->setPosition({winSize.width / 2, 50});
    this->m_mainLayer->addChild(menu);

    return true;
}

float TimelineTrackEditor::timeToPixel(float time) {
    // Map seconds (time) to screen pixels based on zoom level
    return (time * 100.0f) * m_zoomLevel;
}

void TimelineTrackEditor::renderTracks() {
    m_trackDrawer->clear();
    
    // Draw the timeline axis
    m_trackDrawer->drawSegment({0, 100}, {300, 100}, 2.0f, ccc4f(1, 1, 1, 1));

    // Draw each event as a "Keyframe"
    for (const auto& event : m_events) {
        float x = timeToPixel(event.timestamp);
        m_trackDrawer->drawDot({x, 100}, 8.0f, ccc4f(1, 0, 0, 1)); // Red dot for event
    }
}

void TimelineTrackEditor::onPlay(CCObject* sender) {
    m_isPlaying = !m_isPlaying;
    if (m_isPlaying) {
        this->scheduleUpdate(); // Start tracking level time
    } else {
        this->unscheduleUpdate();
    }
}
