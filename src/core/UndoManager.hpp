#ifndef UndoManager_hpp
#define UndoManager_hpp

#include <Geode/Geode.hpp>
#include <vector>
#include <stack>

using namespace geode::prelude;

struct GenerationCommand {
    std::vector<int> addedObjectIDs; // Store IDs of objects created in this action
};

class UndoManager {
public:
    static UndoManager* shared();
    
    // Register an action when generating objects
    void pushAction(std::vector<int> objectIDs);
    
    // Perform the undo operation
    void undoLastAction(LevelEditorLayer* editor);

private:
    std::stack<GenerationCommand> m_history;
};

#endif
