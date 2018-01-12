#include "asset.h"

AAssetManager* AssetManager::aAssetManager = nullptr;

void AssetManager::set(const AAssetManager* aAssetManager) {
    LOG_PRINT_DEBUG("Set asset manager");

    // set asset manager
    AssetManager::aAssetManager = (AAssetManager*) aAssetManager;
}

std::vector<char> AssetManager::readFile(const std::string& name) {
    LOG_PRINT_DEBUG("Read file: %s", name.c_str());

    // check asset manager
    if (!aAssetManager) LOG_PRINT_ERROR("Asset manager was not set");

    // open asset
    AAsset* aAsset = AAssetManager_open(aAssetManager, name.c_str(), AASSET_MODE_UNKNOWN);
    if (!aAsset) LOG_PRINT_ERROR("Fail to read file: %s", name.c_str());

    // read asset
    std::vector<char> buffer;
    size_t length = (size_t) AAsset_getLength(aAsset);
    buffer.resize(length);
    AAsset_read(aAsset, buffer.data(), length);

    // close asset
    AAsset_close(aAsset);

    // return buffer(file contents)
    return buffer;
}

std::string AssetManager::readString(const std::string& name) {
    // read file with null terminator
    std::vector<char> file = readFile(name);

    // convert to string
    std::string text(file.data(), file.size());
    LOG_PRINT_DEBUG("Part of text: %s", text.substr(0, 30).c_str());

    // return string
    return text;
}

std::string AssetManager::readShader(const std::string& name) {
    // read string from .glsl file
    return readString("shader/" + name + ".glsl");
}

ObjData AssetManager::readObject(const std::string &name) {
    // read text from .obj file
    std::stringstream text(readString("object/" + name + ".obj"));
    std::string line;

    // string of regular expression
    const std::string strFloat(R"(\s+([-+]?[0-9]*\.?[0-9]+))");
    const std::string strTuple(R"(\s+(\d+/\d+/\d+))");

    // string match and regular expressions
    std::smatch matchText;
    const std::regex regexPos("v" + strFloat + strFloat + strFloat);
    const std::regex regexNor("vn" + strFloat + strFloat + strFloat);
    const std::regex regexTex("vt" + strFloat + strFloat + strFloat);
    const std::regex regexQuad("f" + strTuple + strTuple + strTuple + strTuple);
    const std::regex regexTriangle("f" + strTuple + strTuple + strTuple);

    // list of attributes, map of face
    std::vector<glm::vec3> posList;
    std::vector<glm::vec3> norList;
    std::vector<glm::vec2> texList;
    std::unordered_map<std::string, Index> faceMap;

    // create new .obj data
    ObjData objData = ObjData();

    // parsing text
    LOG_PRINT_DEBUG("Parsing .obj file");
    while (getline(text, line, '\n')) {
        if (regex_search(line, matchText, regexPos)) { // v: position
            posList.push_back(glm::vec3(atof(matchText[1].str().c_str()),
                                        atof(matchText[2].str().c_str()),
                                        atof(matchText[3].str().c_str())));
        } else if (regex_search(line, matchText, regexNor)) { // vn: normal
            norList.push_back(glm::vec3(atof(matchText[1].str().c_str()),
                                        atof(matchText[2].str().c_str()),
                                        atof(matchText[3].str().c_str())));
        } else if (regex_search(line, matchText, regexTex)) { // vt: texture coordinates
            texList.push_back(glm::vec2(atof(matchText[1].str().c_str()),
                                        atof(matchText[2].str().c_str())));
        } else if (regex_search(line, matchText, regexQuad)) { // f: quad face
            for (int i = 1; i <= 4; i++) {
                const std::string key = matchText[i].str();

                if (faceMap.find(key) == faceMap.end()) {
                    faceMap[key] = (Index) faceMap.size();

                    // parsing tuple
                    std::smatch matchKey;
                    std::regex regexKey(R"((\d+)/(\d+)/(\d+))");
                    std::regex_match(key, matchKey, regexKey);

                    // create new vertex
                    Vertex vertex;
                    vertex.pos = posList[atoi(matchKey[1].str().c_str()) - 1];
                    vertex.nor = norList[atoi(matchKey[3].str().c_str()) - 1];
                    vertex.tex = texList[atoi(matchKey[2].str().c_str()) - 1];
                    objData.vertices.push_back(vertex);
                }

                // add new index
                objData.indices.push_back(faceMap[key]);
            }
        } else if (regex_search(line, matchText, regexTriangle)) { // f: triangle face
            for (int i = 1; i <= 3; i++) {
                const std::string key = matchText[i].str();

                if (faceMap.find(key) == faceMap.end()) {
                    faceMap[key] = (Index) faceMap.size();

                    // parsing tuple
                    std::smatch matchKey;
                    std::regex regexKey(R"((\d+)/(\d+)/(\d+))");
                    std::regex_match(key, matchKey, regexKey);

                    // create new vertex
                    Vertex vertex;
                    vertex.pos = posList[atoi(matchKey[1].str().c_str()) - 1];
                    vertex.nor = norList[atoi(matchKey[3].str().c_str()) - 1];
                    vertex.tex = texList[atoi(matchKey[2].str().c_str()) - 1];
                    objData.vertices.push_back(vertex);
                }

                // add new index
                objData.indices.push_back(faceMap[key]);
            }
        }
    }

    // compute tangent
    computeTangent(objData);

    // return .obj data
    LOG_PRINT_DEBUG("Vertex count: %u, Index count: %u",
                    (unsigned int) objData.vertices.size(), (unsigned int) objData.indices.size());
    return objData;
}

