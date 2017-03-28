#include "stdafx.h"
#include "gameStudy.h"


gameStudy::gameStudy()
{
}


gameStudy::~gameStudy()
{
}

HRESULT gameStudy::init()
{
	gameNode::init(true);
	
	IMAGEMANAGER->addImage("background", "image/background.bmp", 1600, 1100, true, RGB(255, 0, 255));
	
	// mainScene Btn..
	IMAGEMANAGER->addImage("btn_attack", "image/btn_attack.bmp", 105, 105, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_army", "image/btn_army.bmp", 57, 57, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_map_setting", "image/btn_map_setting.bmp", 55, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_mission", "image/btn_mission.bmp", 55, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_setting", "image/btn_setting.bmp", 55, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("money_slot", "image/money_slot.bmp", 200, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_shop", "image/btn_shop.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("worker_slot", "image/worker_slot.bmp", 148, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("unit_make_btn", "image/unit_make_btn.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("upgrade_btn", "image/btn_upgrade.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("info_btn", "image/btn_info.bmp", 100, 100, true, RGB(255, 0, 255));
	

	// mainScene pop
	IMAGEMANAGER->addImage("elixir_pop", "image/elixir_pop.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("money_pop", "image/money_pop.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_collector_pop", "image/gold_collector_pop.bmp", 710, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_collector_pop", "image/elixir_collector_pop.bmp", 710, 540, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("setting_slot", "image/setting_slot.bmp", 475, 300, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_pop", "image/town_hall_pop.bmp", 710, 540, true, RGB(255, 0, 255));

	// mainScene progress
	IMAGEMANAGER->addImage("progress_elixir", "image/progress_elixir.bmp", 175, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progress_gold", "image/progress_gold.bmp", 175, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("progress_pop", "image/progress_pop.bmp", 346, 25, true, RGB(255, 0, 255));

	// mainScene unit make
	IMAGEMANAGER->addImage("unit_make_pop", "image/unit_make_pop.bmp", 709, 478, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("archer_slot", "image/archerSlot.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barbarian_slot", "image/barbarianSlot.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("giant_slot", "image/giantSlot.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wall_breaker_slot", "image/wallBreakerSlot.bmp", 75, 75, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("unit_list_slot", "image/unit_list_slot.bmp", 90, 330, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("upgrade", "image/upgrade.bmp", 150, 102, true, RGB(255, 0, 255));

	//selectScene
	IMAGEMANAGER->addImage("selectSceneBackground", "image/selectSceneBackground2.bmp", 1300, 1114, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectBtn", "image/selectBtn.bmp", 50, 50, true, RGB(255, 0, 255));

	// playScene
	IMAGEMANAGER->addImage("unit_slot_bottom", "image/unit_slot_bottom.bmp", 1300, 111, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("btn_attack_finish", "image/btn_attack_finish.bmp", 115, 42, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectUnit", "image/selectUnit.bmp", 272, 109, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("star_slot", "image/star_slot.bmp", 156, 53, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goblin_town", "image/goblin_town.bmp", 102, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("goblin_town_1", "image/goblin_town.bmp", 102, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mortar_1", "image/Mortar_1.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("star", "image/star.bmp", 14375, 352, 25,1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playScene_finish_pop_0", "image/play_finish_pop_0.bmp", 854, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playScene_finish_pop_1", "image/play_finish_pop_1.bmp", 854, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playScene_finish_pop_2", "image/play_finish_pop_2.bmp", 854, 480, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playScene_finish_pop_3", "image/play_finish_pop_3.bmp", 854, 480, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("hpBarBottom", "image/hpBarBottom.bmp", 63, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hpBarTop", "image/hpBarTop.bmp", 63, 12, true, RGB(255, 0, 255));


	// icons
	IMAGEMANAGER->addImage("gold_icon", "image/gold_icon_small.bmp", 20, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_icon", "image/elixir_icon_small.bmp", 15, 17, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("stage_mark", "image/stage_mark.bmp", 35, 35, true, RGB(255, 0, 255));


	// unit
	IMAGEMANAGER->addFrameImage("barbarian", "image/barbarian.bmp", 384, 300, 8, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("barbarianAttack", "image/barbarianAttack.bmp", 546, 58, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archer", "image/archer.bmp", 252, 270, 7, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("archerAttack", "image/archerAttack.bmp", 296, 45, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giant", "image/giant.bmp", 784, 630, 7, 6, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("giantAttack", "image/giantAttack.bmp", 784, 630, 7, 6, true, RGB(255, 0, 255));

	// mapMakeScene
	IMAGEMANAGER->addImage("slot_background", "image/slot_background.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("slot_background_bottom", "image/slot_background_bottom.bmp", 1300, 140, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("title_map_setting_mode", "image/title_map_setting_mode.bmp", 146, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("save_btn_map_setting_mode", "image/save_btn_map_setting_mode.bmp", 231, 227, true, RGB(255, 0, 255));

	// mapmake
	IMAGEMANAGER->addImage("btn_slot", "image/btn_slot.bmp", 256, 79, true, RGB(255, 0, 255));

	// buildings
	IMAGEMANAGER->addImage("builder_hut_1", "image/Builder_Hut_1.bmp", 100, 100, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("elixir_storage_1", "image/Elixir_Storage1.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_storage_2", "image/Elixir_Storage2.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_storage_3", "image/Elixir_Storage3.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_storage_4", "image/Elixir_Storage4.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_storage_5", "image/Elixir_Storage5.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_storage_6", "image/Elixir_Storage6.bmp", 150, 150, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("elixir_collector_1", "image/elixir_collector_1.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_collector_2", "image/elixir_collector_2.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_collector_3", "image/elixir_collector_3.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_collector_4", "image/elixir_collector_4.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("elixir_collector_5", "image/elixir_collector_5.bmp", 150, 150, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("town_hall_1", "image/town_hall_1.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_2", "image/town_hall_2.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_3", "image/town_hall_3.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_4", "image/town_hall_4.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_5", "image/town_hall_5.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_6", "image/town_hall_6.bmp", 200, 250, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("town_hall_7", "image/town_hall_7.bmp", 200, 250, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("gold_storage_1", "image/Gold_Storage1.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_storage_2", "image/Gold_Storage2.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_storage_3", "image/Gold_Storage3.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_storage_4", "image/Gold_Storage4.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_storage_5", "image/Gold_Storage5.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_storage_6", "image/Gold_Storage6.bmp", 150, 150, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("gold_mine_1", "image/gold_mine_1.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_mine_2", "image/gold_mine_2.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_mine_3", "image/gold_mine_3.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_mine_4", "image/gold_mine_4.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("gold_mine_5", "image/gold_mine_5.bmp", 150, 150, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("barracks_1", "image/Barracks1.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barracks_2", "image/Barracks2.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barracks_3", "image/Barracks3.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barracks_4", "image/Barracks4.bmp", 150, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("barracks_5", "image/Barracks5.bmp", 150, 150, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("building_bottom_1_1_error", "image/building_bottom_1_1_error.bmp", 50, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_destroyed_1_1", "image/building_destroyed_1_1.bmp", 50, 34, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_2_2", "image/building_bottom_2_2.bmp", 100, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_2_2_error", "image/building_bottom_2_2_error.bmp", 100, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_3_3", "image/building_bottom_3_3.bmp", 150, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_destroyed_3_3", "image/destroyed_3_3.bmp", 150, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_3_3_error", "image/building_bottom_3_3_error.bmp", 150, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_4_4", "image/building_bottom_4_4.bmp", 200, 136, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_bottom_4_4_error", "image/building_bottom_4_4_error.bmp", 200, 136, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addImage("wall_1", "image/wall_1.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wall_1_1", "image/wall_1_1.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("wall_1_2", "image/wall_1_2.bmp", 75, 75, true, RGB(255, 0, 255));

	
	//sound
	SOUNDMANAGER->addSound("bgm", "sound/mainBackgourndSound.mp3", true, true);
	SOUNDMANAGER->addSound("gold", "sound/goldSound.mp3", false, false);



	SCENEMANAGER->addScene("mainScene", new mainScene);
	SCENEMANAGER->addScene("mapMakeScene", new mapMakeScene);
	SCENEMANAGER->addScene("selectPlayScene", new selectPlayScene);
	SCENEMANAGER->addScene("playScene", new playScene);
	SCENEMANAGER->addScene("stageMake", new stageMake);

	SCENEMANAGER->changeScene( "mainScene" );

	return S_OK;
}

void gameStudy::release()
{

	gameNode::release();
}

void gameStudy::update()
{
	SCENEMANAGER->update();

	gameNode::update();
}

void gameStudy::render( )
{
	//백버퍼에서 뿌려줌
	/*HDC backDC = this->getBackBuffer()->getMemDC();*/
	PatBlt( getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS );
	//============================================================
	
	SCENEMANAGER->render();
	
	TIMEMANAGER->render( getMemDC() );
	//============================================================
	//백버퍼에 있는 그림을 HDC에 그리자
	this->getBackBuffer()->render( getHDC(), 0, 0 );
}

