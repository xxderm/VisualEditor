#include "SelectedShape.hpp"

#include <utility>

namespace VisualEditor::Graphics {

        SelectedShape::SelectedShape(const std::shared_ptr<Shape>& shape) {
            mShape = shape;
            this->mPosition = shape->GetPosition();
        }

        void SelectedShape::Render() {
            mShape->Render();
            auto size = mShape->GetSize();
            size.x *= 1.1;
            size.y *= 1.1;
            GraphicUtility::Grid(mPosition, size);
        }

        void SelectedShape::Load(nlohmann::json *data, uint32_t *index) {
            Shape::Load(data, index);
            mShape->Load(data, index);
        }

        void SelectedShape::Save(nlohmann::json *data, uint32_t *index) {
            Shape::Save(data, index);
            mShape->Save(data, index);
        }

        bool SelectedShape::IsMouseHover(ImVec2 mousePos) {
            return mShape->IsMouseHover(mousePos);
        }

        bool SelectedShape::IsInFlexBorder(ImVec2 mouse) {
            return mShape->IsInFlexBorder(mouse);
        }

        void SelectedShape::Amplify(ImVec2 mouse) {
            mShape->Amplify(mouse);
        }

        void SelectedShape::Flex(double dist) {
            mShape->Flex(dist);
        }

        Quad SelectedShape::GetBounds(ImVec2 pos) {
            return mShape->GetBounds(pos);
        }

        Shape *SelectedShape::Copy() {
            return mShape->Copy();
        }

    }