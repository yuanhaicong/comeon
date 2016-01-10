#include "CCLoginReader.h"
#include "CCLogin.h"

USING_NS_CC;

static CCLoginReader* _instanceMyClassReader = nullptr;

CCLoginReader* CCLoginReader::getInstance()
{
	if (!_instanceMyClassReader)
	{
		_instanceMyClassReader = new CCLoginReader();
	}
	return _instanceMyClassReader;
}

void CCLoginReader::purge()
{
	CC_SAFE_DELETE(_instanceMyClassReader);
}

Node* CCLoginReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions)
{
	CCLogin* node = CCLogin::create();
	setPropsWithFlatBuffers(node, nodeOptions);
	return node;
} 