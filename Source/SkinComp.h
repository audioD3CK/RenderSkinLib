#pragma once
#include "JuceHeader.h"
#include "ListItem.h"
#include "NamableObject.h"
#include "BoundsDriver.h"

class Skin;

/**
 reperestns one control element on a skin
 **/
class SkinComp :
public ComponentBoundsConstrainer,
public ListItem,
public SimpleNamableObject,
public ChangeListener
{
public:
	SkinComp(Skin* skin);
	~SkinComp(void);
    
    juce_UseDebuggingNewOperator
    
	void checkBounds(Rectangle<int>& bounds, const Rectangle<int>& previousBounds, const Rectangle<int>& limits, bool isStretchingTop, bool isStretchingLeft,bool isStretchingBottom,bool isStretchingRight) override;
    void changeListenerCallback(ChangeBroadcaster* obj)override;
    
    virtual Component* createControllComponent();
    
	virtual double getDefaultFrame() const;
    virtual Range<int> getRange()const;
    
    void setUseControllArea(bool b);
    
    virtual void setValue(double frame);
    virtual double getValue() const;

    double getAbsolutFrame();
    
    virtual int getNumFrames()const;
    Image getMask(const Rectangle<int>& rect);
    
    const String getHelpText() const;
    
	const File getStripFile(const String& prefix);
	
	void setFromXml(XmlElement* el);
    
    int getSensitivity()const;
    
    Skin* getSkin()const;
    
    int getParameterIndex()const;
    void setParameterIndex(int);
    
    enum CompType
	{
		none,
		slider,
		togglebutton
	};
	
	enum ClipType
	{
		rect,
		ellipse,
		smoothrect
	};
  
    ClipType getClipType()const;
    void setClipType(ClipType type);
    
    CompType getCompType()const;
    void setType(CompType type);
    
	BoundsDriver graphicArea;
	BoundsDriver controllArea;
    
	Image stripImage;
    
	Value interpolation;
	Value useControllArea;
    Value sensitivity;
    Value gradient;
    
    String helpText;
    String title;
    
protected:
    WeakReference<Skin> skin;
    
    Range<int> frames;
    
    int parameterIndex;
    
    double value;
    
    CompType compType;
    ClipType cliptype;
    
    friend class SkinCompPropsGUI;
    
    JUCE_LEAK_DETECTOR(SkinComp);
    
    WeakReference<SkinComp>::Master masterReference;
    friend class WeakReference<SkinComp>;
};


