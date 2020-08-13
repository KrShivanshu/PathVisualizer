#include "AssetMan.hpp"

Engine::AssetMan::AssetMan() {}
Engine::AssetMan::~AssetMan() {}

void Engine::AssetMan::AddTextures(const string id, const string filepath, bool wantRepeated)
{
	auto texture = make_unique<Texture>();

	if (texture->loadFromFile(filepath))
	{
		texture->setRepeated(wantRepeated);
		_textureMap[id] = move(texture);
	}
}

void Engine::AssetMan::AddFont(const string id, const string filepath)
{
	auto font = make_unique<Font>();
	if (font->loadFromFile(filepath))
	{
		_fontMap[id] = move(font);
	}
}

Texture& Engine::AssetMan::GetTexture(string id)
{
	// TODO: insert return statement here
	return *(_textureMap.at(id).get());
}

Font& Engine::AssetMan::GetFont(string id)
{
	// TODO: insert return statement here
	return *(_fontMap.at(id).get());
}