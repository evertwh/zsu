/*
 *  zsu.cp
 *  zsu
 *
 *  Created by evert haasdijk on 22/01/2009.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <iostream>
#include "zsu.h"
#include "zsuPriv.h"

void zsu::HelloWorld(const char * s)
{
	 zsuPriv *theObj = new zsuPriv;
	 theObj->HelloWorldPriv(s);
	 delete theObj;
};

void zsuPriv::HelloWorldPriv(const char * s) 
{
	std::cout << s << std::endl;
};

