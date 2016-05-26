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

#include "Master.h"

#define CMAKE_MASTERTEMPLATE_FILE "../Resources/CMakeLists.MasterTemplate.txt" // As long as the working dir is the Bin subdir
#define CMAKE_OUTPUT_FILENAME   "CMakeLists.txt"


namespace LCMake {

Master::Master(const LString& aID, const LString& aBasePath): CMakeFile< LCMake::Master >(aID, CMAKE_MASTERTEMPLATE_FILE, aBasePath + '/' + CMAKE_OUTPUT_FILENAME),
mBasePath(aBasePath)
{
    /*
     * #   CMakeVersion
     * #   ModulesDependency
     * #   MasterName
     * #   InstallTargets
     *
     */


    mVariables = {
        {"CMakeVersion"      ,{"CMakeVersion"      ,"CMake Minimum Version", {""}}},
        {"ProjectName"       ,{"ProjectName"       ,"Project Name"       , {""}}},
        {"Author"            ,{"Author"            ,"Author"            , {""}}},
        {"Email"             ,{"Email"             ,"Email"             , {""}}},
        {"Targets"           ,{"Targets"           ,"Targets List"      , {""}}},
        {"ModulesDependency" ,{"ModulesDependency" ,"Modules Dependency" , {""}}},
        {"MasterName"        ,{"MasterName"        ,"MasterName"        , {""}}},
        {"InstallTargets"    ,{"InstallTargets"    ,"InstallTargets"    , {""}}}
    };

    mParsers = {
        {"CMakeVersion"       ,&Master::xValue},
        {"ModulesDependency"  ,&Master::xModulesDependency},
        {"MasterName"         ,&Master::xValue},
        {"InstallTargets"     ,&Master::xInstallTargets},
        {"ProjectName"        ,&Master::xValue},
        {"Author"             ,&Master::xValue},
        {"Email"              ,&Master::xValue},
        {"Targets"            ,&Master::xTargets}
    };
}

Master::Master(const Master& other)
{

}

Master::Master()
{

}


Master& Master::operator=(const Master& other)
{
    return *this;
}


bool Master::operator==(const Master& other) const
{
    return ID() == other.ID();
}


int32_t Master::xInstallTargets(File::Variable& Var)
{
    mOutFile << '[' << Var.mID << ": unimplemented]";
    return ErrCode::Implement;
}


int32_t Master::xModulesDependency(File::Variable& Var)
{
    mOutFile << "# Modules Dependencies:" << std::endl;
    if(!Var.mValue.empty()){
        for(LString& M : Var.mValue)
            mOutFile << "find_package(" << M << " REQUIRED)" << std::endl;
    }
    return ErrCode::Implement;
}

int32_t Master::xValue(File::Variable& Var)
{
    lfnl << "Varibale: [" << chgreen << Var.mID << creset << Var.mValue.front() << ": \n" ;
    LString::List& L = Var.mValue;
    if(!L.empty()){
        mOutFile << (L[0].empty() ? "[EMPTY]" : L[0]);
        return ErrCode::Ok;
    }
    return ErrCode::NullValue;
}

Master::~Master()
{
    
    mParsers.clear();
}

int32_t Master::xTargets(File::Variable& Var)
{
    return ErrCode::Implement;
}


int32_t Master::EndParseVariable(File::Variable& Var)
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

}
