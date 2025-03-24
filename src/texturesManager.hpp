#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

class TextureManager
{
  public:
    ~TextureManager();
    void LoadTexture(const std::string &key, const std::string &filePath);
    Texture2D GetTexture(const std::string &key) const;
    void UnloadAllTextures();

  private:
    std::unordered_map<std::string, Texture2D> textures;
};