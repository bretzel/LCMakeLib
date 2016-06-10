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

//#ifndef LCMAKE_FEATURE_H
//#define LCMAKE_FEATURE_H
// Disabled protected include, using pragma:
#pragma once

#include <LDirInfo>
#include <File.h>

namespace LCMake {

struct Feature final
{
    Feature() = delete;
    ~Feature();

    static const LString::List& ListCMakeSystemModules();
    static const LString::List& ListCMakeCustomModules();
    static LString& ProjectBasePath() { return Feature::mProjectBasePath; }
    static LString& DefaultProjectBasePath();
    static LString& ProjectName() { return mProjectName; }

private:
    static LDirInfo mDir;                       ///< Directory scannings
    static LString::List mCMakeSysModules;      ///< Find cmake modules from the system-wide (/usr/share/cmake-?/Modules).
    static LString::List mCMakeCustomModules;   ///< Custom find cmake modules ( $HOME/Applications/CMakeModules )
    static LString  mProjectBasePath;           ///< ... Global Project's base path ... ( default: $HOME/Applications; @see DefaultProjectBasePath)
    static File::List mFiles;                   ///< Involved CMake specialized Generators.
    static LString  mProjectName;               ///< The name of the project is stored here.


};

}

// disabled include protection, using pragma instead
//#endif // LCMAKE_FEATURE_H
