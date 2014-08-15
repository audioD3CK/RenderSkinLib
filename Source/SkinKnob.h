#pragma once
#include "JuceHeader.h"
#include "CompPopup.h"

class SkinComp;

class SkinKnob :
public Slider,
public Slider::Listener,
public ChangeListener
{
public:
	SkinKnob(SkinComp* comp);
	~SkinKnob();
    
    void changeListenerCallback(ChangeBroadcaster* b)override;
    
	void mouseUp(const MouseEvent& e)override;
    void mouseDown(const MouseEvent& e)override;
    void mouseMove(const MouseEvent& e)override;

    void sliderValueChanged(Slider* slider)override;
    
	void mouseWheelMove(const MouseEvent& event,const MouseWheelDetails& wheel)override;
	void paint(Graphics& g)override;
    
private:
    CompPopup popup;
	WeakReference<SkinComp> comp;
};

