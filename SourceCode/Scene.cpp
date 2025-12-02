#include"all.h"


//スタティック変数の宣言
int ISCENE::curScene = SCENE_NONE;  //現在のシーン
int ISCENE::nextScene = SCENE_TITLE;  //次のシーン


void ISCENE::renderFade()
{
    if (fadeAlpha <= 0.0f) return;

    static std::unique_ptr<GameLib::Sprite>fadeSpr = nullptr;

    if (!fadeSpr)
    {
        fadeSpr.reset(sprite_load(L"./Data/Images/seni.png")); 
    }

    VECTOR2 pos{ 0,0 };
    VECTOR2 scale{ 1920.0f, 1080.0f };
    VECTOR2 texPos{ 0,0 };
    VECTOR2 texSize{ 1,1 };
    VECTOR2 pivot{ 0,0 };
    float angle = 0;
    VECTOR4 color{ 0,0,0,fadeAlpha };

    sprite_render(fadeSpr.get(), pos.x, pos.y, scale.x, scale.y,
        texPos.x, texPos.y, texSize.x, texSize.y,
        pivot.x, pivot.y, angle,
        color.x, color.y, color.z, color.w);
}