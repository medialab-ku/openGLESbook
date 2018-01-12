#include "main.h"

Scene* scene = nullptr;

void surfaceCreated(const AAssetManager* aAssetManager, const int id) {
    // set asset manager
    AssetManager::set(aAssetManager);

    // select scene
    switch (id) {
        case 0:
            scene = new HelloTeapot();
            break;
        case 1:
            scene = new ImageTexturing();
            break;
        case 2:
            scene = new PhongLighting();
            break;
        case 3:
            scene = new ArcballRotation();
            break;
        case 4:
            scene = new NormalMapping();
            break;
        case 5:
            scene = new TangentMapping();
            break;
        case 6:
            scene = new ShadowMapping();
            break;
        case 7:
            scene = new CubeMapping();
            break;
        case 8:
            scene = new PN_Triangles();
            break;
        case 9:
            scene = new DispMapping();
            break;
        default:
            // impossible case
            break;
    }
}

void surfaceChanged(const int width, const int height) {
    // update screen width and height
    Screen::setWidth(width);
    Screen::setHeight(height);
}

void drawFrame(const float deltaTime) {
    // run scene
    if (scene) scene->run(deltaTime);
}

void touchEvent(const int motion, const float x, const float y) {
    // update touch motion
    switch (motion) {
        case 0:
            Touch::setMotion(Touch::Motion::DOWN);
            break;
        case 1:
            Touch::setMotion(Touch::Motion::MOVE);
            break;
        case 2:
            Touch::setMotion(Touch::Motion::UP);
            break;
        default:
            // impossible case
            break;
    }

    // update touch position
    Touch::setX(x);
    Touch::setY(y);
}
