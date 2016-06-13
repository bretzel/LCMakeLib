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

#include "LCMakeLists.h"
#include <Journal++.h>
// ----------- TEMPORAIRE -- POUR FIN DE TESTS ET R&DEV!!..:-) -------------------------------------------------------------------------
#define CMAKE_MASTERTEMPLATE_FILE "../Resources/CMakeLists.MasterTemplate.txt" // As long as the working dir is the Bin subdir
#define CMAKE_OUTPUT_FILENAME   "CMakeLists.txt"
// --------------------------------------------------------------------------------------------------------------------------------


namespace LCMake {

LCMakeLists::LCMakeLists(const LString& aID, const LString& aBasePath): CMakeFile< LCMake::LCMakeLists >(aID, CMAKE_MASTERTEMPLATE_FILE, aBasePath + '/' + CMAKE_OUTPUT_FILENAME),
mBasePath(aBasePath)
{
    /*
     * #   CMakeVersion
     * #   ModulesDependency
     * #   InstallTargets
     *
     */


    mVariables = {
        {"CMakeVersion"      ,{"CMakeVersion"      ,"CMake Minimum Version", {""}}},
        {"ProjectName"       ,{"ProjectName"       ,"Project Name"       , {""}}},
        {"Author"            ,{"Author"            ,"Author"            , {"Serge Lussier"}}},
        {"Email"             ,{"Email"             ,"Email"             , {"lussier.serge@gmail.com"}}},
        {"Alias"             ,{"Alias"             ,"Alias"             , {"Bretzelus-I"}}},
        {"Targets"           ,{"Targets"           ,"Targets List"      , {""}}},
        {"ModulesDependency" ,{"ModulesDependency" ,"Modules Dependency" , {""}}},
        {"InstallTargets"    ,{"InstallTargets"    ,"InstallTargets"    , {""}}},
        {"IncludeDirs"       ,{"IncludeDirs"       ,"IncludeDirs"       , {""}}}
    };

    mParsers = {
        {"CMakeVersion"       ,&LCMakeLists::xValue},
        {"ModulesDependency"  ,&LCMakeLists::xModulesDependency},
        {"InstallTargets"     ,&LCMakeLists::xInstallTargets},
        {"ProjectName"        ,&LCMakeLists::xValue},
        {"Author"             ,&LCMakeLists::xValue},
        {"Email"              ,&LCMakeLists::xValue},
        {"Targets"            ,&LCMakeLists::xTargets},
        {"IncludeDirs"        ,&LCMakeLists::xIncludeDirs}
    };
}

LCMakeLists::LCMakeLists(const LCMakeLists& other)
{

}

LCMakeLists::LCMakeLists()
{

}


LCMakeLists& LCMakeLists::operator=(const LCMakeLists& other)
{
    return *this;
}


bool LCMakeLists::operator==(const LCMakeLists& other) const
{
    return ID() == other.ID();
}


int32_t LCMakeLists::xInstallTargets(File::Variable& Var)
{
    mOutFile << '[' << Var.mID << ": unimplemented]";
    return ErrCode::Implement;
}


int32_t LCMakeLists::xModulesDependency(File::Variable& Var)
{
    mOutFile << "# Modules Dependencies:" << std::endl;
    if(!Var.mValue.empty()){
        for(LString& M : Var.mValue)
            mOutFile << "FIND_PACKAGE(" << M << " REQUIRED)" << std::endl;
    }
    return ErrCode::Ok;
}

int32_t LCMakeLists::xIncludeDirs(File::Variable& Var)
{
    if(Var.mValue.size()){
        mOutFile << "INCLUDE_DIRECTORIES(" << std::endl;
        mOutFile << "    ${CMAKE_CURRENT_BINARY_DIR}" << std::endl;
        for(LString aInc : Var.mValue){
            mOutFile << "    ${" <<  LString("").Arg(aInc) << "}" << std::endl;
        }
        mOutFile << ")" << std::endl;
        mOutFile << "set(CMAKE_INCLUDE_CURRENT_DIR ON)" << std::endl;
    }
    return ErrCode::Ok;
}



int32_t LCMakeLists::xValue(File::Variable& Var)
{
    lfnl << "Varibale: [" << chgreen << Var.mID << creset << Var.mValue.front() << ": \n" ;
    LString::List& L = Var.mValue;
    if(!L.empty()){
        mOutFile << (L[0].empty() ? "[EMPTY]" : L[0]);
        return ErrCode::Ok;
    }
    return ErrCode::NullValue;
}

LCMakeLists::~LCMakeLists()
{
    
    mParsers.clear();
}

int32_t LCMakeLists::xTargets(File::Variable& Var)
{
    if(Var.mValue.empty())
        return ErrCode::NullValue;

    for(LString TargetName : Var.mValue){
        Target& Tg = TargetByID(TargetName);
        if(!Tg) return ErrCode::ObjectNotFound;
        if(Tg.Type() != Target::Enum::APP){
            //library
            mOutFile << "ADD_LIBRARY(" << std::endl;
        }
        else
            mOutFile << "ADD_EXECUTABLE(" << std::endl << "    " << Tg.Name() << std::endl;
        if(Tg.Type() != Target::Enum::APP)
            mOutFile << (Tg.Type() == Target::Enum::DYNAMIC ? "    SHARED" : "    STATIC") << std::endl;
        mOutFile << "    ${CppSourceFilesHere}" << std::endl
                    << ")" << std::endl;

        // Target_Links:
        LString::List  L = Tg.Dependencies();
        mOutFile << "TARGET_LINK_LIBRARIES(" << std::endl << "    " << Tg.Name() << std::endl;
        for(LString A : L){
            mOutFile << "    ${" << A << "}" << std::endl;
        }
        mOutFile << ")" << std::endl;
    }
    return ErrCode::Ok;
}


int32_t LCMakeLists::EndParseVariable(File::Variable& Var)
{
    GeneratorFN G = (*this)(Var.mID);
    lfnl << ":\n";
    if(G)
        return (this->*G)(Var);
    ///@todo Check that the variable id is really defined somewhere
    mOutFile << '[' << Var.mID << ": undef]";
    LexerMsg M = LexerMsg::PushWarning(ErrCode::Implement) + LString(" -- No Generator implemented for variable: `%s`").Arg(Var.mID);
    std::cerr << M.cc() << "\n";
    return ErrCode::Implement;
}



LCMakeLists& LCMakeLists::operator<<(const Target& TG)
{
    Journal JOUT = JFnInfo << cwhite << "Adding Target IDentifed by [" << cyellow <<TG.Name() << cwhite << "]:\n";
    mTargets[TG.Name()] = TG;
    for(LString A : TG.CMakeLibDepsVars())
        JOUT << chblue << A << cwhite <<", ";
    JOUT << ends;
    (*this)["Targets"].mValue.push_back(TG.Name());
    JFnInfo << cwhite << "Target IDentifier also pushed into the Generator Variable...[" << cyellow <<TG.Name() << cwhite << "]:\n";
    return *this;
}

Target& LCMakeLists::TargetByID(const LString& aID)
{
    Target::List::iterator I = mTargets.find(aID);
    if(I != mTargets.end())
        return I->second;
    return Target::Null;
}

void LCMakeLists::UpdateTargetByID(const LString& aID, const LCMake::Target& Tg)
{
    Target::List::iterator I = mTargets.find(aID);
    if(I != mTargets.end()){
        Target& T = I->second;
        T = Tg;
    }

}


LCMakeLists& LCMakeLists::operator<<(const LString& aIncludeDir)
{
    Variable& Var = (*this)["IncludeDirs"];

    for(LString a : Var.mValue){
        if(a == aIncludeDir)
            return *this;
    }
    Var << aIncludeDir;
    return *this;
}

bool LCMakeLists::RemoveTarget(const LString& aName)
{
    Target::List::iterator I = mTargets.find(aName);
    if(I != mTargets.end()){
        mTargets.erase(I);
        return true;
    }
    return false;
}


}
