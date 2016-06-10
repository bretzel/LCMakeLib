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

#include "FindCMakeTemplate.h"
#include "LCMakeLists.h"
namespace LCMake {

FindCMakeTemplate::FindCMakeTemplate(const FindCMakeTemplate& other)
{

}

FindCMakeTemplate::FindCMakeTemplate()
{

}

FindCMakeTemplate::~FindCMakeTemplate()
{

}


FindCMakeTemplate& FindCMakeTemplate::operator=(const FindCMakeTemplate& other)
{
    return *this;
}

bool FindCMakeTemplate::operator==(const FindCMakeTemplate& other) const
{
    return false;
}

FindCMakeTemplate::FindCMakeTemplate(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeOutputFile): CMakeFile< LCMake::FindCMakeTemplate >(aID, aCMakeTemplateFile, aCMakeOutputFile)
{

// Name
//
    mVariables = {
        {"Name", {"Name", "Module Name", {""}}}
    };

    mParsers = {
        {"Name", &FindCMakeTemplate::xValue}
    };

}

int32_t FindCMakeTemplate::xValue(File::Variable& Var)
{
    mOutFile << Var.mValue[0];
    return ErrCode::Implement;
}

int32_t FindCMakeTemplate::EndParseVariable(LCMake::File::Variable& Var)
{
    GeneratorFN G = (*this)(Var.mID);
    lfnl << ":\n";
    if(G)
        return (this->*G)(Var);
    File* F = File::FileInstance("Master");
    if(!F) {
        return ErrCode::ObjectNotFound;
    }
    File::Variable& MasterVar = (*F)[Var.mID];
    if(!MasterVar){
        // Search hard,hard, everywhere! I lost my sonvar ! :-)
        mOutFile << '[' << MasterVar.mID << ": undef]";
        LexerMsg M = LexerMsg::PushWarning(ErrCode::Implement) + LString(" -- No Generator implemented for variable: `%s`").Arg(Var.mID);
        std::cerr << M.cc() << "\n";

        return ErrCode::ObjectNotFound;
    }
    for(LString A : MasterVar.mValue)
        if(!A.empty()) mOutFile <<  A;
        
    return ErrCode::Ok;
}

}
