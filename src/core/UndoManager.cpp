#include "UndoManager.hpp"

UndoManager* UndoManager::shared() {
    static UndoManager* instance = new UndoManager();
    return instance;
}

void UndoManager::pushAction(std::vector<int> objectIDs) {
    m_history.push({objectIDs});
}

void UndoManager::undoLastAction(LevelEditorLayer* editor) {
    if (m_history.empty()) return;

    auto lastAction = m_history.top();
    auto objects = editor->m_objects;

    // Remove only the objects created in the last action
    for (int id : lastAction.addedObjectIDs) {
        for (int i = objects->count() - 1; i >= 0; --i) {
            auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
            if (obj->m_itemID == id) { // Using itemID as a unique reference
                editor->removeObject(obj, true);
                break;
            }
        }
    }
    m_history.pop();
}
