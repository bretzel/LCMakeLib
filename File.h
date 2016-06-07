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
#include <LexMessage.h>


#include <utility>
#include <map>
#include <fstream>
#include <errno.h>
#include <LexMessage.h>

namespace LCMake {


struct File {


protected:

    LString         mCMakeTemplateFile;
    LString         mCMakeOutputFile;

    LString         mID;
    std::ofstream   mOutFile;
    std::ifstream   mInFile;

public:
    
    struct Variable final{
        LString       mID;
        LString       mLabel;
        LString::List mValue;

        typedef LString::List::iterator ValueIterator;

        Variable(){}
        Variable(const LString& aID, const LString& aLabel,const LString& aValue);
        Variable(const Variable& V);

        ~Variable();
        
        //- --------------------- CUSTOM OPERATORS ----------------
        // ...
        Variable& operator = (const Variable& V);
        Variable& operator = (const LString& Data);
        Variable& operator = (const LString::List& Data);
        Variable& operator << ( const LString& Data);
        Variable& operator << (const LString::List& Data);
        Variable& operator >>(LString& Value);
        bool      operator !(){ return mValue[0].empty(); }

        // -------------- Sous réserve -------------------------
        template<typename T> Variable& operator >> (T& Value){
            LString V;
            (*this) >> V;
            if(V.empty()) return *this;
            V >> Value;  // std:ostrstream magic....
            return *this;
        }
        // -----------------------------------------------------
        void Reset();
        Variable& Clear(){
            mValue.clear();
            return *this;
        }
        bool operator == (const Variable& V);
        //- -------------------------------------------------------
        ValueIterator mValueIterator;
        static Variable& GC();
    };
    
    typedef std::map<LString, File*>          List;
    typedef std::map<LString, Variable>       Dictionary;

    static List sFiles;
    static int      PushFile(File* F);
    static File*    PopFile(const LString aID);
    static File*    FileInstance(const LString aID);
    Dictionary  mVariables;
    File(){}
    File(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeOutputFile);

    Variable& operator[](const LString& VariableID);

    Dictionary& Variables() { return mVariables; } ///< Yeah, Unprotected, Writable.
    static int32_t PushGenerator(const LString& ID, File* pFile);
    static File* QueryGenerator(const LString& ID);

    LString ID() const { return mID; }
    void    SetID(const LString& aID){
        mID = aID;
    }

    int32_t   OpenInput();
    int32_t   CloseInput();
    int32_t   OpenOutput();
    int32_t   CloseOutput();

    int32_t   Generate();

    int32_t BeginParseVariable();
    virtual int32_t EndParseVariable(File::Variable& Var) = 0;
};




template<typename Generator> class CMakeFile : public File
{

public:

    typedef int32_t (Generator::*GeneratorFN)(File::Variable& );
    typedef std::map<LString, typename CMakeFile<Generator>::GeneratorFN> VariableParser;

    CMakeFile(): File(){}
    CMakeFile(const LString aID, const LString& aCMakeTemplateFile, const LString& aCMakeOutputFile): File(aID, aCMakeTemplateFile,aCMakeOutputFile){}

    virtual ~CMakeFile(){
        mParsers.clear();
    }

    //virtual int32_t EndParseVariable() = 0;

protected:
    VariableParser mParsers;
    GeneratorFN operator()(const LString& aID){
        GeneratorFN Fn;
        if(mParsers.find(aID) == mParsers.end())
            throw LexerMsg::PushError(ErrCode::ObjectNotFound) + LString(" No Generator-handler for variable %s").Arg(aID);
        return mParsers[aID];
    }

};



}

