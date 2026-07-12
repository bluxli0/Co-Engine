#include "SmartGridSerializer.hpp"

// Initialize the Singleton instance
SmartGridSerializer* SmartGridSerializer::sharedState() {
    static SmartGridSerializer* instance = new SmartGridSerializer();
    return instance;
}

// Retrieves and caches metadata for objects
ObjectMetadata SmartGridSerializer::getObjectMetadata(int objectID) {
    if (m_metadataCache.find(objectID) != m_metadataCache.end()) {
        return m_metadataCache[objectID];
    }

    // Default metadata for unknown objects
    ObjectMetadata meta = {objectID, 30.0f, 30.0f, true, false};

    // Database lookup logic (Can be expanded to hundreds of IDs)
    switch(objectID) {
        case 1:    meta = {1, 30.0f, 30.0f, true, false}; break;
        case 211:  meta = {211, 30.0f, 30.0f, false, true}; break;
        case 1764: meta = {1764, 30.0f, 30.0f, true, false}; break;
    }

    m_metadataCache[objectID] = meta;
    return meta;
}

// Generates grid coordinates for any given area
std::vector<CCPoint> SmartGridSerializer::calculatePlacementMatrix(float areaWidth, float areaHeight, float precision) {
    std::vector<CCPoint> matrix;
    for (float x = 0; x < areaWidth; x += precision) {
        for (float y = 0; y < areaHeight; y += precision) {
            matrix.push_back({x, y});
        }
    }
    return matrix;
}

// Pattern Generation Logic
std::vector<ObjectMetadata> SmartGridSerializer::generatePatternLayout(std::string patternType, float length) {
    std::vector<ObjectMetadata> layout;
    
    if (patternType == "WavePath") {
        for (float x = 0; x < length; x += 30.0f) {
            layout.push_back(getObjectMetadata(1)); // Path blocks
        }
    } else if (patternType == "HazardStaircase") {
        for (float x = 0; x < length; x += 60.0f) {
            layout.push_back(getObjectMetadata(211)); // Spike hazards
        }
    }
    
    return layout;
}

// Intelligent placement: checks for existing objects to prevent overlapping
void SmartGridSerializer::placeWithOptimization(LevelEditorLayer* editor, ObjectMetadata obj, CCPoint pos) {
    auto objects = editor->m_objects;
    bool collision = false;
    
    // Scan active objects in the editor for collision
    for (int i = 0; i < objects->count(); ++i) {
        auto other = static_cast<GameObject*>(objects->objectAtIndex(i));
        if (abs(other->getPositionX() - pos.x) < 20.0f && abs(other->getPositionY() - pos.y) < 20.0f) {
            collision = true;
            break;
        }
    }
    
    if (!collision) {
        editor->createObject(obj.objectID, pos, true);
    }
}

// Validation logic
bool SmartGridSerializer::isPlacementValid(CCPoint position, ObjectMetadata objData) {
    // Basic bounds check (e.g., stay within level limits)
    return (position.x >= 0 && position.y >= 0);
}
