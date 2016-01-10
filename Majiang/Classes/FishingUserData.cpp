#include "FishingUserData.h"
#include "StaticData.h"

FishingUserData* FishingUserData::create( Json::Value data)
{
        FishingUserData* userdata = new FishingUserData();
        userdata->init( data );
       return userdata;
}

bool FishingUserData::init( Json::Value data ){

	id = data["id"].asInt();

	gold = data["gold"].asInt();
	ep = data["experience"].asInt();
	fag = data["fag"].asInt();
	crystal = data["crystal"].asInt();

	nickname = data["nickname"].asString();
	imageurl = data["imageurl"].asString();
	ident = data["ident"].asString();
	equip = data["equip"].asInt();

	pktotal = data["pktotal"].asInt();
	pkwin = data["pkwin"].asInt();
	pklose = data["pklose"].asInt();

	imgid = data["img_id"].asInt();

	weapon_id = data["weapon_id"].asInt();

	speed = data["speed"].asInt();
	frequence = data["frequence"].asInt();
	scope = data["scope"].asInt();
	crit = data["crit"].asInt();

	return true;

}