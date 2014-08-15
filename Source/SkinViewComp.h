#pragma once
#include "JuceHeader.h"

class Skin;

class SkinViewComp :
	public Component,
	public ChangeListener
{
public:
	SkinViewComp(Skin* skin);
	~SkinViewComp();
    
	void paint(Graphics& g)override;
	void childBoundsChanged(Component* comp)override;
    
    Skin* getSkin()const;
    
protected:
	WeakReference<Skin> skin;
};

