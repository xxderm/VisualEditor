#include "QuadShape.hpp"

namespace VisualEditor{
    namespace Graphics {

        void QuadShape::Render() {
            GraphicUtility::QuadEdge(mPosition, mSize, mColor);
        }

        Quad QuadShape::GetBounds(ImVec2 pos) {
            Quad quad;
            quad.TopLeft = ImVec2(pos.x - (mSize.x / 2. + 0.01), (pos.y + (mSize.y / 2. + 0.01)));
            quad.TopRight = ImVec2(pos.x + (mSize.x / 2. + 0.01), (pos.y + (mSize.y / 2. + 0.01)));
            quad.BtmLeft = ImVec2(pos.x - (mSize.x / 2. + 0.01), (pos.y - (mSize.y / 2. + 0.01)));
            quad.BtmRight = ImVec2(pos.x + (mSize.x / 2. + 0.01), (pos.y - (mSize.y / 2. + 0.01)));
            return quad;
        }

        bool QuadShape::IsMouseHover(ImVec2 mousePos) {
            auto res = ((mousePos.x >= mPosition.x - mSize.x / 2.) && (mousePos.x <= mPosition.x + mSize.x / 2.)) &&
                       ((mousePos.y >= mPosition.y - mSize.y / 2.) && (mousePos.y <= mPosition.y + mSize.y / 2.));
            return res;
        }

        Shape* QuadShape::Copy() {
            QuadShape* copy = new QuadShape();
            copy->mSize = this->mSize;
            copy->mPosition = this->mPosition;
            copy->mColor = this->mColor;
            return copy;
        }

        bool QuadShape::IsInFlexBorder(ImVec2 mouse) {
            auto res =
                    ( (mouse.x >= mPosition.x - (mSize.x + 0.1) / 2. && mouse.x < mPosition.x - (mSize.x ) / 2.)
                    || (mouse.x > mPosition.x + (mSize.x ) / 2. && mouse.x < mPosition.x + (mSize.x + 0.1) / 2.) )
                    ||
                    ( (mouse.y >= mPosition.y - (mSize.y + 0.1) / 2. && mouse.y < mPosition.y - mSize.y / 2.)
                    || (mouse.y > mPosition.y + mSize.y / 2. && mouse.y < mPosition.y + (mSize.y + 0.1) / 2.) );
            return res;
        }

        void QuadShape::Amplify(ImVec2 mouse) {
            auto dist = sqrt( ((mPosition.x - mouse.x) * (mPosition.x - mouse.x))
                              + ((mPosition.y - mouse.y) * (mPosition.y - mouse.y)) );
            //mSize = ImVec2(dist * 2. - 0.025, dist * 2. - 0.025);
            Flex(dist * 2. - 0.085);
        }

        void QuadShape::Flex(double dist) {
            mSize = ImVec2(dist, dist);
        }

        QuadShape::QuadShape(const QuadShape &other) : Shape(other) {
            this->mSize = other.mSize;
        }

        void QuadShape::Save(nlohmann::json *data) {
            Shape::Save(data);
            (*data)["Name"] = GetName();
            (*data)["Size"]["X"] = mSize.x;
            (*data)["Size"]["Y"] = mSize.y;
        }

        void QuadShape::Load(nlohmann::json *data) {
            Shape::Load(data);
            mSize.x = (*data)["Size"]["X"];
            mSize.y = (*data)["Size"]["Y"];
        }

    }
}