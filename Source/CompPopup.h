#pragma once
#include "JuceHeader.h"
class ParameterInterface;

class SkinComp;
class CompPopup :
public DeletedAtShutdown,
public Component,
public Timer,
public ChangeListener,
public ComponentListener
{
public:
	CompPopup(ParameterInterface* comp = nullptr);
	~CompPopup(void);
    
    juce_UseDebuggingNewOperator

	void paint(Graphics& g);
	void timerCallback();
	void popup(int x, int y, SkinComp* comp);
	void fadeout();
	void fadein();
    void mouseExit(const MouseEvent & 	event	) override;
    void mouseEnter(const MouseEvent& e) override;
	void changeListenerCallback(ChangeBroadcaster*obj);
    void timeOut();
    void stopTimeOut();
    void componentMovedOrResized (Component& component, bool wasMoved, bool wasResized);
    
    static void show(Component* param, Component* comp);
    static void hide(int timeout = 0);
    
private:
	float fade;
	float coeff;
	int count;
    Component* targetComp;
    juce_DeclareSingleton(CompPopup, false);
    
	ParameterInterface* comp;
};

