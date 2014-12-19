//
//  BallSprite.cpp
//  TumTum_Base
//
//  Created by ohtaisao on 2014/12/11.
//
//

#include "BallSprite.h"


BallSprite *BallSprite::createBallSprite(Node *parent ,b2World *world, const std::string& filename)
{
    BallSprite* pInstance = BallSprite::create();
    
    //Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    
    pInstance->setTexture(filename);
    
   
    // shape.m_radius = sptite->getContentSize().width / PTM_RATIO; // 形状の大きさ
   
    /**
     *
     剛体は次の手順で作成する。剛体とは物理エンジンの影響をうけることが出来る物質のこと
     
     1. 位置・減衰率などで剛体を定義する。
     2. 剛体を作成するためにワールドを使用する。
     3. 図形・摩擦・密度などから装備を定義する。
     4. 剛体から装備を作成する。
     */
    b2Body* body; // 剛体。rigid body。
    b2BodyDef bodyDef; // 剛体の定義
    b2CircleShape shape; // 装備の形状
    float radius = getBallRadius();
    shape.m_radius = radius/ PTM_RATIO;;
    b2FixtureDef fixtureDef; // 装備の形状定義
    
    
    // 1. 位置・減衰率などで剛体を定義する。
    bodyDef.type = b2_dynamicBody;
    //bodyDef.position.Set((winSize.width / 2) / PTM_RATIO, (winSize.height) / PTM_RATIO);
    bodyDef.userData = pInstance; // 画像をこの剛体に紐付ける
    
    // 2. 剛体を作成するためにワールドを使用する。
    body = world->CreateBody(&bodyDef);
    
    fixtureDef.shape = &shape; // 形状を紐付ける
    fixtureDef.density = 1; // 密度
    fixtureDef.friction = 0.9; // 摩擦
    
    // 4. 剛体から装備を作成する。
    body->CreateFixture(&fixtureDef);
    
    /** PhysicsSpriteに各種情報をセットする */
    //parent->addChild(pInstance);
    pInstance->setB2Body(body);
    pInstance->setPTMRatio(PTM_RATIO);

    
    parent->addChild(pInstance);
    
    return pInstance;
}

BallSprite *BallSprite::createParticleSprite(Node *parent ,b2World *world, const std::string& filename) {
    BallSprite* pInstance = BallSprite::create();
    
    //Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(filename);
    
    pInstance->setTexture(filename);
    
    //パーティクルシステムのデータ設定
    b2ParticleSystemDef particleSystemDef;
    
    //各パーティクルの半径を設定
    particleSystemDef.radius =  getBallRadius();
    
    //パーティクルシステムの生成
    b2ParticleSystem * particleSystem = world->CreateParticleSystem(&particleSystemDef);
    void ** userData = particleSystem->GetUserDataBuffer();
    (*userData) = pInstance;
    parent->addChild(pInstance);
    return pInstance;
    
    //画面サイズ取得
    //Size size = Director::getInstance()->getWinSize();
    
    //生成位置設定
    //Point pos = {size.width/2/PTM_RATIO,size.height * 0.2/PTM_RATIO};
    
    //グループで生成する際はパーティクルグループの形を設定する必要がある
    //b2PolygonShape* shape = new b2PolygonShape();
    //shape->SetAsBox(size.width*0.8/PTM_RATIO, size.height*0.05/PTM_RATIO);
    
    //パーティクルグループのデータ設定
    //b2ParticleGroupDef groupDef;
    
    //パーティクルのグループを設定
   // groupDef.shape = shape;
    
    //flagsを設定する事でパーティクルの挙動を設定する事ができます
    //今回は海を作るので水になっていますが
    //バネや砂など色々な挙動を設定する事ができます。
   // groupDef.flags = b2_waterParticle;
    //groupDef.color = b2ParticleColor(100,150,255,255);
    //groupDef.position.Set(pos.x / PTM_RATIO, pos.y / PTM_RATIO);
    //seaGroup = particleSystem->CreateParticleGroup(groupDef);
    
    //各パーティクルのユーザーデータに「Sprite*」を持たせる
    //ユーザーデータは「b2ParticleSystem」がバッファとして保持している。
    //各グループはデータの開始地点を保持しており
    //自分のグループが保持しているパーティクルの分だけループして取得する事ができる
    /*
    void ** userData = particleSystem->GetUserDataBuffer() + seaGroup->GetBufferIndex();
    for(int i = 0; i != seaGroup->GetParticleCount();i++,userData++){
        Sprite * tex = Sprite::create("tex.png");
        (*userData) = tex;
        tex->setScale(0.5f);
        this->addChild(tex);
    }
     */
}

