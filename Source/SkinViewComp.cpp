#include "SkinViewComp.h"
#include "Skin.h"

SkinViewComp::SkinViewComp(Skin* skin)
{
	this->skin = skin;

}

SkinViewComp::~SkinViewComp()
{

}

void SkinViewComp::childBoundsChanged(Component* comp)
{
	repaint();
}
void SkinViewComp::paint(Graphics& g)
{
    
}

Skin* SkinViewComp::getSkin()const
{
    return this->skin;
}