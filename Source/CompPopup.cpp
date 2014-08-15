#include "CompPopup.h"
#include "SkinComp.h"
//#include "ParameterInterface.h"
#include "ShottyLook.h"

CompPopup::CompPopup(ParameterInterface* comp)
{
    this->setAlpha(0);
	this->comp = comp;
    this->setFocusContainer(false);
    
    //	comp->addChangeListener(this);
	count = 0;
    fade = 0;
    //	setSize(100,24);
	setInterceptsMouseClicks(false,false);
	setAlwaysOnTop(true);
    //    this->setEditable(true);
    
    //    addAndMakeVisible(&this->input);
}
CompPopup::~CompPopup(void)
{
    Desktop::getInstance().getAnimator().removeChangeListener(this);
    this->clearSingletonInstance();
    //	comp->removeChangeListener(this);
    this->deleteAllChildren();
}
void CompPopup::paint(Graphics& g)
{
    g.setColour(Colours::black);
    //	g.setOpacity(2. / 3.);
    g.fillAll();
    
    //	g.fillRoundedRectangle(0,0,getWidth(),getHeight());
    //	g.setOpacity(1);
    //	g.setColour(Colours::white);
    //	g.drawText("test",0,0,getWidth(),getHeight(),Justification::centred,true);
}
void CompPopup::mouseEnter(const MouseEvent & 	event	)
{
    this->stopTimeOut();
}

void CompPopup::mouseExit(const MouseEvent & 	event	)
{
    this->timeOut();
}

void CompPopup::stopTimeOut()
{
    this->stopTimer();
}
void CompPopup::timeOut()
{
    this->startTimer(1000);
}

juce_ImplementSingleton(CompPopup);
void CompPopup::hide(int timeout)
{
    CompPopup::getInstance()->timeOut();
}
void CompPopup::fadeout()
{
    int time = 500;
    this->setFocusContainer(false);
    this->setInterceptsMouseClicks(false, false);
    
    if(fade != 0)
    {
        this->fade = 0;
        Desktop::getInstance().getAnimator().animateComponent(this, this->getBounds(), fade, time, false, 0, 0);
        
        Desktop::getInstance().getAnimator().addChangeListener(this);
    }
    
}
void CompPopup::fadein()
{
    CompPopup* pop = this;
    Component* param = this->getChildComponent(0);
    Component* comp = this->targetComp;
    
    Rectangle<int> r = comp->getScreenBounds();
    int xOff = (r.getWidth() - param->getWidth())/2;
    
    Rectangle<int> tr(r.getX() + xOff, r.getBottom(),param->getWidth(), param->getHeight());
    if(pop->getAlpha() == 0)
        pop->setBounds(tr);
    
    pop->setFocusContainer(true);
    pop->addToDesktop(ComponentPeer::windowIsTemporary);
    pop->setInterceptsMouseClicks(true, true);
    pop->stopTimer();
    param->addMouseListener(pop, true);
    
    bool isNewTarget = Desktop::getInstance().getAnimator().getComponentDestination(pop) != tr;
    if(this->fade == 0 || isNewTarget)
    {
        this->fade = 0.7;
        Desktop::getInstance().getAnimator().animateComponent(pop, tr, fade, 500, false, 0, 0);
    }
    
}
void CompPopup::show(Component* param, Component* comp)
{
    
    CompPopup* pop = CompPopup::getInstance();
    if(param != nullptr)
    {
        pop->deleteAllChildren();
        pop->addAndMakeVisible(param);
        param->addComponentListener(pop);
    }
    if(comp != nullptr)
    {
        pop->targetComp = comp;
    }
    
    pop->fadein();
    //    pop->setTopLeftPosition();
}
void CompPopup::componentMovedOrResized (Component& component,
                                         bool wasMoved,
                                         bool wasResized)
{
    if(this->getChildComponent(0) == &component && wasResized)
    {
        this->setSize(component.getWidth(), component.getHeight());
    }
}
void CompPopup::timerCallback()
{
    //    CompPopup::getInstance()->setVisible(false);
    this->fadeout();
    this->stopTimer();
    return;
    
	if(count >= 0)
    {
		count ++;
    }
	if(count == 25)
	{
		coeff = -0.1;
		return;
	}
    
	fade += coeff;
	fade = jlimit(0.f,1.f,fade);
	if(fade == 0)
	{
		setVisible(false);
		stopTimer();
	}
    
	repaint();
}

void CompPopup::popup(int x, int y, SkinComp* comp)
{
	setVisible(true);
	count = -1;
    x = jlimit(0, this->getParentComponent()->getWidth() - this->getWidth(), x);
    y = jlimit(0, this->getParentComponent()->getHeight() - this->getHeight(), y);
	setTopLeftPosition(x,y);
    //	if(comp!=this->comp)
    //		fade = 0;
	coeff = 0.1;
	startTimer(1000/25);
    
}
void CompPopup::changeListenerCallback(ChangeBroadcaster*obj)
{
    if(this->getAlpha() == 0)
        this->setVisible(false);
    
    Desktop::getInstance().getAnimator().removeChangeListener(this);
    //	repaint();
}

//juce_ImplementSingleton(CompPopup);