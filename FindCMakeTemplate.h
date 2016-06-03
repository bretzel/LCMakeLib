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

//#ifndef LCMAKE_FINDCMAKETEMPLATE_H
//#define LCMAKE_FINDCMAKETEMPLATE_H
// Disabled protected include, using pragma:
#pragma once

#include <File.h>

namespace LCMake {

class FindCMakeTemplate : public LCMake::CMakeFile<FindCMakeTemplate>
{
public:
    FindCMakeTemplate();
    FindCMakeTemplate(const FindCMakeTemplate& other);
    FindCMakeTemplate(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeOutputFile);
    FindCMakeTemplate& operator=(const FindCMakeTemplate& other);
    bool operator==(const FindCMakeTemplate& other) const;
    virtual ~FindCMakeTemplate();

    int32_t xValue(File::Variable& Var);
    virtual int32_t EndParseVariable(LCMake::File::Variable& Var);
};
}

// disabled include protection, using pragma instead
//#endif // LCMAKE_FINDCMAKETEMPLATE_H
