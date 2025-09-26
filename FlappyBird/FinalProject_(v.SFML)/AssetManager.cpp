#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
using namespace std;
using namespace sf;
namespace ASU
{
	void AssetManager::LoadTexture(string name, string fileName)
	{
		Texture tex;

		if (tex.loadFromFile(fileName))
		{
			this->_textures[name] = tex;
		}
	}

	Texture& AssetManager::GetTexture(string name)
	{
		return this->_textures.at(name);
	}

	void AssetManager::LoadFont(string name, string fileName)
	{
		Font font;

		if (font.loadFromFile(fileName))
		{
			this->_fonts[name] = font;
		}
	}

	Font& AssetManager::GetFont(string name)
	{
		return this->_fonts.at(name);
	}
}