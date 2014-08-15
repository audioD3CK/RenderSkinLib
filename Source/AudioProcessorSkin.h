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
    
private:
    AudioProcessor* processor;
};