#include "Skin.h"
#include "SkinComp.h"

namespace BinaryData
{
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

void Skin::loadDefault()
{
    int dummy;
    XmlDocument d(BinaryData::getNamedResource("skin_d3ckskin", dummy));
    ScopedPointer<XmlElement> el = d.getDocumentElement();
    this->loadFromXml(el);
}

void Skin::initSize()
{
    this->scaleToScreen();
}

void Skin::refreshComps(bool sync)
{
    for(int i = this->getComps().getNumRows() ; -- i >= 0 ; )
    {
        SkinComp* s = dynamic_cast<SkinComp*>(comps.getItem(i));
        if(sync)
        {
            s->sendSynchronousChangeMessage();
        }
        else
        {
            s->sendChangeMessage();
        }
    }
}

const File& Skin::getFile() const
{
    return this->file;
}

bool Skin::showPopups() const
{
    return this->popupsVisible.getValue();
}

Skin::Skin():
SimpleNamableObject(this)
{
    this->scale = -1;
    this->popupsVisible = true;
}

Skin::~Skin()
{
    masterReference.clear();
}

double Skin::getScale()const
{
    return this->scale.getValue();
}
void Skin::setScale(double scale,bool sendChangeMess)
{
    const double rounded = scale;
    if(this->scale != rounded)
    {
        this->scale = rounded;
        if(sendChangeMess)
        {
            sendChangeMessage();
            this->refreshComps(true);
        }
        else
        {
            this->refreshComps(false);
            
        }
    }
}

Array<PropertyComponent*> Skin::getPropertyComponents() const
{
    Array<PropertyComponent*> arr;
    arr.add(new SliderPropertyComponent(this->scale,"scale",0.1,10,0.1,1));
    return arr;
}

String Skin::getPropertySectionName()const
{
    return "ui";
}

const String Skin::getImageFormatEnding(ImageFileFormat* format)
{
    
	if(dynamic_cast<PNGImageFormat*>(format)) return "png";
	if(dynamic_cast<GIFImageFormat*>(format)) return "gif";
	if(dynamic_cast<JPEGImageFormat*>(format)) return "jpg";
	return "jpg";
}

SkinComp* Skin::createComp()
{
    return new SkinComp(this);
}

SkinComp* Skin::operator[](const String& id)
{
    for(int i = this->getComps().getNumRows() ; -- i >= 0 ; )
    {
        SkinComp* s = dynamic_cast<SkinComp*>(comps.getItem(i));
        if(s && s->getName() == id)
        {
            return s;
        }
    }
    return nullptr;
}

double Skin::getScreenScale()const
{
    double desiredW = (double)Desktop::getInstance().getDisplays().getMainDisplay().userArea.getWidth() * (double)this->screenRatio.getValue();
    double desiredH = (double)Desktop::getInstance().getDisplays().getMainDisplay().userArea.getHeight() * (double)this->screenRatio.getValue();
    return this->getScaleCalculated(Rectangle<int>(desiredW,desiredH));
}

void Skin::scaleToScreen(double maxRatio)
{
    this->setScale(this->getScreenScale());
}

double Skin::getMaxOriginalSize()const
{
    return jmax( this->backgroundImage.getWidth() , this->backgroundImage.getHeight());
}

double Skin::getScaleCalculated(const Rectangle<int>& c)const
{
    const double w = (double)c.getWidth() / (double)this->getWidth();
    const double h = (double)c.getHeight() / (double)this->getHeight();
    return jmin(w,h)  ;
}

int Skin::getWidth()const
{
    return this->backgroundImage.getWidth();
}

int Skin::getHeight()const
{
    return this->backgroundImage.getHeight();
}

Image Skin::getFromFileOrMemory(const File& file,const String& prefix)
{
    int size;
    const void* imgData = BinaryData::getNamedResource((prefix + file.getFileName().replace(".", "_")).toRawUTF8(),size);
    Image img = file.exists() ? ImageCache::getFromFile( file) : ImageCache::getFromMemory(imgData, size);
    return img;
}

double Skin::getScreenRatio() const
{
    return this->screenRatio.getValue();
}

void Skin::setScreenRatio(double ratio)
{
    this->screenRatio = ratio;
    this->scaleToScreen();
}

OwnedList<SkinComp>& Skin::getComps()const
{
    return const_cast<Skin*>(this)->comps;
}


void Skin::loadFromXml(XmlElement* el)
{
    
    this->clear();
	jassert( el->getTagName().equalsIgnoreCase("skin"))
    
	this->setName(  el->getStringAttribute("name" ));
    
    this->screenRatio = el->getDoubleAttribute("screenRatio",0.5);
    
    this->graphicArea = Rectangle<int>::fromString( el->getStringAttribute("bounds" ));
    
    File file = this->file.getParentDirectory().getChildFile("background."+getImageFormatEnding());
    backgroundImage = Skin::getFromFileOrMemory(file);
	
    
	XmlElement* c = el->getChildByName("comps");
	if(c)
	{
		XmlElement* comp = c->getFirstChildElement();
		while(comp)
		{
			SkinComp* skinComp = this->createComp();
            skinComp->setList(&comps);
			skinComp->setFromXml(comp);
			comp = comp->getNextElement();
		}
	}
    this->initSize();
}

void Skin::clear()
{
    while(this->getComps().getNumRows())
    {
        this->comps.getLast()->moveToTrash();
    }
    sendChangeMessage();
}

void Skin::loadFromFile(const File& file)
{
    XmlDocument doc(file);
    ScopedPointer<XmlElement> el = doc.getDocumentElement();
    if(el)
    {
        this->file = file;
        loadFromXml(el);
    }
	
}
