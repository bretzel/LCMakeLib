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

#include "Target.h"

namespace LCMake {


Target Target::Null("", Target::Enum::Null);

Target::Target(const LString& aID, Target::Enum aType):
mType(aType),
mName(aID)
{

}


Target::Target()
{

}

Target::Target(const Target& tg)
{
    mName = tg.mName;
    mType = tg.mType;
    mDeps = tg.mDeps;
    mLibrariesDependList = tg.mLibrariesDependList;
}

Target::~Target()
{
    mDeps.clear();
    mName.clear();
}

Target& Target::operator=(const Target& tg)
{
    lfnl << chblue << tg.Name() << creset << "\n";
    mName = tg.mName;
    mType = tg.mType;
    mDeps = tg.mDeps;
    mLibrariesDependList = tg.mLibrariesDependList; // Deep copy.
    return *this;
}

bool Target::operator==(const Target& other) const
{
    return (mName == other.mName) && (mType == other.mType);
}


LString Target::Type(Target::Enum TG)
{
    std::map<Target::Enum, LString> Tp;
    Tp[Target::Enum::APP    ] ="RUNTIME";
    Tp[Target::Enum::DYNAMIC] ="LIBRARY";
    Tp[Target::Enum::STATIC ] = "ARCHIVE";


    return Tp[TG];
}


/*!
    @brief Appends Module Name's variable ( ID part of the CMAKE Variables ) into the list of dependencies.
 */
Target& Target::operator<<(const LString& dep)
{
    mDeps.push_back(dep);
    return *this;
}


/*!
    @brief Clears the target data so the instance can be compared as NULL target against other instances.
 */
bool Target::Clear()
{
    if(mDirty){
        ///@todo Signal a warning before rejecting this clear request.
        return false;
    }
    mDeps.clear();
    mLibrariesDependList.clear();
    mName = "";
    mType = Target::Enum::Null;
    return true;
}


}
