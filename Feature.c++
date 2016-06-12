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
#include <Journal>

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
    mDir.Open("/usr/share");
    LString::List L;
    int n = mDir.ListFiltered(L, {"cmake-","",""});
    LString ModDir;
    if(n != 1){
        mDir.Close();
        throw LexerMsg::PushError(ErrCode::Required) + LString(" one element, got %d").Arg(n);
    }

    ModDir = LString("/usr/share/%s/Modules").Arg(L.front());
    JFnInfo << cwhite << "Found:" << cyellow << L.front() << ends;
    JFnInfo << cwhite << "CMake System Modules Subdirectory:" << cyellow << ModDir << ends;
    mDir.Close();
    L.clear();
    if(mDir.Open(ModDir)){
        n = mDir.ListFiltered(L, {"Find","", ".cmake"});
        if(n > 0){
            for(LString A : L){
                JCNote << cyellow << A << creset << ends;
            }
        }
        else {
            JCNote << cyellow << "No Find*.cmake" << creset << ends;
        }
    }
    // Assume for now..,... Disons que
    mDir.Close();
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
