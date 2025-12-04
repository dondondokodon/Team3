#pragma once
//シーンインターフェイス
class ISCENE
{
protected:
	int timer=0;
	int state=0;
	// フェード用
	float fadeAlpha = 0.0f;
	bool isFading = false;    // フェード中か
	bool fadeOut = true;
public:		   
	static int curScene;
	static int nextScene;
	virtual ~ISCENE(){}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void init() = 0;
	virtual void deinit() = 0;

	virtual void deleteSprite() = 0;

	void startFade(int scene)
	{
		nextScene = scene;
		isFading = true;
		fadeOut = true;
		fadeAlpha = 0.0f;
	}

	void updateFade()
	{
		if (!isFading) return;

		if (fadeOut)
		{
			fadeAlpha += 0.02f; // 調整可能
			if (fadeAlpha >= 1.0f)
			{
				fadeAlpha = 1.0f;
				fadeOut = false;
				// シーン切替
				curScene = nextScene;
			}
		}
		else
		{
			fadeAlpha -= 0.02f;
			if (fadeAlpha <= 0.0f)
			{
				fadeAlpha = 0.0f;
				isFading = false;
			}
		}
	}

	void renderFade();

	void startFadeIn()
	{
		isFading = true;
		fadeOut = false;  // フェードインにする
		fadeAlpha = 1.0f;
	}
};


