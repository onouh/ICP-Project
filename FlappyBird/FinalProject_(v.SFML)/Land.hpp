#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

using namespace std;
using namespace sf;
namespace ASU
{
	class Land
	{
	public:
		Land(GameDataRef data);

		void MoveLand(float dt);
		void DrawLand();

		const vector<Sprite>& GetSprites() const;

	private:
		GameDataRef _data;

		vector<Sprite>_landSprites;

	};
}