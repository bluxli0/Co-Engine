#include <Geode/Geode.hpp>

using namespace geode::prelude;

/**
 * Co Engine entry point.
 * We register our resource dependencies using the _spr macro 
 * to ensure Geode's resource manager maps them correctly.
 */
$on_mod(Loaded) {
    // Register the sprite sheet for the dashboard and UI icons
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PSM_Sheet.plist"_spr);
    
    log::info("Co Engine initialized: Procedural Suite resources registered.");
}

// REMOVED the $on_mod(Unloaded) block because it is causing the compiler error.
