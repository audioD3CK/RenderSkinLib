#pragma once
#include "JuceHeader.h"

#include "SkinComp.h"
#include "PropertySource.h"

#include "OwnedList.h"
#include "BoundsDriver.h"

/**
    class representing th ebackend of a skin
 **/
class Skin:
	public SimpleNamableObject,
    public PropertySource
{
public:
	Skin();
	~Skin();
    
    juce_UseDebuggingNewOperator
    
    virtual SkinComp* createComp();
    
    virtual int getWidth()const;
    virtual int getHeight()const;
    
    virtual void loadFromXml(XmlElement* el);

	void loadFromFile(const File& file);
    void loadDefault();
    void setLastDocumentOpened (const File& file);
	static  const String getImageFormatEnding(ImageFileFormat* f = nullptr);
    SkinComp* operator[](const String& id);
    
    Array<PropertyComponent*> getPropertyComponents() const override;
    String getPropertySectionName()const override;
    
    double getScaleCalculated(const Rectangle<int>& c)const;

    void setScreenRatio(double);
    double getScreenRatio() const;
    void scaleToScreen(double maxRatio = -1);
    
    double getMaxOriginalSize()const;
    
    const File& getFile() const;

    void refreshComps(bool sync);
    static Image getFromFileOrMemory(const File& file,const String& prefix = String::empty);
    
    double getScale()const;
    void setScale(double scale,bool sendChangeMessage = true);

    void initSize();

    void clear();
    
    bool showPopups() const;
    double getScreenScale()const;

    OwnedList<SkinComp>& getComps()const;

    Array<MouseListener*> mouseListeners;

    Image backgroundImage;
    Value scale;
    Value popupsVisible;
    Value screenRatio;

    /**
     the area the background images is trimmed, this is also used to set an offset for the control's positions.
     **/
    BoundsDriver graphicArea;

protected:
    
    OwnedList<SkinComp> comps;
    
    /**
     the file the skin was loaded form, if applicable
     **/
    File file;
    
    JUCE_LEAK_DETECTOR(Skin)
    WeakReference<Skin>::Master masterReference;
    friend class WeakReference<Skin>;
    
};

