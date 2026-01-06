#include "SceneMap.h"
#include <cmath>

////カメラ
//float Map::calcCamera(Tile& tile)
//{
//	VECTOR2 locatePos = { SCREEN_W * 0.3, SCREEN_H * 0.5 };	//持ってきたいポジション
//	VECTOR2 dist = locatePos - tile.getWorldPos();
//	speed = -8;
//
//	float len = sqrt(dist.x * dist.x + dist.y * dist.y);
//	normalized = { dist.x / len, dist.y / len };
//	return len;
//	//tile.setLocalPos();
//}
//
//void Map::updateTile(Tile& tile, float len)
//{
//	float friction = 0.5f;
//	speed += friction;
//	VECTOR2 velocity = normalized;
//	tile.addWorldPos(velocity * speed);
//}

