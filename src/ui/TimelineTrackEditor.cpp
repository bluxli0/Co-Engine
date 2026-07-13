#include "TimelineTrackEditor.hpp"

bool TimelineTrackEditor::init() {
    // FLAlertLayer::init requires all 9 parameters:
    // delegate, title, desc, btn1, btn2, width, scroll, height, textScale
    if (!FLAlertLayer::init(nullptr, "Timeline Track Editor", "", "OK", nullptr, 320.0f, false, 240.0f, 1.0f)) {
        return false;
    }

    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // 1. Setup the track drawing area
    m_trackDrawer = CCDrawNode::create();
    this->m_mainLayer->addChild(m_trackDrawer);

    // 2. Playback Button - FIX: Needs 4 params (normal, selected, target, callback)
    auto menu = CCMenu::create();
    auto playBtn = CCMenuItemSpriteExtra::create(
        ButtonSprite::create("Play"),
        ButtonSprite::create("Play"),  // selected state
        this,
        menu_selector(TimelineTrackEditor::onPlay)
    );
    menu->addChild(playBtn);
    menu->setPosition({winSize.width / 2, 50});
    this->m_mainLayer->addChild(menu);

    return true;
}

float TimelineTrackEditor::timeToPixel(float time) {
    // Map seconds (time) to screen pixels based on zoom level
    return (time * 100.0f) * m_zoomLevel;
}

float TimelineTrackEditor::pixelToTime(float x) {
    // Reverse mapping: pixels to time
    return x / (100.0f * m_zoomLevel);
}

void TimelineTrackEditor::renderTracks() {
    if (!m_trackDrawer) return;
    
    m_trackDrawer->clear();
    
    // Draw the timeline axis
    m_trackDrawer->drawSegment({0, 100}, {300, 100}, 2.0f, ccc4f(1, 1, 1, 1));

    // Draw each event as a "Keyframe"
    for (const auto& event : m_events) {
        float x = timeToPixel(event.timestamp);
        m_trackDrawer->drawDot({x, 100}, 8.0f, ccc4f(1, 0, 0, 1)); // Red dot for event
    }
}

void TimelineTrackEditor::updateKeyframeVisuals() {
    renderTracks();
}

void TimelineTrackEditor::onPlay(CCObject* sender) {
    m_isPlaying = !m_isPlaying;
    if (m_isPlaying) {
        this->scheduleUpdate(); // Now works because FLAlertLayer inherits from CCNode
    } else {
        this->unscheduleUpdate();
    }
}

void TimelineTrackEditor::onAddKeyframe(CCObject* sender) {
    // Add a new keyframe at the current time
    TimelineEvent newEvent = {m_currentTime, 0, 1.0f};
    m_events.push_back(newEvent);
    renderTracks();
}

void TimelineTrackEditor::onDeleteKeyframe(CCObject* sender) {
    // TODO: Implement delete logic
}

void TimelineTrackEditor::onSliderMove(CCObject* sender) {
    // TODO: Implement slider logic
}

void TimelineTrackEditor::update(float dt) {
    if (m_isPlaying) {
        m_currentTime += dt;
        renderTracks();
    }
}

TimelineTrackEditor* TimelineTrackEditor::create() {
    auto ret = new TimelineTrackEditor();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
