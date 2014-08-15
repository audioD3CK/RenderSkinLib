#include "SkinComp.h"
#include "Skin.h"
#include "SkinKnob.h"

SkinComp::SkinComp(Skin* skin)
{
	this->skin = skin;
    
    
    this->parameterIndex = 0;
    
	graphicArea.addChangeListener(this);
    
    
	interpolation = (false);
	useControllArea = (false);
    
    this->cliptype = SkinComp::rect;
	sensitivity = 100;
	compType = none;
	framei = 0;
	graphicArea.setBounds(0,0,20,20);
	controllArea.setBounds(0,0,20,20);
    
}

SkinComp::~SkinComp(void)
{
    masterReference.clear();
}

Range<int> SkinComp::getRange()const
{
    return this->frames;
}

double SkinComp::getAbsolutFrame()
{
    const double length = frames.getEnd() - frames.getStart();//-1;
	return length * getFrame() + frames.getStart();
}

int SkinComp::getNumFrames()const
{
    return this->frames.getLength();
}

int SkinComp::getParameterIndex()const
{
    return this->parameterIndex;
}
void SkinComp::setParameterIndex(int i)
{
    this->parameterIndex = i;
    sendChangeMessage();
}

int SkinComp::getSensitivity()const
{
    return this->sensitivity.getValue();
}



const String SkinComp::getHelpText() const
{
    return this->helpText;
}


double SkinComp::getFrame() const
{
    
    return framei;
    
}

double SkinComp::getDefaultFrame()const
{
    return 0;
}

void SkinComp::setFrame(double frame)
{
    
	this->framei = frame;
    
	sendChangeMessage();
}

void SkinComp::setType(CompType type)
{
	this->compType = type;
	sendChangeMessage();
}



SkinComp::ClipType SkinComp::getClipType()const
{
    return this->cliptype;
}

Skin* SkinComp::getSkin() const
{
    return this->skin;
}

SkinComp::CompType SkinComp::getCompType()const
{
    return this->compType;
}

void SkinComp::setClipType(ClipType type)
{
    this->cliptype = type;
}

const File SkinComp::getStripFile(const String& prefix)
{
    const String fileName = prefix+"_"+getName()+"."+skin->getImageFormatEnding();
    
    return File(skin->getFile().getParentDirectory().getChildFile(fileName));
}

Image SkinComp::getMask(const Rectangle<int>& rect)
{
    Image mask = Image(Image::ARGB,rect.getWidth(),rect.getHeight(),true);
    Graphics g(mask);
    g.setColour(Colours::black);
    
    if(getClipType() == SkinComp::ellipse)
    {
        g.fillEllipse(0,0,rect.getWidth(),rect.getHeight());
    }
    else if(getClipType() == SkinComp::smoothrect)
    {
        Rectangle<float> outer(rect.getWidth(),rect.getHeight());
        int border = 40 * this->skin->getScale();
        Rectangle<float> center = outer.withSizeKeepingCentre(rect.getWidth()-border, rect.getHeight()-border);
        g.fillRect(center);
        
        ColourGradient top(Colours::black,center.getX(),center.getY(),Colours::transparentBlack,center.getX(),outer.getY(),false);
        Path p;
        p.startNewSubPath(outer.getTopLeft());
        p.lineTo(outer.getTopRight());
        p.lineTo(center.getTopRight());
        p.lineTo(center.getTopLeft());
        p.closeSubPath();
        g.setFillType(top);
        g.fillPath(p);
        
        ColourGradient left(Colours::black,center.getX(),center.getY(),Colours::transparentBlack,outer.getX(),center.getY(),false);
        p.clear();
        p.startNewSubPath(center.getTopLeft());
        p.lineTo(center.getBottomLeft());
        p.lineTo(outer.getBottomLeft());
        p.lineTo(outer.getTopLeft());
        p.closeSubPath();
        g.setFillType(left);
        g.fillPath(p);
        
        ColourGradient right(Colours::black,center.getRight(),center.getY(),Colours::transparentBlack,outer.getRight(),center.getY(),false);
        p.clear();
        p.startNewSubPath(center.getTopRight());
        p.lineTo(center.getBottomRight());
        p.lineTo(outer.getBottomRight());
        p.lineTo(outer.getTopRight());
        p.closeSubPath();
        g.setFillType(right);
        g.fillPath(p);
        
        ColourGradient bottom(Colours::black,center.getX(),center.getBottom(),Colours::transparentBlack,center.getX(),outer.getBottom(),false);
        p.clear();
        p.startNewSubPath(center.getBottomLeft());
        p.lineTo(center.getBottomRight());
        p.lineTo(outer.getBottomRight());
        p.lineTo(outer.getBottomLeft());
        p.closeSubPath();
        g.setFillType(bottom);
        g.fillPath(p);
        
    }
    else
    {
        g.fillAll();
    }
    
    return  mask;
}

Component* SkinComp::createControllComponent()const
{
    if(getCompType() == SkinComp::slider || getCompType() == SkinComp::togglebutton)
    {
        return new SkinKnob(const_cast<SkinComp*>(this));
    }
    else
    {
        return nullptr;
    }
}



void SkinComp::setFromXml(XmlElement* el)
{
	interpolation = el->getBoolAttribute("interpolation",false);
	useControllArea = el->getBoolAttribute("usecontrollarea",false);
    
	setName(el->getStringAttribute("id"));
	sensitivity.setValue(el->getDoubleAttribute("sensitivity",sensitivity.getValue()));
    
	graphicArea = Rectangle<int>::fromString(el->getStringAttribute("graphicarea"));
	controllArea = Rectangle<int>::fromString(el->getStringAttribute("controllarea"));
	compType = (CompType)el->getIntAttribute("type",none);
	cliptype = (ClipType)el->getIntAttribute("clip",rect);
    
    frames.setStart(el->getIntAttribute("start"));
	frames.setEnd(el->getIntAttribute("end"));

    this->title = el->getStringAttribute("title");
    this->helpText = el->getStringAttribute("help");
    
    
	File stripFile = getStripFile(String(skin->getComps().items.size()+10));
	this->stripImage = Skin::getFromFileOrMemory(stripFile,"_");
    
	sendChangeMessage();
}

void SkinComp::changeListenerCallback(ChangeBroadcaster* obj)
{
	if(obj == &graphicArea && (bool)useControllArea.getValue() == false)
		controllArea = graphicArea;
}

void SkinComp::checkBounds(Rectangle<int>& bounds, const Rectangle<int>& previousBounds, const Rectangle<int>& limits, bool isStretchingTop, bool isStretchingLeft,bool isStretchingBottom,bool isStretchingRight)
{
	bounds.setX(jmax(0,bounds.getX()));
	bounds.setY(jmax(0,bounds.getY()));
	bounds.setWidth(jmax(bounds.getWidth(),4));
	bounds.setHeight(jmax(bounds.getHeight(),4));
}