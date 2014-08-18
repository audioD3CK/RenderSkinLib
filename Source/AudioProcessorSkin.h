#pragma once
#include "Skin.h"

class AudioProcessorSkin:
public AudioProcessorListener,
public Skin
{
public:
    AudioProcessorSkin(AudioProcessor* p);
    ~AudioProcessorSkin();
    void audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)override;
    void audioProcessorChanged (AudioProcessor* processor)override;
    
    virtual SkinComp* createComp()override;

    
    AudioProcessor* getProcessor()const;
    

    
private:
    AudioProcessor* processor;
    
    WeakReference<AudioProcessorSkin>::Master masterReference;
    friend class WeakReference<AudioProcessorSkin>;
};