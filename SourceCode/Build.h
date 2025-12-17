#pragma once

class Player;


//追加効果(ビルド)の基底クラス
class Build
{
public:
	virtual ~Build() = default;

	virtual void Update(Player& p) {}

	//ビルドフラグ
	static bool extraJump;

	//中身
	virtual int AddMaxJump() const { return 0; }

};


//ジャンプ追加
class ExtraJump : public Build
{
public:
	int AddMaxJump() const;
};