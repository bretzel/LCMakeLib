/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016 Serge Lussier (Bretzelus-I), lussier.serge@gmail.com
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

//#ifndef LCMAKE_MASTER_H
//#define LCMAKE_MASTER_H
// Disabled protected include, using pragma:
#pragma once
#include <File.h>
#include <Target.h>
namespace LCMake {

class CMakeTemplate : public CMakeFile<LCMake::CMakeTemplate>
{

    Target::List    mTargets;
    LString         mBasePath;

    //
    LString::List   mIncludeDirsList;     ///< Global repo of the CMAKE_INCLUDE variables set by the Modules Dependency no matter the target
    LString::List   mLibrariesDependList; ///< Global repo of the List of CMAKE variables set for the Libraries dependency


public:

    CMakeTemplate();
    CMakeTemplate(const CMakeTemplate& other);
    CMakeTemplate(const LString& aID, const LString& aBasePath);
    ~CMakeTemplate();
    CMakeTemplate& operator=(const CMakeTemplate& other);
    bool operator==(const CMakeTemplate& other) const;

    int32_t xValue             (File::Variable& Var);    // Single Value
    int32_t xModulesDependency (File::Variable& Var);    // Specialized Generator
    int32_t xInstallTargets    (File::Variable& Var);    // Specialized Generator
    int32_t xTargets           (File::Variable& Var);    // Specialized Generator

    CMakeTemplate&  operator << (const Target& TG);

    virtual int32_t EndParseVariable(Variable& Var);
    Target::List    Targets(){ return mTargets; } // Deep; recursive copies. Yup...
    Target          TargetByID(const LString& aID);
    void            UpdateTargetByID(const LString& aID, const LCMake::Target& Tg);

};

}

// disabled include protection, using pragma instead
//#endif // LCMAKE_MASTER_H
