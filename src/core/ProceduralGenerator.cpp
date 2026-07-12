#include "ProceduralGenerator.hpp"
#include "LevelOptimizer.hpp"
#include "UndoManager.hpp"
#include "TaskScheduler.hpp" // Required for the Scheduler

ProceduralGenerator* ProceduralGenerator::shared() {
    static ProceduralGenerator* instance = new ProceduralGenerator();
    return instance;
}

void ProceduralGenerator::generateProceduralArea(LevelEditorLayer* editor, std::string patternName, float startX, float length, GenerationSettings settings) {
    m_mt.seed(settings.seed);

    // Encapsulate the state needed for the task
    struct TaskState {
        float currentX;
        float endX;
        std::vector<int> batch;
    };
    
    // We create a shared pointer to persist state across frames
    auto state = std::make_shared<TaskState>(TaskState{startX, startX + length, {}});

    auto task = ProceduralTask{
        patternName,
        [this, editor, settings, state](float dt) {
            auto serializer = SmartGridSerializer::sharedState();
            float sliceStep = 90.0f; // 3 blocks per frame to keep it smooth
            float batchEnd = std::min(state->currentX + sliceStep, state->endX);

            for (float x = state->currentX; x < batchEnd; x += 30.0f) {
                // Determine logic based on pattern
                float y = 150.0f + (sin(x * 0.05f) * (settings.difficulty * 40.0f));
                CCPoint pos = {x, y};
                auto meta = serializer->getObjectMetadata(1);

                if (serializer->isPlacementValid(pos, meta)) {
                    serializer->placeWithOptimization(editor, meta, pos);
                    state->batch.push_back(meta.objectID);
                }
            }
            state->currentX = batchEnd;
        },
        [state]() { return state->currentX >= state->endX; }
    };

    TaskScheduler::shared()->addTask(task);
    
    // Once task finishes, register Undo (You would ideally have a callback for this)
    // For now, note that the UndoManager needs to handle the batch provided by the task
}
