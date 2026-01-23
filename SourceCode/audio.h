#pragma once

//ŠÖ”
void audio_init();
void audio_deinit();

enum SE
{
	coinGet,		//“ü‚ê‚½
	P_jumpGround,	//“ü‚ê‚½
	P_jump,			//“ü‚ê‚½
	P_jump2,
	P_doge,			//“ü‚ê‚½
	P_lightA,		//“ü‚ê‚½
	P_hit,			//“ü‚ê‚½
	P_HeavyA,		//“ü‚ê‚½
	B_jumpA1,		//“ü‚ê‚½
	B_jumpA2,
	B_Jump,			//“ü‚ê‚½
	B_tailA,		//“ü‚ê‚½
	B_hit,			//“ü‚ê‚½
	B_Shout,		//“ü‚ê‚½H	
	titlePic,
	tranpFly,		//“ü‚ê‚½H
	buttonPic,
	result1,
	result3,
	buy,			//“ü‚ê‚½H
	zako2_A,		//“ü‚ê‚½
	zakoFlyA,		//“ü‚ê‚½
	pic,
	bigAttack,		//“ü‚ê‚½
	score,
};

enum BGM
{
	main = score + 1,
	battle,
	result
};
