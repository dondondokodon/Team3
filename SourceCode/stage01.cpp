#include "stage.h"
#include"ImageManager.h"
#include "Player.h"

void Stage01::init()
{
	//背景（グラデーション）
	back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billBack);
	back.pos = { 0,0 };
	back.scale = { 1,1 };
	back.texPos = { 0,0 };
	back.texSize = { 1280 * 2, 720 };
	back.pivot = { 0,0 };
	back.color = { 1,1,1,1 };
	back.speed = { 0,0 };
	back.offset = { 0,0 };
	back.angle = 0;
	back.act = 0;
	back.timer = 0;
	back.anime = 0;
	back.animeTimer = 0;
	back.anime_state = 0;
	back.radius = 0;

	//遠々背景
	back_back.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billBackBack);
	back_back.pos = { 0,100 };
	back_back.scale = { 1,1 };
	back_back.texPos = { 0,0 };
	back_back.texSize = { 2560 * 2, 720 };
	back_back.pivot = { 0,0 };
	back_back.color = { 1,1,1,1 };
	back_back.speed = { 0.1,0.1 };
	back_back.offset = { 0,0 };
	back_back.angle = 0;
	back_back.act = 0;
	back_back.timer = 0;
	back_back.anime = 0;
	back_back.animeTimer = 0;
	back_back.anime_state = 0;
	back_back.radius = 0;

	//中背景
	middle.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billMiddle);
	middle.pos = { 0,100 };
	middle.scale = { 1,1 };
	middle.texPos = { 0,0 };
	middle.texSize = { 2560 * 2, 720 };
	middle.pivot = { 0,0 };
	middle.color = { 1,1,1,1 };
	middle.speed = { 0.3,0.3 };
	middle.offset = { 0,0 };
	middle.angle = 0;
	middle.act = 0;
	middle.timer = 0;
	middle.anime = 0;
	middle.animeTimer = 0;
	middle.anime_state = 0;
	middle.radius = 0;

	//近背景
	front.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billFront);
	front.pos = { 0,0 };
	front.scale = { 1,1 };
	front.texPos = { 0,0 };
	front.texSize = { 2560 * 2, 720 };
	front.pivot = { 0,0 };
	front.color = { 1,1,1,1 };
	front.speed = { 0.5,0.5 };
	front.offset = { 0,0 };
	front.angle = 0;
	front.act = 0;
	front.timer = 0;
	front.anime = 0;
	front.animeTimer = 0;
	front.anime_state = 0;
	front.radius = 0;


	//地面
	ground.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::billGround);
	ground.pos = { 0,0 };
	ground.scale = { 1,1 };
	ground.texPos = { 0,0 };
	ground.texSize = { 1280 * 2+300, 720 };
	ground.pivot = { 0,0 };
	ground.color = { 1,1,1,1 };
	ground.speed = { 1,0.5 };
	ground.offset = { 0,0 };
	ground.angle = 0;
	ground.act = 0;
	ground.timer = 0;
	ground.anime = 0;
	ground.animeTimer = 0;
	ground.anime_state = 0;
	ground.radius = 0;

	//足場
	footings.clear();	//一応クリア

	StageLayer f;

	f.spr = ImageManager::Instance().getSprite(ImageManager::SpriteNum::footing);
	f.pos = { 500,500 };
	f.scale = { 1,1 };
	f.texPos = { 0,0 };
	f.texSize = { 240, 50 };
	f.pivot = { f.texSize.x*0.5f,f.texSize.y * 0.5f };
	f.color = { 1,1,1,1 };
	f.speed = { 1,1 };
	f.offset = { 0,0 };
	f.angle = 0;
	f.act = 0;
	f.timer = 0;
	f.anime = 0;
	f.animeTimer = 0;
	f.anime_state = 0;
	f.radius = 0;

	footings.push_back(f);
}


void Stage01::update()
{
	back.pos.x += -0.2f;
	//middle.pos.x += -0.5f;
	//front.pos.x += -0.7f;

	if (back.pos.x <= -1280)
		back.pos.x = 0;

}

void Stage01::deinit()
{
	footings.clear();
}

//ステージのrender１も２も使ってへん
void Stage01::render()
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);	
	//back.render();
	//back_back.render();
	//middle.render();
	//front.render();
	//ground.render();
}

void Stage01::cameraRender(CAMERA camera)
{
	GameLib::setBlendMode(GameLib::Blender::BS_ALPHA);
	back.render();
	back_back.cameraRender(camera);
	middle.cameraRender(camera);
	front. cameraRender(camera);
	ground.cameraRender(camera);
	for (auto& footing : footings)
	footing.cameraRender(camera);	//こいつに当たり判定をつけないといけない
}

// Stageのもの
void Stage::checkFootingCollision(Player& character)
{
	// まず毎フレームfalseにしておく（地面や他の足場で上書きされる前提）
	character.setIsGround(false);
	bool onAnyFooting = false;
	for (auto& footing : footings)
	{
		if (&footing == character.getBeforeLayer() &&
			character.getSpeed().y > 3)
		{
			onAnyFooting = true;
			continue;	// 前回乗ってた足場は無視する
		}

		// 足場の中心座標・サイズ		マジックナンバーはマジで適当な調整
		float fx = footing.pos.x - 12.5f;
		float fy = footing.pos.y;
		float fw = footing.texSize.x * footing.scale.x;
		float fh = footing.texSize.y * footing.scale.y - 80;

		// 足場の上端（pivot中心なら）
		float footingTop = fy - fh * 0.5f;

		// キャラの足元Y
		float footY = character.getPos().y + character.getPivot().y * character.getScale().y;

		// キャラの横幅
		float cw = character.getTexSize().x * character.getScale().x * 0.3f; // 必要なら調整
		float cx = character.getPos().x;
		float charLeft = cx - cw * 0.5f;
		float charRight = cx + cw * 0.5f;

		// 横方向の重なり
		bool isOverlapX = (charRight > fx - fw * 0.5f) && (charLeft < fx + fw * 0.5f);

		// 前フレームの足元Y
		float prevFootY = character.getBeforePos().y + character.getPivot().y * character.getScale().y;
		float deltaY = footY - prevFootY;

		// 足場の上に乗る条件
		bool isOnFooting = isOverlapX && prevFootY <= footingTop && footY >= footingTop && character.getSpeed().y > 2;	//2は小さすぎると横移動だけで乗れるから

		//すでに立っているとき
		bool isStanding =
			isOverlapX &&
			fabs(footY - footingTop) < 1.0f;

		if (isOnFooting||isStanding) {
			// 足場の上に乗る
			character.setBeforeLayer(&footing);
			character.setPos(VECTOR2{ character.getPos().x, footingTop - character.getPivot().y * character.getScale().y });
			float speedX = character.getSpeed().x;
			character.setSpeed(VECTOR2{ speedX, 0 });
			character.setIsGround(true);
			return; // 一つの足場に乗ったら他はチェックしない
		}
	}

	if(!onAnyFooting)
	character.setBeforeLayer(nullptr);
}
