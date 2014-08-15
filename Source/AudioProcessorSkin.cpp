#include "AudioProcessorSkin.h"

AudioProcessorSkin::AudioProcessorSkin(AudioProcessor* p)
{
    this->processor = p;
    this->processor->addListener(this);
}

AudioProcessorSkin::~AudioProcessorSkin()
{
    this->processor->removeListener(this);
}

void AudioProcessorSkin::audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)
{
    
}

void AudioProcessorSkin::audioProcessorChanged (AudioProcessor* processor)
{
    
}
