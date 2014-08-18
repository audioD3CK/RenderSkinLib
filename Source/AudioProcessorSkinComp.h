#pragma once
#include "SkinComp.h"

class AudioProcessorSkin;

class AudioProcessorSkinComp :
public AudioProcessorListener,
public SkinComp
{
public:
    AudioProcessorSkinComp(AudioProcessorSkin* skin);
    ~AudioProcessorSkinComp();
    void audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)override;
    void audioProcessorChanged (AudioProcessor* processor)override;
    
    
    virtual void setValue(double) override;
    virtual double getValue()const override;

    
private:
    WeakReference<AudioProcessorSkin> skin;
    
    WeakReference<AudioProcessorSkinComp>::Master masterReference;
    friend class WeakReference<AudioProcessorSkinComp>;

};