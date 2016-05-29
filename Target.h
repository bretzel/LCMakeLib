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

    enum Enum {
        APP,     // RUNTIME
        DYNAMIC, // LIBRARY
        STATIC   // ARCHIVE
    };

    Target();
    Target(const Target& other);
    Target(const LString& aID, Target::Enum aType);
    virtual ~Target();

    Target& operator=(const Target& other);
    bool operator==(const Target& other) const;
    LString Name() const { return mName; }
    static LString Type(Target::Enum TG);

private:
    Enum        mType;
    LString     mName;
    
};



}

// disabled include protection, using pragma instead
//#endif // LCMAKE_TARGET_H
