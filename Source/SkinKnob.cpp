#include "SkinKnob.h"
#include "SkinComp.h"

SkinKnob::SkinKnob(SkinComp* comp)
{
	this->comp = comp;
    
    comp->addChangeListener(this);
    
	setSliderStyle(Slider::Rotary);
	setRange(0,1);
	setTextBoxStyle(Slider::NoTextBox,true,32,32);
	setMouseCursor(MouseCursor::DraggingHandCursor);
	setRange(0,1);
	setSliderStyle(Slider::LinearVertical);
	setSliderSnapsToMousePosition(false);
	setMouseCursor(MouseCursor::DraggingHandCursor);
    
    this->addListener(this);
    setOpaque(false);

}
SkinKnob::~SkinKnob()
{
    if(this->comp)
    {
        this->comp->removeChangeListener(this);
    }
}

void SkinKnob::changeListenerCallback(ChangeBroadcaster *b)
{
    if(this->comp)
    {
        this->setValue(comp->getFrame(),NotificationType::dontSendNotification);
        this->setMouseDragSensitivity(comp->getSensitivity());
    }
}

void SkinKnob::sliderValueChanged(Slider* slider)
{
	comp->setFrame(slider->getValue());
}

void SkinKnob::mouseMove(const juce::MouseEvent &event)
{
    Slider::mouseMove(event);
}
void SkinKnob::mouseDown(const MouseEvent &e)
{
    if(getParentComponent() && getParentComponent()->getParentComponent())
    {
        getParentComponent()->getParentComponent()->addChildComponent(&popup);
        MouseEvent e2 = e.getEventRelativeTo(this);
        popup.popup(getX(),getY()+getHeight(),this->comp);
    }
    
    Slider::mouseDown(e);
}

void SkinKnob::mouseUp(const MouseEvent& e)
{
    
	if(e.mods.isCtrlDown())
    {
		this->comp->setFrame(comp->getDefaultFrame());
    }
	else
    {
		if(comp->getCompType() == SkinComp::togglebutton)
		{
			int len = comp->getNumFrames();//getRange().getLength();
			int currentStep = len * comp->getFrame();
			currentStep ++;
			currentStep %= (len+1);
			comp->setFrame(  (float)currentStep / (len) );
		}
    }
    
	Slider::mouseUp(e);
    
    popup.fadeout();
    
    
}
void SkinKnob::mouseWheelMove(const MouseEvent& e,const MouseWheelDetails& wheel)
{
    MouseWheelDetails d(wheel);
    d.deltaX  /= 5;
    d.deltaY /= 5;
	Slider::mouseWheelMove(e,d);
    
    
    popup.popup(getX(),getY()+getHeight(),this->comp);
    popup.fadeout();
	
}

void SkinKnob::paint(Graphics& g)
{
	//do not paint anything!
}