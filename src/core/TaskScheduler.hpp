#ifndef TaskScheduler_hpp
#define TaskScheduler_hpp

#include <Geode/Geode.hpp>
#include <queue>
#include <functional>

using namespace geode::prelude;

struct ProceduralTask {
    std::string name;
    std::function<void(float)> work; // The function to execute
    std::function<bool()> isFinished; // Condition to finish
};

class TaskScheduler : public CCNode {
public:
    static TaskScheduler* shared();
    void addTask(ProceduralTask task);
    void update(float dt) override;

private:
    std::queue<ProceduralTask> m_taskQueue;
    TaskScheduler() { this->scheduleUpdate(); }
};

#endif
