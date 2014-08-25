#include "SkinGUI.h"
#include "Skin.h"
#include "SkinCompGUI.h"
#include "SkinCompControl.h"

const int controllHeight = 20;

SkinGUI::SkinGUI(Skin* skin,double scale):
SkinViewComp(skin),
skinChooser("skin file",skin->getFile(),false,false,false,"*.xml","","choose skin"),
resizer(this,this)
{
	skinChooser.setBounds(0,0,getWidth(),controllHeight);
	skinChooser.addListener(this);
	addAndMakeVisible(&skinChooser);
    addAndMakeVisible(resizer);
    resizer.setAlpha(0);
    this->setOpaque(false);
    this->resizer.addMouseListener(this, true);
    
    this->setFixedAspectRatio((double)this->skin->graphicArea.getWidth() / (double)this->skin->graphicArea.getHeight());
    
    this->setMinimumSize(this->skin->graphicArea.getWidth() / 10, this->skin->graphicArea.getHeight()/10);
    this->setMaximumSize(this->skin->graphicArea.getWidth() * 10, this->skin->graphicArea.getHeight()*10);
    
    if(scale != -1)
    {
        this->setScale(scale);
    }
    else if(this->skin->getScale() < 0)
    {
        this->skin->scaleToScreen();
    }
    
	changeListenerCallback(&skin->getComps());
    
    skin->addChangeListener(this);
    skin->scale.addListener(this);
    skin->getComps().addChangeListener(this);
    this->skin->graphicArea.addChangeListener(this);
}

SkinGUI::~SkinGUI()
{
    if(this->skin)
    {
        skin->removeChangeListener(this);
        skin->graphicArea.removeChangeListener(this);
        skin->scale.removeListener(this);
        skin->getComps().removeChangeListener(this);
    }
}

Skin* SkinGUI::getSkin()const
{
    return this->skin;
}

void SkinGUI::checkBounds (Rectangle<int>& bounds, const Rectangle<int>& previousBounds, const Rectangle<int>& limits, bool isStretchingTop, bool isStretchingLeft, bool isStretchingBottom, bool isStretchingRight)
{
    ComponentBoundsConstrainer::checkBounds(bounds, previousBounds, limits, isStretchingTop, isStretchingLeft, isStretchingBottom, isStretchingRight);
    
    this->skin->setScale(this->getScaleCalculated(bounds));
}

void SkinGUI::refreshCompPositions()
{
    skin->refreshComps(true);
}

double SkinGUI::getScaleCalculated(const Rectangle<int>& c)const
{
    return this->skin->getScaleCalculated(c);
}

double SkinGUI::getScale() const
{
    return this->skin->getScale();
}

void SkinGUI::setScale(double scale)
{
    this->skin->setScale(scale) ;
}

SkinCompGUI* SkinGUI::createCompGUI(SkinComp *comp)
{
    return  new SkinCompGUI(comp,this);
}

void SkinGUI::changeListenerCallback(ChangeBroadcaster* obj)
{
	if(obj == &skin->getComps())
	{
		if(skin->getComps().getNumRows())
		{
            graphics.clear();
            controlls.clear();
            parameters.clear();
            
			skinChooser.setVisible(false);
			for(int i = skin->getComps().getNumRows() ; -- i >= 0  ; )
			{
				SkinCompGUI* comp = this->createCompGUI(skin->getComps().items.getUnchecked(i));
				SkinCompControll* comp2 = new SkinCompControll( skin->getComps().items.getUnchecked(i),this );
                
				graphics.add(comp);
				controlls.add(comp2);
                
				addAndMakeVisible(comp);
				addAndMakeVisible(comp2);
			}
            this->setSize();
		}
        
	}
    if(obj == &this->skin->graphicArea || obj == &skin->getComps())
    {
        this->setSize();
        
    }
    else
    {
        setSize();
    }
    this->refreshCompPositions();
	repaint();
}

void SkinGUI::valueChanged (Value& value)
{
    this->setSize();
}

void SkinGUI::setSize()
{
    if(!skin->graphicArea.isEmpty())
    {
        double w = (double)skin->graphicArea.getWidth()*this->getScale();
        double h = (double)skin->graphicArea.getHeight()*this->getScale();
        SkinViewComp::setSize(w,h);
    }
    else
    {
        SkinViewComp::setSize(getWidth(),controllHeight*(parameters.size()) +20);
    }
    
    repaint();
    
}

void SkinGUI::mouseUp(const MouseEvent& e)
{
    for(int i = this->skin->mouseListeners.size() ; -- i >= 0; )
    {
        MouseListener* l = this->skin->mouseListeners.getUnchecked(i);
        l->mouseUp(e);
    }
}

void SkinGUI::filenameComponentChanged(FilenameComponent* comp)
{
    skin->loadFromFile(comp->getCurrentFile());
}

void SkinGUI::resized()
{
    if(parameters.size())
    {
        for(int i = getNumChildComponents(); -- i >= 0 ; )
        {
            Component* c = getChildComponent(i);
            
            c->setBounds(0,c->getY(),getWidth(),c->getHeight());
        }
    }
    
    this->refreshCompPositions();
    
    resizer.toFront(false);
    resizer.setBounds(getWidth()-controllHeight, getHeight()-controllHeight, controllHeight, controllHeight);
    
    
}

void SkinGUI::paint(Graphics& g)
{
    Rectangle<int> c = skin->graphicArea;
    g.drawImage(skin->backgroundImage,0,0,getWidth(),getHeight(),0,0,skin->backgroundImage.getWidth(),skin->backgroundImage.getHeight());
}