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

#include "File.h"
#include <LexMessage.h>


/*!
 *
    @file File.c++ This is a very big file that initializes each of the
                   internal and cmake variables sets based on the CMake File templates !
 */

namespace LCMake {

File::List   File::sFiles;

static File::Variable VSV = {"",{""}};




File::File(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeFile):
mID(aID),
mCMakeTemplateFile(aCMakeTemplateFile),
mCMakeOutputFile(aCMakeFile)
{
}

int32_t File::PushGenerator(const LString& ID, File* pFile)
{

    if(File::sFiles.find(ID) == File::sFiles.end())
        File::sFiles[ID] = pFile;
    else
        return ErrCode::Redeclared;
    //...
    return ErrCode::Ok;
}

File* File::QueryGenerator(const LString& ID)
{
    File::List::iterator It = File::sFiles.find(ID);
    if(It != File::sFiles.end()) return It->second;
    return 0;
}


File::Variable& File::operator[](const LString& VariableID)
{
    File::Dictionary::iterator It = mVariables.find(VariableID);
    if(It != File::mVariables.end()) return It->second;
    return VSV;
}



}



