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

Target::List Target::sTargets;


Target::Target(LObject* aParent, const LString& aID, Target::Type aType): LObject(aParent, aID),
mTargetType(aType)
{
    Target::sTargets[aID] = this;
}


Target::Target()
{

}

Target::Target(const Target& other)
{

}

Target::~Target()
{
    Target::sTargets.erase(ID());
}

Target& Target::operator=(const Target& other)
{
    return *this;
}

bool Target::operator==(const Target& other) const
{
    return ID() == other.ID();
}



Target* Target::Seek(const LString& aID)
{
    Target::List::iterator It = Target::sTargets.find(aID);
    return It != Target::sTargets.end() ? It->second : 0;
}


}
