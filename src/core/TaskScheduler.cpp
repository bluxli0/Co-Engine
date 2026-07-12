#include "TaskScheduler.hpp"

TaskScheduler* TaskScheduler::shared() {
    static TaskScheduler* instance = new TaskScheduler();
    return instance;
}

void TaskScheduler::addTask(ProceduralTask task) {
    m_taskQueue.push(task);
}

void TaskScheduler::update(float dt) {
    if (m_taskQueue.empty()) return;

    // Process the current task
    auto& currentTask = m_taskQueue.front();
    currentTask.work(dt);

    // If finished, pop and move to next
    if (currentTask.isFinished()) {
        m_taskQueue.pop();
        Notification::create(currentTask.name + " complete!", NotificationIcon::Success)->show();
    }
}
