#include "SelectedShape.hpp"

#include <utility>

namespace VisualEditor {
    namespace Graphics {

        SelectedShape::SelectedShape(std::shared_ptr<Shape> shape) {
            mShape = std::move(shape);
        }

        void SelectedShape::Render() {
            mShape->Render();
            auto size = mShape->GetSize();
            GraphicUtility::Grid(mPosition, size.x * 2.015);
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

        void SelectedShape::Move(ImVec2 delta) {
            mShape->Move(delta);
        }

        Shape *SelectedShape::Copy() {
            return mShape->Copy();
        }

    }
}