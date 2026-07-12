#ifndef SmartGridSerializer_hpp
#define SmartGridSerializer_hpp

#include <Geode/Geode.hpp>
#include <vector>
#include <string>
#include <map>

using namespace geode::prelude;

/**
 * Metadata for every object type.
 * Used by the engine to calculate spacing, collisions, and grid alignment.
 */
struct ObjectMetadata {
    int objectID;
    float width;
    float height;
    bool isSolid;
    bool isHazard;
};

class SmartGridSerializer {
public:
    // Global Accessor (Singleton)
    static SmartGridSerializer* sharedState();

    // -- Core Engine Logic --
    
    // Retrieves size and type data for a specific Geometry Dash object ID
    ObjectMetadata getObjectMetadata(int objectID);

    // Calculates a grid of points based on area size and your chosen precision
    std::vector<CCPoint> calculatePlacementMatrix(float areaWidth, float areaHeight, float precision);

    // Determines if a coordinate is valid (prevents overlapping/clipping)
    bool isPlacementValid(CCPoint position, ObjectMetadata objData);

    // Generates a list of objects based on a named procedural pattern (e.g., "WavePath")
    std::vector<ObjectMetadata> generatePatternLayout(std::string patternType, float length);

    // Executes the actual placement into the Level Editor
    void placeWithOptimization(LevelEditorLayer* editor, ObjectMetadata obj, CCPoint pos);

private:
    // Internal Cache to ensure high performance
    std::map<int, ObjectMetadata> m_metadataCache;
    
    // Private constructor for Singleton pattern
    SmartGridSerializer() {}
};

#endif /* SmartGridSerializer_hpp */
