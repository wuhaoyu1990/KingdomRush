#include "TowerScene.h"
#include "SoundManager.h"

USING_NS_CC;

Scene* Tower::createScene(){
    auto scene = Scene::create();
    auto towerInfLayer = Tower::create();
    scene->addChild(towerInfLayer);
    return scene;
}

bool Tower::init(){
    if ( !Layer::init() ){
        return false;
    }
	//声明监听事件类型并绑定执行函数
	auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->setSwallowTouches(true);//重叠精灵
	touchListener->onTouchBegan = CC_CALLBACK_2(Tower::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Tower::onTouchEnded, this);
	

    //取得屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 第二层了，显示书本图标-删掉底层，直接显示书皮
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Point(i*310,j*150));
			sprite->setAnchorPoint(Point(0,0));
			addChild(sprite);
		}
	}

	// 背景-书-右边
    auto sprite1 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite1->setPosition(Vec2(visibleSize.width * 3/4 + origin.x, visibleSize.height/2 + origin.y));

	//书-左边
    auto sprite2 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite2->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));

	//旋转
	sprite2->setFlippedX(true);
    sprite2->setRotation(360);

	// 添加图片精灵到画面层
    this->addChild(sprite1, 1);
	this->addChild(sprite2, 1);

	//关闭叉叉
	auto sprite3 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png");
	//添加点击
	spriteCloseButton = MenuItemSprite::create(sprite3,sprite3,sprite3,CC_CALLBACK_1(Tower::closeScene,this));  
    auto closeEnemyScene = Menu::create(spriteCloseButton,NULL);  //实现三者之间的顺序切换  
	closeEnemyScene->setPosition(Vec2(visibleSize.width - sprite3->getContentSize().width * 3 / 2  + origin.x, 
								visibleSize.height + origin.y - sprite3->getContentSize().height / 2));
    this->addChild(closeEnemyScene,2); 
	//怪物列表
	//框框
	creepFrame = Sprite::createWithSpriteFrameName("encyclopedia_creep_thumbs_frame_0002.png");  

    creepFrame->setPosition(Point(visibleSize.width * 0.17, visibleSize.height * 0.75));
	this->addChild(creepFrame,3); 


	//无效的拇指图标
	auto spriteCreepThumbNull = Sprite::createWithSpriteFrameName("encyclopedia_tower_thumbs_0121.png");

	//初始化拇指图标20个
	//初始化拇指图标20个
	for(int i = 0; i < 20; i ++)
	{
		auto temp1 = String::createWithFormat("encyclopedia_tower_thumbs_01%02d.png",i+1)->getCString();
		auto temp2 = String::createWithFormat("encyclopedia_tower_01%02d.png",i+1)->getCString();

		towerDesc[i] = TowerDesc::createTowerDesc(temp1);
		towerDesc[i]->setPosition(Point(visibleSize.width * (0.17 + (i % 4)*0.085), 
												visibleSize.height * (0.75 - ((i / 4) % 5) *0.15)));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), towerDesc[i]);
		towerDesc[i]->towerThumbFileName = temp1;
		towerDesc[i]->towerDescFileName = temp2;
		//初始化游标
		towerDesc[i]->num = i;
		this->addChild(towerDesc[i],2);
		
	}


	//初始化说明大图
	bigSprite = Sprite::createWithSpriteFrameName(towerDesc[0]->towerDescFileName);

	bigSprite->setPosition(Vec2(visibleSize.width * 0.7,visibleSize.height * 0.75));
	this->addChild(bigSprite,2);

	//字-塔
    auto labelTitle = Label::createWithTTF("TOWERS", "Marker Felt.ttf", 24);
    labelTitle->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 6 / 7));
	labelTitle->setColor(Color3B(0,0,0));
    this->addChild(labelTitle, 2);

	////////////////////////////////////////////////
	///一大堆label-开始
	///////////////////////////////////////////////
	//塔名称
	labelName = Label::createWithTTF("", "Marker Felt.ttf", 24);
    // 设置label在屏幕中的显示位置
    labelName->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.60));
	labelName->setColor(Color3B(0,0,0));
    // 把label添加到画面层
    this->addChild(labelName, 2);

	labelAttackSpeed = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackSpeed->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.50));
	labelAttackSpeed->setColor(Color3B(0,0,0));
    this->addChild(labelAttackSpeed, 2);

	labelAttackValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.45));
	labelAttackValue->setColor(Color3B(0,0,0));
    this->addChild(labelAttackValue, 2);

	labelAttackRange = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackRange->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.40));
	labelAttackRange->setColor(Color3B(0,0,0));
    this->addChild(labelAttackRange, 2);
	
	//塔属性补充
    labelNotice = Label::createWithTTF("*", "Marker Felt.ttf", 16);
    labelNotice->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.15));
	labelNotice->setColor(Color3B(0,0,0));
	labelNotice->setLineBreakWithoutSpace(true);
	labelNotice->setDimensions(visibleSize.width/3,visibleSize.height * 0.15);
    this->addChild(labelNotice, 2);

	/*****************************
	**显示中文设计模块-开始
	******************************/
	
	//读取xml文档,放入ValueVector中
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("tower.xml");
	int i = 0;
	for( auto& e : txt_vec){
		auto txt_map = txt_vec.at(i).asValueMap();//将键值转化成Map格式，放入txt_map中
		int id_int = txt_map.at("id").asInt();//获取id
		if(id_int == i){
			//auto label_str = txt_map.at("info").asString();//获取info的值
			towerDesc[i]->towerName = txt_map.at("TowerName").asString();
			towerDesc[i]->attackSpeed = txt_map.at("AttackSpeed").asString();
			towerDesc[i]->attackValue = txt_map.at("AttackValue").asString();
			towerDesc[i]->attackRange = txt_map.at("AttackRange").asString();
			towerDesc[i]->note = txt_map.at("Note").asString();
		}else if(id_int == 100){
			labelAttackSpeed->setString(txt_map.at("AttackSpeed").asString());
			labelAttackValue->setString(txt_map.at("AttackValue").asString());
			labelAttackRange->setString(txt_map.at("AttackRange").asString());
		}
		i ++; //下一个怪物	
	}

	/*****************************
	**显示中文设计模块-结束
	*****************************/

	//下面是属性值
	//怪物血值1
	labelAttackSpeed1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // 设置label在屏幕中的显示位置
    labelAttackSpeed1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.50));
	labelAttackSpeed1->setColor(Color3B(0,0,0));
    // 把label添加到画面层
    this->addChild(labelAttackSpeed1, 2);

	//怪物攻击力
	labelAttackValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // 设置label在屏幕中的显示位置
    labelAttackValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.45));
	labelAttackValue1->setColor(Color3B(0,0,0));
    // 把label添加到画面层
    this->addChild(labelAttackValue1, 2);

	//怪物物理防御力
	labelAttackRange1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // 设置label在屏幕中的显示位置
    labelAttackRange1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.40));
	labelAttackRange1->setColor(Color3B(0,0,0));
    // 把label添加到画面层
    this->addChild(labelAttackRange1, 2);

	//////////////////////////////////
	//一大堆label-结束
	//////////////////////////////////

	bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(towerDesc[0]->towerDescFileName));
	labelName->setString(towerDesc[0]->towerName);
	//七大属性
	labelAttackSpeed1->setString(towerDesc[0]->attackSpeed);
	labelAttackValue1->setString(towerDesc[0]->attackValue);
	labelAttackRange1->setString(towerDesc[0]->attackRange);
	labelNotice->setString(towerDesc[0]->note);

	creepFrame->setPosition(towerDesc[0]->getPosition());
	creepFrame->setVisible(true);
	return true;
}

//怪物描述 
bool Tower::onTouchBegan(Touch* touch, Event* event){

	auto target = static_cast<TowerDesc*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->towerDescPic->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);

	if (rect.containsPoint(locationInNode) && target->getParent()->isVisible()){
		SoundManager::playClickEffect();
		bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(target->towerDescFileName));
		labelName->setString(target->towerName);
		//七大属性
		labelAttackSpeed1->setString(target->attackSpeed);
		labelAttackValue1->setString(target->attackValue);
		labelAttackRange1->setString(target->attackRange);
		labelNotice->setString(target->note);

		moveFrame=MoveTo::create(0.1f,target->getPosition());//设置图标的位移时间，位移目标地址
		creepFrame->runAction(moveFrame);
		creepFrame->setVisible(true);

		return true;
	}
	return false;
}

void Tower::onTouchEnded(Touch* touch, Event* event){
	return;
}

//关闭场景
void Tower::closeScene(Ref* pSender){
	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
	return;

}