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

//#ifndef LCMAKE_TARGET_H
//#define LCMAKE_TARGET_H
// Disabled protected include, using pragma:
#pragma once
#include <map>
#include <LString++.h>


namespace LCMake {

struct Target
{

    typedef std::map<LString, Target> List;
    static Target Null;
    enum class Enum : uint8_t{
        APP,     // RUNTIME
        DYNAMIC, // LIBRARY
        STATIC,   // ARCHIVE
        Null
    }; ///< Types of target.

    Target();
    Target(const Target& other);
    Target(const LString& aID, Target::Enum aType);
    virtual ~Target();

    Target& operator=(const Target& other);
    bool operator==(const Target& other) const;
    LString Name() const { return mName; }
    static LString Type(Target::Enum TG);
    Target& operator << (const LString& dep);
    void    SetDepLibsVariablesList(const LString::List& CMakeVariables){ mLibrariesDependList = CMakeVariables; }
    LString::List CMakeLibDepsVars() const { return mLibrariesDependList; }
    LString::List Dependencies() { return mDeps; }
    bool operator !(){ return mType == Enum::Null; }
    Target::Enum Type(){ return mType; }
    void SetType(Target::Enum T){ mType = T; }
    void Clear();
    void SetID(const LString& aID) { mName = aID; }

private:
    Enum        mType;
    LString     mName;
    LString::List mDeps;               ///< Target's specific list of CMake Modules Dependencies.
    mutable LString::List mLibrariesDependList;  ///< Part or complete set of the Libraries depends as ` TARGET_LINK_LIBRARIES(this->mName ${CMAKE_%DEPNAME_LIBARIES}) ` from the Master CMakeLists.

};



}

// disabled include protection, using pragma instead
//#endif // LCMAKE_TARGET_H
