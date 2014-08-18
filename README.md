The most simple way to use this is to create a new instance of [AudioProcessorSkin](/dasdeck/RenderSkinLib/blob/master/Source/AudioProcessorSkin.h) and pass your [AudioProcessor](/julianstorer/JUCE/blob/master/modules/juce_audio_processors/processors/juce_AudioProcessor.h) in the constructor.

```c++
#include "AudioProcessorSkin.h"
#include "SkinGUI.h"

...

AudioProcessor* myProcessor = createSomeProcessor();
AudioProcessorSkin skin(myProcessor);
skin.loadFromFile(File("/path/to/a/skin/file/created/with/RenderSkin.d3ckskin"));

SkinGUI gui(&skin);


```

The public interfaces are not yet secured very much, so you may want to use them with caution.
The expand the skin's behaviour take a look at the two classes
[AudioProcessorSkin](/dasdeck/RenderSkinLib/blob/master/Source/AudioProcessorSkin.h)
and
[AudioProcessorSkinComp](/dasdeck/RenderSkinLib/blob/master/Source/AudioProcessorSkinComp.h),
the extend the basic Skin class withe methods to wrap an AudioProcessor.
