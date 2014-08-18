#include "AudioProcessorSkinComp.h"
#include "AudioProcessorSkin.h"
#include "SkinKnob.h"

AudioProcessorSkinComp::AudioProcessorSkinComp(AudioProcessorSkin* skin):
SkinComp(skin)
{
    this->skin = skin;
    skin->getProcessor()->addListener(this);
}

AudioProcessorSkinComp::~AudioProcessorSkinComp()
{
    masterReference.clear();
    skin->getProcessor()->removeListener(this);
}

void AudioProcessorSkinComp::audioProcessorParameterChanged (AudioProcessor* processor, int parameterIndex, float newValue)
{
    if(parameterIndex == this->getParameterIndex())
    {
        sendChangeMessage();
    }
}

void AudioProcessorSkinComp::audioProcessorChanged (AudioProcessor* processor)
{
    
}

void AudioProcessorSkinComp::setValue(double val)
{
    const int index = this->getParameterIndex();
    
    DBG("set:" + String(index) + " - " + String(val));

    this->skin->getProcessor()->setParameterNotifyingHost(index, val);
}
double AudioProcessorSkinComp::getValue()const
{
    const int parameterIndex = this->getParameterIndex();
    const double val = this->skin->getProcessor()->getParameter(parameterIndex);
    DBG("get:" + String(parameterIndex) + " - " + String(val));
    return val;
}
