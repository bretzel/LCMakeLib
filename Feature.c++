/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Feature.h"
#include "FindCMakeTemplate.h"
#include "LCMakeLists.h"
#include "Target.h"
#include <stdlib.h>

namespace LCMake {


LDirInfo       Feature::mDir;
LString::List  Feature::mCMakeSysModules;
LString::List  Feature::mCMakeCustomModules;
LString        Feature::mProjectBasePath;
File::List     Feature::mFiles;


const LString::List& Feature::ListCMakeCustomModules()
{

    //...
    return Feature::mCMakeCustomModules;
}

const LString::List& Feature::ListCMakeSystemModules()
{
    //...
    return Feature::mCMakeCustomModules;
}

Feature::~Feature()
{
}


LString& Feature::DefaultProjectBasePath()
{
    Feature::mProjectBasePath = LString("%s/Applications").Arg(getenv("HOME"));
    return Feature::mProjectBasePath;
}



}
