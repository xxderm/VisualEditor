#include "CircleShape.hpp"

namespace VisualEditor{
    namespace Graphics {

        void CircleShape::Render() {
            GraphicUtility::CircleEdge(mPosition, mRadius, mColor);
            if (mHovered || mSelected)
                GraphicUtility::CircleEdge(mPosition, mRadius + 0.01);
        }

        void CircleShape::OnEvent(SDL_Event *event, ImVec2 mousePos) {
            if (event->type == SDL_KEYDOWN)
                if (event->key.keysym.sym == SDLK_LSHIFT)
                    mShift = true;
            if (event->type == SDL_KEYUP)
                if (event->key.keysym.sym == SDLK_LSHIFT)
                    mShift = false;

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
                if (mMousePressed && mHovered && !CheckBounds(ImVec2(mousePos.x, -mousePos.y)))
                    mPosition = ImVec2(mousePos.x, -mousePos.y);
            }
        }

        bool CircleShape::CheckBounds(ImVec2 pos) {
            auto rad = (mRadius + 0.01);
            if ((pos.y +  rad) > 1)
                return true;
            if ((pos.y - rad) < -1)
                return true;
            if ((pos.x + rad) > 1)
                return true;
            return (pos.x - rad) < -1;
        }

    }
}