ObjData AssetManager::readBinaryObject(const std::string &name) {
    // read .bin file
    std::vector<char> file = readFile("object/" + name + ".bin");
    char* filePointer = file.data();

    // create new .obj data
    ObjData objData = ObjData();

    // get metadata (counts)
    unsigned int vertexCount = *((unsigned int*) filePointer);
    filePointer += sizeof(unsigned int);
    unsigned int indexCount = *((unsigned int*) filePointer);
    filePointer += sizeof(unsigned int);

    // get vertices data
    objData.vertices.resize(vertexCount);
    memcpy(objData.vertices.data(), filePointer, vertexCount * sizeof(Vertex));
    filePointer += vertexCount * sizeof(Vertex);

    // get indices data
    objData.indices.resize(indexCount);
    memcpy(objData.indices.data(), filePointer, indexCount * sizeof(Index));
    filePointer += indexCount * sizeof(Index);

    // return .obj data
    LOG_PRINT_DEBUG("Vertex count: %u, Index count: %u",
                    (unsigned int) objData.vertices.size(), (unsigned int) objData.indices.size());
    return objData;
}

PngData AssetManager::readTexture(const std::string &name) {
    // read .png file
    std::vector<char> file = readFile("texture/" + name + ".png");

    // decode using picoPNG
    LOG_PRINT_DEBUG("Decoding .png file");
    std::vector<unsigned char> image;
    unsigned long width;
    unsigned long height;
    PicoPNG::decodePNG(image, width, height, (const unsigned char *) file.data(), file.size());

    // create new data
    PngData pngData = PngData();
    pngData.texels.resize(width * height);
    for (unsigned long s = 0; s < width; s++) {
        for (unsigned long t = 0; t < height; t++) {
            Texel& texel = pngData.texels[s + (height - t - 1) * width]; // t-axis flip
            texel.r = image[0 + s * 4 + t * width * 4];
            texel.g = image[1 + s * 4 + t * width * 4];
            texel.b = image[2 + s * 4 + t * width * 4];
            texel.a = image[3 + s * 4 + t * width * 4];
        }
    }
    pngData.width = (GLsizei) width;
    pngData.height = (GLsizei) height;

    // return .png data
    LOG_PRINT_DEBUG("First pixel: %hhx%hhx%hhx%hhx, Second pixel: %hhx%hhx%hhx%hhx",
                    pngData.texels[0].r, pngData.texels[0].g, pngData.texels[0].b, pngData.texels[0].a,
                    pngData.texels[1].r, pngData.texels[1].g, pngData.texels[1].b, pngData.texels[1].a);
    return pngData;
}

PngData AssetManager::readCubeTexture(const std::string &name) {
    // read six .png data
    const PngData posX = readTexture(name + "_px");
    const PngData negX = readTexture(name + "_nx");
    const PngData posY = readTexture(name + "_py");
    const PngData negY = readTexture(name + "_ny");
    const PngData posZ = readTexture(name + "_pz");
    const PngData negZ = readTexture(name + "_nz");

    // create new data
    PngData cubeMapData = PngData();
    cubeMapData.width = posX.width;
    cubeMapData.height = posX.height;

    // copy and concatenate data
    cubeMapData.texels.reserve((unsigned long) (6 * cubeMapData.width * cubeMapData.height));
    cubeMapData.texels.insert(cubeMapData.texels.end(), posX.texels.begin(), posX.texels.end());
    cubeMapData.texels.insert(cubeMapData.texels.end(), negX.texels.begin(), negX.texels.end());
    cubeMapData.texels.insert(cubeMapData.texels.end(), posY.texels.begin(), posY.texels.end());
    cubeMapData.texels.insert(cubeMapData.texels.end(), negY.texels.begin(), negY.texels.end());
    cubeMapData.texels.insert(cubeMapData.texels.end(), posZ.texels.begin(), posZ.texels.end());
    cubeMapData.texels.insert(cubeMapData.texels.end(), negZ.texels.begin(), negZ.texels.end());

    // return cube map data
    return cubeMapData;
}

void AssetManager::computeTangent(ObjData &objData) {
    LOG_PRINT_DEBUG("Compute tangent");

    // get vertices and indices
    std::vector<Vertex>& vertices = objData.vertices;
    std::vector<Index>& indices = objData.indices;

    // initialize tangent to zero vector
    for (unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i].tan = glm::vec3(0.0f);
    }

    // calculate tangent
    for (unsigned int i = 0; i < indices.size(); i += 3) {

        // points in triangle
        Vertex& p0 = vertices[indices[i + 0]];
        Vertex& p1 = vertices[indices[i + 1]];
        Vertex& p2 = vertices[indices[i + 2]];

        // edge vector
        const glm::vec3 p10 = p1.pos - p0.pos;
        const glm::vec3 p20 = p2.pos - p0.pos;

        // texture coordinates difference
        const float s10 = p1.tex.s - p0.tex.s;
        const float t10 = p1.tex.t - p0.tex.t;
        const float s20 = p2.tex.s - p0.tex.s;
        const float t20 = p2.tex.t - p0.tex.t;

        // calculate tangent
        const glm::vec3 tan = (t20 * p10 - t10 * p20) / (s10 * t20 - s20 * t10);

        // sum tangent
        p0.tan += tan;
        p1.tan += tan;
        p2.tan += tan;
    }

    // normalize (average) tangent
    for (unsigned int i = 0; i < vertices.size(); i++) {
        vertices[i].tan = normalize(vertices[i].tan);
    }
}
