/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  Serge Lussier (Bretzelus-I), lussier.serge@gmail.com
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


#pragma once

#include <LString++.h>


#include <utility>
#include <map>
#include <fstream>
#include <errno.h>


namespace LCMake {


struct File {


protected:

    LString         mCMakeTemplateFile;
    LString         mCMakeOutputFile;
    LString         mID;
    std::ofstream   mOutFile;
    std::ifstream   mInFile;

public:
    typedef std::map<LString, File*>          List;
    typedef std::pair<LString, LString::List> Variable;
    typedef std::map<LString, Variable>       Dictionary;

    static List sFiles;
    Dictionary  mVariables;

    File(const LString aID, const LString& aCMakeTemplateFile);

    Variable& operator[](const LString& VariableID);
    static int32_t PushGenerator(const LString& ID, File* pFile);
    static File* QueryGenerator(const LString& ID);

};


template<typename Generator> class CMakeFile : public File
{

public:

    typedef int32_t (Generator::*GeneratorFN)(File::Variable& );


    CMakeFile(): File(){}
    CMakeFile(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeOutputFile): File(aID, aCMakeTemplateFile,aCMakeOutputFile){

    }
};


}

