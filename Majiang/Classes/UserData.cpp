#include "UserData.h"
//#include "StaticData.h"

static UserData* _sharedUserData = NULL;

UserData* UserData::sharedUserData()
{
	if (_sharedUserData == NULL){
		_sharedUserData = new UserData();
		_sharedUserData->init();
	}
	return _sharedUserData;
}

bool UserData::init()
{
	setWins(0);
	setEscape_rate(0);
	setPoints(0);
	setPlaying_times(0); 
	setGender("unknown");
	setGameType(-1);
	setLevelType(-1);
	return true;
}

void UserData::flush()
{
	CCUserDefault::sharedUserDefault()->setStringForKey("ident", UserData::sharedUserData()->getIdent());
	/*
	if (UserData::sharedUserData()->getVisitorId() != 0) {
		int vid = FishingJoyData::sharedFishingJoyData()->getVisitorId();
		CCUserDefault::sharedUserDefault()->setIntegerForKey("visitorId", vid);
		CCUserDefault::sharedUserDefault()->setStringForKey("ident", UserData::sharedUserData()->getIdent());
	}
	
	UserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
	CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
	CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());
	if (FishingJoyData::sharedFishingJoyData()->getVisitorId() != 0) {
		int vid = FishingJoyData::sharedFishingJoyData()->getVisitorId();
		CCUserDefault::sharedUserDefault()->setIntegerForKey("visitorId", vid);
		CCUserDefault::sharedUserDefault()->setStringForKey("ident", FishingJoyData::sharedFishingJoyData()->getIdent());
	}

	if (getGameType() == 0) {
		CCUserDefault::sharedUserDefault()->setBoolForKey("isFirstInSingle", false);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("randnSingle", FishingJoyData::sharedFishingJoyData()->getRandInSingle());
		CCUserDefault::sharedUserDefault()->setStringForKey("nickname", FishingJoyData::sharedFishingJoyData()->getNickName());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", FishingJoyData::sharedFishingJoyData()->getGold());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("ep", FishingJoyData::sharedFishingJoyData()->getEp());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("fag", FishingJoyData::sharedFishingJoyData()->getFag());
		CCUserDefault::sharedUserDefault()->setIntegerForKey("crs", FishingJoyData::sharedFishingJoyData()->getCrs());
		CCUserDefault::sharedUserDefault()->setStringForKey("entries", FishingJoyData::sharedFishingJoyData()->getEntries());
	}
	CCUserDefault::sharedUserDefault()->flush();
	CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
	*/
	UserDefault::sharedUserDefault()->flush();
	UserDefault::sharedUserDefault()->purgeSharedUserDefault();
}

UserData::UserData()
{

}

UserData::~UserData()
{

}

size_t onHttpRequestCompleted(char* data, size_t size, size_t nmemb, string* writedata)
{
	if (writedata == NULL)
		return 0;
	writedata->append(data, size* nmemb);
	return size * nmemb;
}

/***    
	SelectEntryScene Ϊ 1
	LevelScene Ϊ 2
***/
int Scene_to_MallScene_type = 0;