void BallSprite::setPhysics2Sprite(b2World *world, cocos2d::extension::PhysicsSprite *sptite, b2BodyType type, b2Shape shape)
{
    /**
     *
     剛体は次の手順で作成する。剛体とは物理エンジンの影響をうけることが出来る物質のこと
     
     1. 位置・減衰率などで剛体を定義する。
     2. 剛体を作成するためにワールドを使用する。
     3. 図形・摩擦・密度などから装備を定義する。
     4. 剛体から装備を作成する。
     */
    b2Body* body; // 剛体。rigid body。
    b2BodyDef bodyDef; // 剛体の定義
    //b2CircleShape shape; // 装備の形状
    b2FixtureDef fixtureDef; // 装備の形状定義
    
    
    // 1. 位置・減衰率などで剛体を定義する。
    bodyDef.type = type;
    //bodyDef.position.Set((winSize.width / 2) / PTM_RATIO, (winSize.height) / PTM_RATIO);
    bodyDef.userData = sptite; // 画像をこの剛体に紐付ける
    
    // 2. 剛体を作成するためにワールドを使用する。
    body = world->CreateBody(&bodyDef);
    
    fixtureDef.shape = &shape; // 形状を紐付ける
    fixtureDef.density = 1; // 密度
    fixtureDef.friction = 0.9; // 摩擦
    
    // 4. 剛体から装備を作成する。
    body->CreateFixture(&fixtureDef);
    
    /** PhysicsSpriteに各種情報をセットする */
    //parent->addChild(pInstance);
    sptite->setB2Body(body);
    sptite->setPTMRatio(PTM_RATIO);

}

float BallSprite::getBallRadius()
{
    
    return 50;
}

bool BallSprite::init()
{
    if ( !Sprite::init() ) {
        return false;
    }
    _ballContactState = ballContactState::kNone;
    _deleteState      = deleteState::kNoDelete;
    _ballType         = ballType::kRed;
    _ballHilightType  = ballHilightType::kNoTouch;
    
    _isTouchBegan = false;
    _isTouchMoved = false;
    _isTouchEnd   = false;
    
    this->setOpacity(200);
    return true;
}

BallSprite::ballContactState BallSprite::getBallContState(){
    
    return _ballContactState;
}

void BallSprite::setBallContState(ballContactState state) {
    if (state == ballContactState::kFloorContact || ballContactState::kSecondContact) {
        //cpSpaceAddPostStepCallback
        //body->setDynamic(false);
        Vec2 ver = Vec2(0, 0.1);
        //body->setVelocity(ver);
    }
    else {
        //body->setDynamic(true);
    }
    _ballContactState = state;
}

bool BallSprite::isInCircle(Vec2 pos, Node *parent) {
    const Vec2 bpos = parent->convertToNodeSpace(this->getPosition());
    float dist = pos.getDistance(bpos);
    if(dist <= getBallRadius()) {
        return true;
    }
    else {
        return false;
    }
}

bool BallSprite::isInCircle(Touch touch) {
    const Vec2 bpos = this->getPosition();
    Director* pDirector = CCDirector::getInstance();
    Point touchPoint = pDirector -> convertToGL(touch.getLocationInView());
    float dist = touchPoint.getDistance(bpos);
    if(dist <= getBallRadius()) {
        return true;
    }
    else {
        return false;
    }

}

bool BallSprite::getIsTouchBegan() {
    return _isTouchBegan;
}
void BallSprite::setIsTouchBegan() {
    _isTouchBegan = true;
}
bool BallSprite::getIsTouchMoved() {
    return _isTouchMoved;
}
void BallSprite::setIsTouchMoved() {
    _isTouchMoved = true;
}
bool BallSprite::getIsTouchEnd() {
    return _isTouchEnd;
}
void BallSprite::setIsTouchEnd() {
    _isTouchEnd = true;
}

BallSprite::deleteState BallSprite::getDeleteState() {

    return _deleteState;
}

void BallSprite::setDeleteState(deleteState state){
    _deleteState = state;
}

BallSprite::ballType BallSprite::getBallType() {
    return _ballType;
}

void BallSprite::setBallType(ballType state) {
    _ballType = state;
}

BallSprite::ballHilightType BallSprite::getBallHilightType() {
    return _ballHilightType;
}
void BallSprite::setBallHilightType(ballHilightType state) {
    _ballHilightType = state;
    if (state ==  ballHilightType::kNoTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kFirstTouch) {
        this->setOpacity(200);
        this->setNormalTexture();
    }
    else if (state == ballHilightType::kChain) {
        this->setOpacity(150);
        this->setHilightTexture();
        
    }
    else if (state == ballHilightType::kAdjacent) {
        this->setOpacity(255);
        this->setHilightTexture();
    }
    else {
        this->setOpacity(200);
        this->setNormalTexture();
    }
}

void BallSprite::setNormalTexture() {
    ballType type = this->getBallType();
    switch (type) {
        case ballType::kRed:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("ball.png"));
            break;
        case ballType::kBrue:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("blue_ball.png"));
            break;
        case ballType::kYellow:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("yellow_ball.png"));
            break;
        case ballType::kPurple:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("pur_ball.png"));
            break;
        default:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("ball.png"));
            break;
    }

}
void BallSprite::setHilightTexture() {
    ballType type = this->getBallType();
    switch (type) {
        case ballType::kRed:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_ball.png"));
            break;
        case ballType::kBrue:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_blue_ball.png"));
            break;
        case ballType::kYellow:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_yellow_ball.png"));
            break;
        case ballType::kPurple:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_pur_ball.png"));
            break;
        default:
            this->setTexture(Director::getInstance()->getTextureCache()->addImage("hl_ball.png"));
            break;
    }
}
