#pragma once
#include "ShapeFactory.hpp"
#include "pch.hpp"

namespace VisualEditor {

    class IChangeable {
    public:
        virtual void Redo() = 0;
        virtual void Undo() = 0;
    };

    class ICommand : public IChangeable {
    public:
        virtual void Execute() = 0;
        virtual std::string GetName() = 0;
        virtual ~ICommand() = default;
    };

    class CommandDispatcher final {
    public:
        CommandDispatcher() = default;
        void ExecuteCommand(std::shared_ptr<ICommand> cmd) {
            mRedoStack = std::stack<std::shared_ptr<ICommand>>();
            cmd->Execute();
            mUndoStack.push(cmd);
            mCommandStack.push(cmd);
        }
        void Undo() {
            if (mUndoStack.empty())
                return;
            mUndoStack.top()->Undo();
            mRedoStack.push(mUndoStack.top());
            mUndoStack.pop();
            mCommandStack.pop();
        }
        void Redo() {
            if (mRedoStack.empty())
                return;
            mRedoStack.top()->Redo();
            mUndoStack.push(mRedoStack.top());
            mCommandStack.push(mRedoStack.top());
            mRedoStack.pop();
        }
        std::stack<std::shared_ptr<ICommand>> GetStack() { return mCommandStack; }
    private:
        std::stack<std::shared_ptr<ICommand>> mUndoStack;
        std::stack<std::shared_ptr<ICommand>> mRedoStack;
        std::stack<std::shared_ptr<ICommand>> mCommandStack;
    };

    class ShapeChangeColorCommand final : public ICommand {
    public:
        ShapeChangeColorCommand(const std::shared_ptr<Graphics::Shape>& shape, ImVec4 color);
        void Execute() override;
        void Undo() override;
        void Redo() override;
        std::string GetName() override { return "Shape color changed"; }
    private:
        ImVec4 mPrevColor;
        ImVec4 mNewColor;
        std::shared_ptr<Graphics::Shape> mShape;
    };

    class ShapeMoveCommand final : public ICommand {
    public:
        ShapeMoveCommand(const std::shared_ptr<Graphics::Shape>& shape, ImVec2 oldPos, ImVec2 newPos);
        void Execute() override;
        void Undo() override;
        void Redo() override;
        std::string GetName() override { return "Shape moved"; }
    private:
        ImVec2 mPrevPos;
        ImVec2 mNewPos;
        std::shared_ptr<Graphics::Shape> mShape;
    };

    class AddShapeCommand final : public ICommand {
    public:
        AddShapeCommand(std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> storage, Graphics::ShapeType type);
        void Execute() override;
        void Undo() override;
        void Redo() override;
        std::string GetName() override { return "Shape added"; }
    private:
        void Push();
    private:
        std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> mStorage;
        uint32_t mIndexShape{};
        Graphics::ShapeType mType;
        bool mInit = false;
        std::shared_ptr<Graphics::Shape> mShape;
    };
}