#include "QuadShape.hpp"

namespace VisualEditor{
    namespace Graphics {

        void QuadShape::Render() {
            GraphicUtility::QuadEdge(mPosition, mSize, mColor);
            if (mHovered || mSelected)
                GraphicUtility::QuadEdge(mPosition, ImVec2(mSize.x + 0.015, mSize.y + 0.015));
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

    }
}