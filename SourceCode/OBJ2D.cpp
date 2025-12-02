#include"all.h"
#include<cmath>
#include<algorithm>
using namespace std;


bool OBJ2D::animeUpdate(int animeNo, int total, int frame, bool loop)
{
	switch (anime_state)
	{
	case 0:
		anime = animeTimer = 0;
		texPos = { 0, animeNo * texSize.y };

		anime_state++;
	case 1:
		anime = animeTimer / frame;
		if (loop)
		{
			if (anime >= total)
			{
				anime = 0;
				animeTimer = 0;
				return true;
			}
		}
		else
		{
			if (anime >= total)
			{
				anime = total - 1;
				return true;    // アニメの終端に達した
			}
		}
		texPos.x = anime * texSize.x;
		++animeTimer;

		return false;           // アニメの終端ではない

	}
}
//当たり判定
bool OBJ2D::hitCheck(OBJ2D& obj,bool bodyOnly)
{
	if (bodyOnly)
	{
		//円だけ書きます
		float dx = (pos.x+bodyOffset.x) - (obj.pos.x+obj.bodyOffset.x);
		float dy = (pos.y+bodyOffset.y) - (obj.pos.y+obj.bodyOffset.y);
		dx *= dx;
		dy *= dy;
		//当たっていたらtrue
		if (dx + dy < (bodyRadius + obj.bodyRadius) * (bodyRadius + obj.bodyRadius))
			return true;
		return false;
	}

	switch (obj.hitPrimitive)
	{
	case circle:		//引数のほうはbodyだけ
	{
		float dx = (pos.x + offset.x) - (obj.pos.x + obj.bodyOffset.x);
		float dy = (pos.y + offset.y) - (obj.pos.y + obj.bodyOffset.y);
		dx *= dx;
		dy *= dy;
		//当たっていたらtrue
		if (dx + dy < (radius + obj.bodyRadius) * (radius + obj.bodyRadius))
			return true;
		return false;
	}
	break;

	case rect:
	{
		// 矩形の左上と右下を求める 基準点真ん中
		float left = obj.pos.x - obj.pivot.x + offset.x;
		float top = obj.pos.y - obj.pivot.y + offset.y;
		float right = left + obj.texSize.x;
		float bottom = top + obj.texSize.y;

		//円の中心と一番近い線の場所を探す
		VECTOR2 nearPoint;
		nearPoint.x = max(left, min(pos.x, right));
		nearPoint.y = max(top, min(pos.y, bottom));

		//その点と円の中心の距離
		float dx = pos.x - nearPoint.x;
		float dy = pos.y - nearPoint.y;
		float kyori = dx * dx + dy * dy;

		//距離が半径より近ければ当たり
		return kyori <= radius * radius;
	}
	break;

	case line:
	{
		//円と線
		//線のベクトル
		VECTOR2 ab = { obj.texSize.x - obj.pos.x,obj.texSize.y - obj.pos.y };

		//円の中心からAまでのベクトル（Aが線の左端）
		VECTOR2 ac = { pos.x - obj.pos.x,pos.y - obj.pos.y };

		//円から垂線引いた点が線分のどこに行くか　内積を使って求める
		float line = ab.x * ab.x + ab.y * ab.y;
		float t = (ac.x * ab.x + ac.y * ab.y) / line;

		//線分の範囲外なら端にする
		t = max(0.0f, min(1.0f, t));

		//線分上の最近点	線からどれくらいの場所か
		VECTOR2 nearPoint = { obj.pos.x + ab.x * t,obj.pos.y + ab.y * t };

		//矩形と同じ
		float dx = pos.x - nearPoint.x;
		float dy = pos.y - nearPoint.y;
		float kyori = dx * dx + dy * dy;

		//距離が半径より近ければ当たり
		return kyori <= radius * radius;
	}
	break;
	}

}

