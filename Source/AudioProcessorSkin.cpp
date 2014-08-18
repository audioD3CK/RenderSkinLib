#include "AudioProcessorSkin.h"
#include "AudioProcessorSkinComp.h"
AudioProcessorSkin::AudioProcessorSkin(AudioProcessor* p)
{
    this->processor = p;
    this->processor->addListener(this);
}

AudioProcessorSkin::~AudioProcessorSkin()
{
    this->processor->removeListener(this);
    masterReference.clear();
}

SkinComp* AudioProcessorSkin::createComp()
{
    return new AudioProcessorSkinComp(this);
}

void AudioProcessorSkin::audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)
{
    
}

void AudioProcessorSkin::audioProcessorChanged (AudioProcessor* processor)
{
    
}

AudioProcessor* AudioProcessorSkin::getProcessor()const
{
    return processor;
}

