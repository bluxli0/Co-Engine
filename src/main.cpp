#include <Geode/Geode.hpp>

using namespace geode::prelude;

/**
 * The entry point of the Co Engine mod.
 * We register our resource dependencies here to ensure they 
 * are loaded into the game's memory safely on launch.
 */
$on_mod(Loaded) {
    // Register our procedural suite sprite sheet
    // This allows the editor hooks to access 'PSM_Sheet.plist' and 'PSM_Sheet.png'
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PSM_Sheet.plist");
    
    log::info("Co Engine initialized: Procedural Suite resources registered.");
}

// Optional: Define a clean-up method if you need to release heavy memory
// allocations when the mod is unloaded during a live session.
$on_mod(Unloaded) {
    log::info("Co Engine shutting down: Clearing resources.");
}
