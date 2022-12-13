#include "HitBox.h"

HitBox::HitBox(const std::string& tagName) 
	:mTagName(tagName)
{

}

//-------------------------------------
//   tag–¼‚ÌŽæ“¾
//-------------------------------------
std::string HitBox::GetTag()const {
	return mTagName;
}

