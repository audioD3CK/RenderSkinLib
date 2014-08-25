#include "SkinCompGUI.h"
#include "SkinComp.h"
#include "Skin.h"
#include "SkinGUI.h"

SkinCompGUI::SkinCompGUI(SkinComp* comp,SkinGUI* skinGUI):
BoundDrivenComponent(&comp->graphicArea)
{
    this->skinGUI = skinGUI;
	this->comp = comp;
    
	comp->addChangeListener(this);
    
	changeListenerCallback(comp);
    
    this->setOpaque(false);
    
}

double SkinCompGUI::getScale()const
{
    return this->skinGUI->getScale();
}


SkinCompGUI::~SkinCompGUI(void)
{
    if(comp)
    {
        comp->removeChangeListener(this);
    }
}

Point<int> SkinCompGUI::getOffset()const
{
    return this->comp->getSkin()->graphicArea.getPosition()*-1;
}

void SkinCompGUI::audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)
{
    this->repaint();
}

void SkinCompGUI::audioProcessorChanged (AudioProcessor* processor)
{
    this->repaint();
}

bool SkinCompGUI::useMask()const
{
    return true;//this->comp->getClipType() != SkinComp::rect;
}

void SkinCompGUI::resized()
{
}

Image SkinCompGUI::getMask()
{
    return comp->getMask(this->getBounds());//this->mask;
}

void SkinCompGUI::paint(Graphics& g)
{
    
    double frame = comp->getAbsolutFrame() - comp->getRange().getStart();
    
    int index0 = this->comp->getCompType() == SkinComp::CompType::togglebutton ? (frame ? 1 : 0) : (int)frame  ;
    int index1 = index0+1;
    float r2 = frame - index0;
    
    
    Rectangle<int> b = comp->graphicArea;
    Rectangle<int> bScaled = b * this->getScale();
    
    if(this->useMask())
    {
        g.reduceClipRegion(this->getMask(), AffineTransform::identity);
    }
    
    g.drawImage(comp->stripImage,0,0,bScaled.getWidth(),bScaled.getHeight(),0,b.getHeight()*index0,b.getWidth(),b.getHeight());
    
    if(comp->interpolation.getValue() && r2)
    {
        g.setOpacity(r2);
        g.drawImage(comp->stripImage,0,0,bScaled.getWidth(),bScaled.getHeight(),0,b.getHeight()*index1,b.getWidth(),b.getHeight());
    }
    
}

void SkinCompGUI::changeListenerCallback(ChangeBroadcaster* obj)
{
	BoundDrivenComponent::changeListenerCallback(obj);
	repaint();
}