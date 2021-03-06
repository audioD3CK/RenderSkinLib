#pragma once
#include "JuceHeader.h"
#include "BoundDrivenComponent.h"

class SkinGUI;
class SkinComp;

class SkinCompControll :
	public BoundDrivenComponent
{
public:
	SkinCompControll(SkinComp* comp, SkinGUI* gui);
	~SkinCompControll(void);
    
	void resized()override;
    double getScale()const override;
    
    void changeListenerCallback(ChangeBroadcaster* b)override;
    
    Point<int> getOffset()const override;

private:
	SafePointer<SkinGUI> gui;
	ScopedPointer<Component> knob;
	WeakReference<SkinComp> comp;
};