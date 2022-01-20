#pragma once

#include "Graphics.h"
#include "Surface.h"
#include "Codex.h"
#include <vector>
#include <random>
#include "Boundary.h"

class Background
{
public:
	Background(const RectI& bgRegion, int gridWidth, int gridHeight, const std::string& map)
		:
		pTilesetSurface(Codex<Surface>::Retrieve(L"Images\\Tas.bmp")),
		origin(bgRegion.TopLeft()),
		gridWidth(gridWidth),
		gridHeight(gridHeight)
	{
		// generate tile rects
		for (int n = 0; n < nTiles; n++)
		{
			tileRects.emplace_back(
				Vei2{ tileSize,0 } *n, tileSize, tileSize
			);
		}
		// reserve tile map space
		tiles.reserve(gridWidth * gridHeight);
		// load tile grid from map string (B is 0, C is 1 A is -1 etc.)
		{
			auto mi = map.cbegin();
			for (int n = 0; n < gridWidth * gridHeight; n++, ++mi)
			{
				tiles.push_back(*mi - 'B');
				
			}
		}
	}
	void Draw(Graphics& gfx) const
	{
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				const int index = GetTileAt(x, y);
				// negative values are skipped (blank tiles)
				if (index >= 0)
				{
					gfx.DrawSprite(x * tileSize + origin.x, y * tileSize + origin.y,
						tileRects[index], *pTilesetSurface, SpriteEffect::Copy{}
					);
					
				}
			}
		}
	}
	void SetHitBox() {
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				const int index = GetTileAt(x, y);
				// negative values are skipped (blank tiles)
				if (index >= 0)
				{
					TileHitBoxs.push_back(RectF(x * tileSize + origin.x, x * tileSize + origin.x + 32, y * tileSize + origin.y, y * tileSize + origin.y+30));
				}
			}
		}
	}
	std::vector<RectF> GetHitBox() {
		return TileHitBoxs;
	}
private:
	int GetTileAt(int x, int y) const
	{
		return tiles[y * gridWidth + x];
	}

private:
	// tileset image for background
	const Surface* pTilesetSurface;
	// top left corner of background grid
	std::vector<RectF> TileHitBoxs;
	Vei2 origin;
	// vector of tile rects
	std::vector<RectI> tileRects;
	// grid of tiles (indices into the tileRect vector)
	std::vector<int> tiles;
	// number of tiles in set
	int nTiles = 1;
	// tile dimensions in pixels
	int tileSize = 32;
	// grid dimensions in tiles
	int gridWidth;
	int gridHeight;
};