//カメラ込み
//当たり判定
bool OBJ2D::hitCheck(OBJ2D& obj, bool bodyOnly,Camera & camera)
{
	screenPos = camera.ZoomScreen(pos);
	if (bodyOnly)
	{
		//円だけ書きます
		float dx = (screenPos.x + bodyOffset.x) - (obj.screenPos.x + obj.bodyOffset.x);
		float dy = (screenPos.y + bodyOffset.y) - (obj.screenPos.y + obj.bodyOffset.y);
		dx *= dx;
		dy *= dy;
		//当たっていたらtrue
		if (dx + dy < (bodyRadius + obj.bodyRadius) * (bodyRadius + obj.bodyRadius))
			return true;
		return false;
	}

	switch (obj.hitPrimitive)
	{
	case circle:		//引数のほうはbodyだけ
	{
		float dx = (screenPos.x + offset.x) - (obj.screenPos.x + obj.bodyOffset.x);
		float dy = (screenPos.y + offset.y) - (obj.screenPos.y + obj.bodyOffset.y);
		dx *= dx;
		dy *= dy;
		//当たっていたらtrue
		if (dx + dy < (radius + obj.bodyRadius) * (radius + obj.bodyRadius))
			return true;
		return false;
	}
	break;

	case rect:
	{
		// 矩形の左上と右下を求める 基準点真ん中
		float left = obj.pos.x - obj.pivot.x + offset.x;
		float top = obj.pos.y - obj.pivot.y + offset.y;
		float right = left + obj.texSize.x;
		float bottom = top + obj.texSize.y;

		//円の中心と一番近い線の場所を探す
		VECTOR2 nearPoint;
		nearPoint.x = max(left, min(pos.x, right));
		nearPoint.y = max(top, min(pos.y, bottom));

		//その点と円の中心の距離
		float dx = pos.x - nearPoint.x;
		float dy = pos.y - nearPoint.y;
		float kyori = dx * dx + dy * dy;

		//距離が半径より近ければ当たり
		return kyori <= radius * radius;
	}
	break;

	case line:
	{
		//円と線
		//線のベクトル
		VECTOR2 ab = { obj.texSize.x - obj.pos.x,obj.texSize.y - obj.pos.y };

		//円の中心からAまでのベクトル（Aが線の左端）
		VECTOR2 ac = { pos.x - obj.pos.x,pos.y - obj.pos.y };

		//円から垂線引いた点が線分のどこに行くか　内積を使って求める
		float line = ab.x * ab.x + ab.y * ab.y;
		float t = (ac.x * ab.x + ac.y * ab.y) / line;

		//線分の範囲外なら端にする
		t = max(0.0f, min(1.0f, t));

		//線分上の最近点	線からどれくらいの場所か
		VECTOR2 nearPoint = { obj.pos.x + ab.x * t,obj.pos.y + ab.y * t };

		//矩形と同じ
		float dx = pos.x - nearPoint.x;
		float dy = pos.y - nearPoint.y;
		float kyori = dx * dx + dy * dy;

		//距離が半径より近ければ当たり
		return kyori <= radius * radius;
	}
	break;
	}

}


//当たり判定描画　
void OBJ2D::hitAreaRender()
{
	switch (hitPrimitive)
	{
	case circle:
		primitive::circle(pos.x + offset.x, pos.y + offset.y, radius, 1,1, angle, 1, 0, 0, 0.3f);
		break;

	case rect:
		primitive::rect(pos.x + offset.x, pos.y + offset.y, texSize.x + offset.x, texSize.y + offset.y, pivot.x, pivot.y, angle, 1, 0, 0, 0.3f);
		break;

	case line:
		primitive::line(pos.x + offset.x, pos.y + offset.y, texSize.x + offset.x, texSize.y + offset.y, 1, 0, 0, 0.3f);
		break;
	}
}
	//上と下のスケールのところradiusがスケールの分増えている値なのでスケールは常に１固定　増やすと二重にスケールがかかる
