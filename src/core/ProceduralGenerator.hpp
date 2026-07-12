#ifndef ProceduralGenerator_hpp
#define ProceduralGenerator_hpp

#include <Geode/Geode.hpp>
#include "SmartGridSerializer.hpp"
#include <random>

using namespace geode::prelude;

struct GenerationSettings {
    float difficulty;
    bool includeHazards;
    int objectLimit;
    unsigned int seed;
};

class ProceduralGenerator {
public:
    static ProceduralGenerator* shared();

    // The high-level orchestrator
    void generateProceduralArea(LevelEditorLayer* editor, std::string patternName, float startX, float length, GenerationSettings settings);

private:
    ProceduralGenerator() : m_mt(std::random_device{}()) {}

    // Advanced Generators
    void generateSinuousPath(LevelEditorLayer* editor, float startX, float length, GenerationSettings settings);
    void generateFractalSpikes(LevelEditorLayer* editor, float startX, float length, GenerationSettings settings);
    
    // Random engine for deterministic results
    std::mt19937 m_mt;
    float getRandomFloat(float min, float max);
};

#endif
