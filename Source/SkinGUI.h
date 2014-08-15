#pragma once
#include "JuceHeader.h"
#include "SkinViewComp.h"

class SkinCompGUI;
class SkinComp;
class SkinCompControll;

class SkinGUI :
public SkinViewComp,
public FilenameComponentListener,
public ComponentBoundsConstrainer,
public Value::Listener
{
public:
	SkinGUI(Skin* skin,double scale = -1);
	~SkinGUI();
    
	void changeListenerCallback(ChangeBroadcaster* ob)override;
    
	void paint(Graphics& g)override;
    void resized()override;
    void mouseUp(const MouseEvent& e) override;
    
	void filenameComponentChanged(FilenameComponent* comp)override;
    
    void valueChanged (Value& value)override;
    
    void refreshCompPositions();
    
    void checkBounds (Rectangle<int>& bounds, const Rectangle<int>& previousBounds, const Rectangle<int>& limits, bool isStretchingTop, bool isStretchingLeft, bool isStretchingBottom, bool isStretchingRight) override;
    
    double getScale()const;
    double getScaleCalculated(const Rectangle<int>& c)const;
    void setScale(double scale);
    
    virtual SkinCompGUI* createCompGUI(SkinComp*);
    
    Skin* getSkin()const;
    
protected:
    void setSize();
    
	OwnedArray<SkinCompGUI> graphics;
	OwnedArray<SkinCompControll> controlls;
    
    /**
     generic ui paramters
     */
	OwnedArray<Component> parameters;
	FilenameComponent skinChooser;
    TooltipWindow tooltipWindow;
    ResizableCornerComponent resizer;
    double scale;
    
    JUCE_LEAK_DETECTOR(SkinGUI)
};