#include "Command.hpp"
#include <utility>
#include "Shape.hpp"

namespace VisualEditor {

    ShapeChangeColorCommand::ShapeChangeColorCommand(const std::shared_ptr<Graphics::Shape>& shape, ImVec4 color) {
        mNewColor = color;
        mPrevColor = shape->GetColor();
        mShape = shape;
    }

    void ShapeChangeColorCommand::Execute() {
        if (mShape->GetName() == "GroupShape") {
            mShape->SetColor(mNewColor);
        }
        else mShape->SetColor(mNewColor);
    }

    void ShapeChangeColorCommand::Undo() {
        if (mShape->GetName() == "GroupShape") {
            mShape->SetColor(mPrevColor);
        }
        else mShape->SetColor(mPrevColor);
    }

    void ShapeChangeColorCommand::Redo() {
        if (mShape->GetName() == "GroupShape") {
            mShape->SetColor(mNewColor);
        }
        else mShape->SetColor(mNewColor);
    }

    AddShapeCommand::AddShapeCommand(std::shared_ptr<Storage<std::shared_ptr<Graphics::Shape>>> storage,
                                     Graphics::ShapeType type) {
        mStorage = std::move(storage);
        mType = type;
    }

    void AddShapeCommand::Execute() {
        this->Push();
    }

    void AddShapeCommand::Undo() {
        mStorage->Remove(mIndexShape);
    }

    void AddShapeCommand::Redo() {
        this->Push();
    }

    void AddShapeCommand::Push() {
        if (!mInit) {
            mStorage->Push(Graphics::ShapeFactory::CreateShape(mType));
            mShape = mStorage->Back();
            mIndexShape = mStorage->Size();
            mInit = true;
        }
        else {
            mStorage->Push(mShape);
        }
    }

    ShapeMoveCommand::ShapeMoveCommand(const std::shared_ptr<Graphics::Shape> &shape, ImVec2 oldPos, ImVec2 newPos) {
        mShape = shape;
        mPrevPos = oldPos;
        mNewPos = newPos;
    }

    void ShapeMoveCommand::Execute() {

    }

    void ShapeMoveCommand::Undo() {
        mShape->SetPos(mPrevPos);
    }

    void ShapeMoveCommand::Redo() {
        mShape->SetPos(mNewPos);
    }

}