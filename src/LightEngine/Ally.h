#pragma once
#include "PhysicalEntity.h"

class Ally : public PhysicalEntity
{
public:
	enum TagAlly
	{
		TVineR,
		TVineG,
		TNenuphloatR,
		TNenuphloatG,
		TStation,
		TBulb,
	};

	int mTagAlly = -1;

	virtual void OnInitialize();
	virtual void OnUpdate();

	void SetTagAlly(int tagAlly) { mTagAlly = tagAlly; }

	bool IsTagAlly(int tagAlly) const { return mTagAlly == tagAlly; }
};

