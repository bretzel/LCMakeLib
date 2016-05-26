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

#include "File.h"



/*!
 *
    @file File.c++ This is a very big file that initializes each of the
                   internal and cmake variables sets based on the CMake File templates !
 */

namespace LCMake {

File::List   File::sFiles;

static File::Variable VSV = {"",{""}};



LCMake::File::Variable::Variable(const LString& aID, const LString& aValue)
{
    mLabel = aID;
    mValue.push_back(aValue);
}


LCMake::File::Variable::Variable(const LCMake::File::Variable& V)
{
    mLabel  = V.mLabel;
    mValue  = V.mValue; 
}

LCMake::File::Variable::~Variable()
{
    //lfnl << "CHecking Data:\n";
    for(auto VI : mValue){
        VI.clear();
    }
    mValue.clear();
    mLabel.clear();
}


File::Variable& File::Variable::operator=(const LString::List& Data)
{
    mValue = Data;
    return *this;
}

File::Variable& File::Variable::operator=(const LString& Data)
{
    mValue.clear();
    mValue.push_back(Data);
    return *this;
}

File::Variable& File::Variable::operator<<(const LString::List& Data)
{
    for(auto L : Data) mValue.push_back(L);
    return *this;
}



File::Variable& File::Variable::operator<<(const LString& Data)
{
    mValue.push_back(Data);
    return *this;
}


File::Variable& File::Variable::operator=(const File::Variable& V)
{
    mLabel = V.mLabel;
    mValue = V.mValue;
    return *this;
}

bool File::Variable::operator==(const File::Variable& V)
{
    return mLabel == V.mLabel;
}




File::File(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeFile):
mCMakeTemplateFile(aCMakeTemplateFile),
mCMakeOutputFile(aCMakeFile),
mID(aID)
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



/*!
    @brief Direct access to the variable

    @code
        (*Generator)["Author"].second.push_back("Serge Lussier");
*/

File::Variable& File::operator[](const LString& VariableID)
{
    File::Dictionary::iterator It = mVariables.find(VariableID);
    if(It != File::mVariables.end()) return It->second;
    return VSV;
}

void File::Assign(File::Variable& V, const LString::List& Value)
{
    V.mValue = Value;
}

void File::Assign(File::Variable& V, const LString& Value)
{
    lfnl << "ID:`" << V.mLabel << "\n";
    V.mValue.push_back(Value);
}



///@todo : Contr&ocirc;ler les num. de ligne et colonnes......
int32_t File::BeginParseVariable()
{
    // On '%'  :
    LString VarName;
    char C;
    bool rdelim = false;
    bool prot =false;
    mInFile.get(C);
    if(C == '`'){
        mInFile.get(C);
        rdelim = false;
        prot = true;
    }
    while(!mInFile.eof()){
        mInFile.get(C);
        if(C == '`'){
            if(!prot)
                throw LexerMsg::PushError(ErrCode::Invalid) + "Malformed variable name substitution";
            mInFile.get(C);
            break;
        }
        if(!isalnum(C))
            break;
        VarName << C;
    }
    if(mInFile.eof())
        throw LexerMsg::PushError(ErrCode::Eeof) + " - Unexpected" ;
    if(VarName.empty())
        throw LexerMsg::PushError(ErrCode::NullValue) + " Variable identifier cannot be null";
    if(prot && !rdelim){
        throw LexerMsg::PushError(ErrCode::Invalid) + "Malformed variable name substitution";
    }
    File::Variable& Var = (*this)[VarName];
    if(Var.mLabel.empty()){
        File* F = File::QueryGenerator("CMakeMaster");
        Var = (*F)[VarName];
        if(Var.mValue.empty())
            throw LexerMsg::PushError(ErrCode::ObjectNotFound) + LString("%s").Arg(VarName);
    }
    EndParseVariable(Var); // Variable contents to be expanded out to the output file, which is directly accessible from the derived specialized Generators
    ///@todo check that the cursor is at the right position into the input file....
    return ErrCode::Ok;
}



int32_t File::CloseInput()
{
    return 0;
}

int32_t File::CloseOutput()
{
    mOutFile.close();
    return ErrCode::Ok;
}

int32_t File::OpenInput()
{
    mInFile.open(mCMakeTemplateFile.c_str(), std::ios::in);
    if(!mInFile.good())
        throw LexerMsg::PushError(ErrCode::Rejected, 0) + LString("Input Template: [%s] - %s").Arg(mCMakeTemplateFile).Arg(strerror(errno));

    return ErrCode::Ok;
}

int32_t File::OpenOutput()
{
    mOutFile.open(mCMakeOutputFile.c_str(), std::ios::out);
    if(!mOutFile.good())
        throw LexerMsg::PushError(ErrCode::Rejected, 0) + LString("Output File:[%s] - %s").Arg(mCMakeOutputFile).Arg(strerror(errno));

    return ErrCode::Ok;
}

int32_t File::Generate()
{
    char C;
    LString VarName;
    try{
        while(mInFile.eof()){
            mInFile.get(C);
            if(C=='%'){
                BeginParseVariable();
                continue;
            }
            mOutFile << C;
        }
        return ErrCode::Ok;
    }
    catch(LexerMsg E){
        CloseInput();
        CloseOutput();
        throw E;
    }
    return ErrCode::Ok;
}


}
