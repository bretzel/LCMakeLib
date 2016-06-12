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
#include <CDef.h>
#include <Journal>


/*!
 *
    @file File.c++ This is a very big file that initializes each of the
                   internal and cmake variables sets based on the CMake File templates !
 */

namespace LCMake {

File::List   File::sFiles;

LDirInfo       File::mDir;
LString::List  File::mCMakeSysModules;
LString::List  File::mCMakeCustomModules;
LString        File::mProjectBasePath;
File::List     File::mFiles;


static File::Variable VSV = {"UndefCollector", "Undef Collector",{""}};



LCMake::File::Variable::Variable(const LString& aID, const LString& aLabel, const LString& aValue)
{
    mID    = aID;
    mLabel = aLabel;
    mValue.push_back(aValue);
    mValueIterator = mValue.begin();

}


LCMake::File::Variable::Variable(const LCMake::File::Variable& V)
{
    mID     = V.mID;
    mLabel  = V.mLabel;
    mValue  = V.mValue; 
    mValueIterator = mValue.begin();
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


File* File::PopFile(const LString aID)
{
    File::List::iterator I = File::sFiles.find(aID);
    File* F;
    if(I != File::sFiles.end()){
        F = I->second;
        File::sFiles.erase(I); // Popping ...
        return F;
    }
    return 0;
}

File* File::FileInstance(const LString aID)
{
    File::List::iterator I = File::sFiles.find(aID);
    if(I != File::sFiles.end())
        return  I->second;
    return 0;
}

int File::PushFile(File* F)
{
    File::List::iterator I = File::sFiles.find(F->ID());
    if(I != File::sFiles.end()) return -1;
    File::sFiles[F->ID()] = F;
    return File::sFiles.size();
}



File::Variable& File::Variable::operator=(const LString::List& Data)
{
    mValue.clear();
    mValue = Data;
    mValueIterator = mValue.begin();
    return *this;
}

File::Variable& File::Variable::operator=(const LString& Data)
{
    mValue.clear();
    mValue.push_back(Data);
    mValueIterator = mValue.begin();
    return *this;
}

File::Variable& File::Variable::operator<<(const LString::List& Data)
{
    for(auto L : Data) mValue.push_back(L);
    mValueIterator = --mValue.end();
    return *this;
}



File::Variable& File::Variable::operator<<(const LString& Data)
{
    mValue.push_back(Data);
    mValueIterator = --mValue.end();
    return *this;
}


File::Variable& File::Variable::operator=(const File::Variable& V)
{
    mLabel = V.mLabel;
    mValue = V.mValue;
    mValueIterator = mValue.begin();
    return *this;
}

bool File::Variable::operator==(const File::Variable& V)
{
    return mLabel == V.mLabel;
}

File::Variable& File::Variable::operator>>(LString& Value)
{
    if(mValueIterator != mValue.end()){
        Value = *mValueIterator;
        ++mValueIterator;
    }
    else
        Value.clear();

    LexerMsg::PushWarning(ErrCode::Oob) + "Variable [" + mID + "]-> Out of range ";
    return *this;
}

void File::Variable::Reset()
{
    mValueIterator = mValue.begin();
}



File::Variable&   File::Variable::GC()
{
    return VSV; // See what's of undef catched
}



File::File(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeFile):
mCMakeTemplateFile(aCMakeTemplateFile),
mCMakeOutputFile(aCMakeFile),
mID(aID)
{
    File::PushFile(this);
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

        VarName << C;
        mInFile.get(C);
        if(C == '`'){
            if(!prot)
                throw LexerMsg::PushError(ErrCode::Invalid) + "Malformed variable name substitution";
            //mInFile.get(C);
            break;
        }
        if(!isalnum(C))
            break;
    }

    if(mInFile.eof())
        throw LexerMsg::PushError(ErrCode::Eeof) + " - Unexpected" ;
    if(VarName.empty())
        throw LexerMsg::PushError(ErrCode::NullValue) + " Variable identifier cannot be null";
    if(prot && !rdelim){
        throw LexerMsg::PushError(ErrCode::Invalid) + "Malformed variable name substitution";
    }

    lfnl << "To Query [" << chgreen << VarName << creset << "]:\n";

    File::Variable& Var = (*this)[VarName];
    if(Var.mLabel.empty()){
        File* F = File::QueryGenerator("CMakeMaster");
        if(!F) {
            throw LexerMsg::PushError(ErrCode::ObjectNotFound) + LString(" [%s%s]").Arg(Colors::Data::Ansi(Colors::Enum::Orange210)).Arg(VarName);
        }
        Var = (*F)[VarName];
        if(Var.mValue.empty())
            throw LexerMsg::PushError(ErrCode::ObjectNotFound) + LString("%s").Arg(VarName);
    }
    EndParseVariable(Var); // Variable contents to be expanded out to the output file, which is directly accessible from the derived specialized Generators
    mOutFile << C;
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
    lfnl << ":\n";
    mInFile.open(mCMakeTemplateFile.c_str(), std::ios::in);
    if(!mInFile.good())
        throw LexerMsg::PushError(ErrCode::Rejected, 0) + LString("Input Template: [%s] - %s").Arg(mCMakeTemplateFile).Arg(strerror(errno));

    return ErrCode::Ok;
}

int32_t File::OpenOutput()
{
    lfnl << ":\n";
    mOutFile.open(mCMakeOutputFile.c_str(), std::ios::out);
    if(!mOutFile.good())
        throw LexerMsg::PushError(ErrCode::Rejected, 0) + LString("Output File:[%s] - %s").Arg(mCMakeOutputFile).Arg(strerror(errno));

    return ErrCode::Ok;
}

int32_t File::Generate()
{
    lfnl << ":\n";
    char C;
    LString VarName;
    try{
        while(!mInFile.eof()){
            mInFile.get(C);
            std::cout << C;
            if(C=='%'){
                BeginParseVariable();
                continue;
            }
            mOutFile << C;
        }
        CloseInput();
        CloseOutput();
        return ErrCode::Ok;
    }
    catch(LexerMsg E){
        CloseInput();
        CloseOutput();
        throw E;
    }
    return ErrCode::Ok;
}




const LString::List& File::ListCMakeCustomModules()
{
    return {""};
}

const LString::List& File::ListCMakeSystemModules()
{
    mDir.Open("/usr/share");
    LString::List L;
    int n = mDir.ListFiltered(L, {"cmake-","",""});
    LString ModDir;
    if(n != 1){
        mDir.Close();
        throw LexerMsg::PushError(ErrCode::Required) + LString(" one element, got %d").Arg(n);
    }

    ModDir = LString("/usr/share/%s/Modules").Arg(L.front());
    JFnInfo << cwhite << "Found:" << cyellow << L.front() << ends;
    JFnInfo << cwhite << "CMake System Modules Subdirectory:" << cyellow << ModDir << ends;
    mDir.Close();
    L.clear();
    if(mDir.Open(ModDir)){
        n = mDir.ListFiltered(L, {"Find","", ".cmake"});
        if(n > 0){
            for(LString A : L){
                JCNote << cyellow << A << creset << ends;
            }
        }
        else {
            JCNote << cyellow << "No Find*.cmake" << creset << ends;
        }
    }
    // Assume for now..,... Disons que
    mDir.Close();
    return File::mCMakeCustomModules;
}





}
