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
}

Target::~Target()
{
    mDeps.clear();
    mName.clear();
}

Target& Target::operator=(const Target& tg)
{
    mName = tg.mName;
    mType = tg.mType;
    mDeps = tg.mDeps;
    return *this;
}

bool Target::operator==(const Target& other) const
{
    return (mName == other.mName) && (mType == other.mType);

}


LString Target::Type(Target::Enum TG)
{
    std::map<Target::Enum, LString> Tp;
    Tp[Target::APP    ] ="RUNTIME";
    Tp[Target::DYNAMIC] ="LIBRARY";
    Tp[Target::STATIC ] = "ARCHIVE";


    return Tp[TG];
}

Target& Target::operator<<(const LString& dep)
{
    mDeps.push_back(dep);
    return *this;
}


}
