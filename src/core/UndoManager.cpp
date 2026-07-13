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
    auto objects = editor->getAllObjects();

    for (int id : lastAction.addedObjectIDs) {
        for (int i = objects->count() - 1; i >= 0; --i) {
            auto obj = static_cast<GameObject*>(objects->objectAtIndex(i));
            // Updated to m_objectID
            if (obj->m_objectID == id) { 
                editor->removeObject(obj, true);
                break;
            }
        }
    }
    m_history.pop();
}