void OBJ2D::bodyHitAreaRender()
{
	//円だけ
	primitive::circle(pos.x + bodyOffset.x, pos.y + bodyOffset.y, bodyRadius,1,1, angle, 0, 1, 0, 0.3f);
}


//カメラ判定あり版
void OBJ2D::hitAreaRender(Camera& camera)
{
	screenPos = camera.ZoomScreen(pos);
	switch (hitPrimitive)
	{
	case circle:
		primitive::circle(screenPos.x + offset.x, screenPos.y + offset.y, radius, 1, 1, angle, 1, 0, 0, 0.3f);
		break;

	case rect:
		primitive::rect(pos.x + offset.x, pos.y + offset.y, texSize.x + offset.x, texSize.y + offset.y, pivot.x, pivot.y, angle, 1, 0, 0, 0.3f);
		break;

	case line:
		primitive::line(pos.x + offset.x, pos.y + offset.y, texSize.x + offset.x, texSize.y + offset.y, 1, 0, 0, 0.3f);
		break;
	}
}
//上と下のスケールのところradiusがスケールの分増えている値なのでスケールは常に１固定　増やすと二重にスケールがかかる
void OBJ2D::bodyHitAreaRender(Camera& camera)
{
	screenPos = camera.ZoomScreen(pos);
	//円だけ
	primitive::circle(screenPos.x + bodyOffset.x, screenPos.y + bodyOffset.y, bodyRadius, 1, 1, angle, 0, 1, 0, 0.3f);
}


//bool CHARACTER::hitCheck(OBJ2D& obj,bool bodyOnly)
//{
//	//距離が届いていない場合
//
//	float radiusCopy = radius;	//同じ関数使いまわすためにradiusの値を変える
//	radius = eyeRadius;
//	if (!OBJ2D::hitCheck(obj,true))
//	{
//		radius = radiusCopy;
//		return false;
//	}
//
//	radius = radiusCopy;
//	//キャラの周りに当たったら
//	if (OBJ2D::hitCheck(obj,false))
//		return true;
//
//	////相手へのベクトル
//	//VECTOR2 objP = obj.getPos();
//	//VECTOR2 aite = { (objP.x + obj.getOffset().x) - (pos.x + offset.x),
//	//				(objP.y  + obj.getOffset().y ) - (pos.y + offset.y) };
//
//	// 相手へのベクトルを「最近接点」から求める処理を追加
//	VECTOR2 objP = obj.getPos();
//	VECTOR2 diff = { objP.x - pos.x,
//					 objP.y - pos.y };
//
//	float dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
//	if (dist < 1e-6f) return true;
//
//	// 正規化
//	diff.x /= dist;
//	diff.y /= dist;
//
//	// プレイヤー円の最近接点を計算
//	VECTOR2 nearest = { (objP.x) - diff.x ,
//						(objP.y) - diff.y };
//
//	// 敵から最近接点へのベクトルを aite に置き換える
//	VECTOR2 aite = { nearest.x - (pos.x),
//					 nearest.y - (pos.y) };
//
//	//相手のベクトルの正規化
//	float len = sqrtf(aite.x * aite.x + aite.y * aite.y);
//	if (len < 1e-6f)return true;	//０除算を避けるためここでリターン
//	aite.x /= len;
//	aite.y /= len;
//
//	//自キャラの方向ベクトル
//	VECTOR2 my;
//	my.x = sinf(angle);
//	my.y = -cosf(angle);
//
//	////お試し ベクトル描画
//	//VECTOR2 center = { pos.x+offset.x , pos.y+offset.y  };
//	//primitive::line(center.x, center.y, center.x + my.x * 50, center.y + my.y * 50, 0, 1, 0, 1, 2); // 自分の向きベクトル
//	//primitive::line(center.x, center.y, center.x + aite.x * 50, center.y + aite.y * 50, 1, 1, 0, 1, 2); // 相手方向ベクトル
//
//
//	float naiseki = aite.x * my.x + aite.y * my.y;
//
//
//	float viewAngle = ToRadian(30.0f);				 // 前方30度（ラジアン）
//	float edgeAngle = asinf(obj.getRadius() / dist); // 円の端ぶんの補正角度
//	float limit = cosf(viewAngle + edgeAngle);		 // 内積比較用にcos値へ変換
//
//	if (naiseki > limit)
//
//	{
//		//前方30度で当たっている
//		return true;
//	}
//	else
//	{
//		//後方で当たっている
//		return false;
//	}
//}

