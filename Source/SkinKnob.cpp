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
        this->setVisible(comp->getCompType() == SkinComp::slider || comp->getCompType() == SkinComp::togglebutton);
        
        this->setValue(comp->getValue(),NotificationType::dontSendNotification);
        this->setMouseDragSensitivity(comp->getSensitivity());
    }
}

void SkinKnob::sliderValueChanged(Slider* slider)
{
	comp->setValue(slider->getValue());
}

void SkinKnob::mouseUp(const MouseEvent& e)
{
    
	if(e.mods.isCtrlDown())
    {
		this->comp->setValue(comp->getDefaultFrame());
    }
	else
    {
		if(comp->getCompType() == SkinComp::togglebutton)
		{
			int len = comp->getNumFrames();//getRange().getLength();
			int currentStep = len * comp->getValue();
			currentStep ++;
			currentStep %= (len+1);
			comp->setValue(  (float)currentStep / (len) );
		}
    }
    
	Slider::mouseUp(e);
    
}
void SkinKnob::mouseWheelMove(const MouseEvent& e,const MouseWheelDetails& wheel)
{
    MouseWheelDetails d(wheel);
    d.deltaX  /= 5;
    d.deltaY /= 5;
	Slider::mouseWheelMove(e,d);
    
	
}

void SkinKnob::paint(Graphics& g)
{
	//do not paint anything!
}