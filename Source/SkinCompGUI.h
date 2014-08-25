#pragma once
#include "BoundDrivenComponent.h"

class SkinComp;
class SkinGUI;

class SkinCompGUI :
public BoundDrivenComponent,
public AudioProcessorListener

{
public:
	SkinCompGUI(SkinComp* comp,SkinGUI* skinGUI);
	~SkinCompGUI();
    
	virtual void paint(Graphics& g)override;
	void changeListenerCallback(ChangeBroadcaster* obj)override;
    virtual void audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)override;
    virtual void audioProcessorChanged (AudioProcessor* processor)override;
    double getScale()const override;
    void resized()override;
    Point<int> getOffset()const override;
    
    bool useMask()const;
    Image getMask();
    
protected:
    Image mask;
	WeakReference<SkinComp> comp;
    SafePointer<SkinGUI> skinGUI;
};