//当たり判定の描画ワロタ
void OBJ2D::hitAreaRender(int f)
{
	//視界の描画
	float fov = ToRadian(60.0f);
	int steps = 60;
	float start = angle - fov / 2;
	float end = angle + fov / 2;

	for (int i = 0;i <= steps;i++)
	{
		float t = (float)i / steps;
		float theta = start + (end - start) * t;



		//原点終点
		VECTOR2 endPoint = { pos.x + offset.x + eyeRadius * sinf(theta),
						pos.y + offset.y + eyeRadius * -cosf(theta) };

		primitive::line(pos.x + offset.x, pos.y + offset.y, endPoint.x, endPoint.y, 1, 0, 0, 0.3f, 2.0f);
	}

	//キャラ本体の描画
	primitive::circle(pos.x, pos.y, radius, scale.x, scale.y, angle, 1, 0, 0, 0.3f);
}


//p1がプレイヤー
bool hitCheck(CHARACTER* p1, CHARACTER* p2,int num)
{
	switch (num)
	{
	case JUDGE::attackPlayer:		return p1->hitCheck(*p2,false);	//自分から敵の当たり判定
	case JUDGE::attackEnemy:		return p2->hitCheck(*p1, false);//敵から自分の当たり判定
	case JUDGE::bodyOnly:		return p1->hitCheck(*p2, true);	//体だけ
	}
	return false;//引数ミスってるとき
}

//カメラあり版
bool camera_hitCheck(CHARACTER* p1, CHARACTER* p2, int num,Camera& camera)
{
	switch (num)
	{
	case JUDGE::attackPlayer:		
		if (p2->getMutekiTimer())return false;
		return p1->hitCheck(*p2, false, camera);	//自分から敵の当たり判定
	case JUDGE::attackEnemy:		if (p1->getMutekiTimer())return false;   return p2->hitCheck(*p1, false,camera);//敵から自分の当たり判定
	case JUDGE::bodyOnly:		return p1->hitCheck(*p2, true,camera);	//体だけ
	}
	return false;//引数ミスってるとき
}

//スケール反転
void ScaleRebarse(CHARACTER* p1,CHARACTER* p2)
{
	if (p1->getPos().x < p2->getPos().x)
	{
		if (p1->getScale().x < 0 && p2->getScale().x < 0)
		{
			p1->setScale({ -p1->getScale().x, p1->getScale().y });
			p2->setScale({ -p2->getScale().x,p2->getScale().y });
		}
	}
	else if (p1->getScale().x > 0 && p2->getScale().x > 0)
	{
		p1->setScale({ -p1->getScale().x, p1->getScale().y });
		p2->setScale({ -p2->getScale().x, p2->getScale().y });
	}
}
void setPos(CHARACTER* p1, CHARACTER* p2)//p1がプレイやー
{
	p1->setp((p1->getPos().x - p1->getSX())+p2->getSX());
}

void CHARACTER::hitEfect()
{
	static int timer = 0;

	if (efectOn)
	{
		if (timer > 60)
		{
			timer = 0;
			efectOn = false;
			color.w = 1;
			return;
		}

		if (timer % 5 == 0)
		{
			if (color.w > 0.5)	color.w = 0.5f;
			else color.w = 1;
		}
		timer++;
	}
}