#ifndef OPENGLES_ASSET_H
#define OPENGLES_ASSET_H

#include "global.h"
#include "utility/picopng.h"

class AssetManager {
public:
    static void set(const AAssetManager* aAssetManager);
    static std::string readShader(const std::string& name);
    static ObjData readObject(const std::string &name);
    static ObjData readBinaryObject(const std::string &name);
    static PngData readTexture(const std::string &name);
    static PngData readCubeTexture(const std::string &name);
private:
    static AAssetManager* aAssetManager;
    static std::vector<char> readFile(const std::string& name);
    static std::string readString(const std::string& name);
    static void computeTangent(ObjData& objData);
};

#endif // OPENGLES_ASSET_H
