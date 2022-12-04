#include "CircleShape.hpp"

namespace VisualEditor{
    namespace Graphics {

        void CircleShape::Render() {
            GraphicUtility::CircleEdge(mPosition, mRadius, mColor);
            if (mHovered || mSelected)
                GraphicUtility::CircleEdge(mPosition, mRadius + 0.01);
        }

        void CircleShape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
            Shape::OnEvent(event, mousePos);
            auto dist = sqrt( ((mPosition.x - mousePos.x) * (mPosition.x - mousePos.x))
                    + ((mPosition.y - -mousePos.y) * (mPosition.y - -mousePos.y)) );
            mHovered = dist <= mRadius;
            auto normPos = ImVec2(mousePos.x, -mousePos.y);
            if (event->type == SDL_MOUSEBUTTONDOWN &&
                    ((normPos.x > -1 && normPos.x < 1) && (normPos.y > -1 && normPos.y < 1))
            ) {
                if (!mHovered && mShift && mSelected) {

                }
                else mSelected = mHovered;
                mMousePressed = true;
            }
            if (event->type == SDL_MOUSEBUTTONUP)
                mMousePressed = false;
            if (event->type == SDL_MOUSEMOTION) {
                if (mMousePressed && mHovered && !CheckBounds(ImVec2(mousePos.x, -mousePos.y)) )
                    mPosition = ImVec2(mousePos.x, -mousePos.y);
            }
        }

        Quad CircleShape::GetBounds(ImVec2 pos) {
            Quad quad;
            quad.TopLeft = ImVec2(pos.x - (mRadius + 0.01), pos.y + (mRadius + 0.01));
            quad.TopRight = ImVec2(pos.x + (mRadius + 0.01), pos.y + (mRadius + 0.01));
            quad.BtmLeft = ImVec2(pos.x - (mRadius + 0.01), pos.y - (mRadius + 0.01));
            quad.BtmRight = ImVec2(pos.x + (mRadius + 0.01), pos.y - (mRadius + 0.01));
            return quad;
        }

        const bool CircleShape::IsMouseHover(ImVec2 mousePos) const {
            return 0;
        }

    }
}