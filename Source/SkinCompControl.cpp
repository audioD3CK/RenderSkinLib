#include "SkinComp.h"
#include "Skin.h"
#include "SkinViewComp.h"
#include "SkinComp.h"
#include "SkinGUI.h"
#include "SkinCompControl.h"
#include "SkinKnob.h"

SkinCompControll::SkinCompControll(SkinComp* comp, SkinGUI* gui):
BoundDrivenComponent(&comp->graphicArea)
{
	this->comp = comp;
	this->gui = gui;
    
	comp->addChangeListener(this);
    
    this->knob = comp->createControllComponent();
    if(this->knob)
    {
        addChildComponent(this->knob);
    }
    
	changeListenerCallback(comp);
}

void SkinCompControll::changeListenerCallback(ChangeBroadcaster* b)
{
    
    BoundDrivenComponent::changeListenerCallback(b);
    resized();
}

Point<int> SkinCompControll::getOffset()const
{
    return this->comp->getSkin()->graphicArea.getPosition()*-1;
}

double SkinCompControll::getScale()const
{
    return this->gui->getScale();
}

SkinCompControll::~SkinCompControll()
{
    if(comp)
    {
        comp->removeChangeListener(this);
    }
}

void SkinCompControll::resized()
{
    if(knob)
    {
        if((bool)comp->useControllArea.getValue() == true)
        {
            Rectangle<int> rect = comp->controllArea.translated(-comp->graphicArea.getX(),-comp->graphicArea.getY());
            knob->setBounds(rect * this->getScale());
        }
        else
        {
            knob->setBounds(0,0,getWidth(),getHeight());
        }
    }
}
