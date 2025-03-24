#include "texturesManager.hpp"
#include <stdexcept>

TextureManager::~TextureManager()
{
    UnloadAllTextures();
}

void TextureManager::LoadTexture(const std::string &key, const std::string &filePath)
{
    if (textures.find(key) != textures.end())
        return; // Texture already loaded

    Image img = LoadImage(filePath.c_str());
    textures[key] = LoadTextureFromImage(img);
    UnloadImage(img);
}

Texture2D TextureManager::GetTexture(const std::string &key) const
{
    auto it = textures.find(key);
    if (it == textures.end())
        throw std::runtime_error("Texture not found: " + key);
    return it->second;
}

void TextureManager::UnloadAllTextures()
{
    for (auto &pair : textures)
    {
        UnloadTexture(pair.second);
    }
    textures.clear();
}