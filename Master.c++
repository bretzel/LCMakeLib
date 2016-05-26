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

#define CMAKE_MASTERTEMPLATE_FILE "../Resource/CMake.MasterTemplate.txt" // As long as the working dir is the Bin subdir
#define CMAKE_OUTPUT_FILENAME   "CMakeLists.txt"


namespace LCMake {

Master::Master(const LString aID, const LString& aBasePath): CMakeFile< LCMake::Master >(aID, CMAKE_MASTERTEMPLATE_FILE, aBasePath + '/' + CMAKE_OUTPUT_FILENAME),
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
        {"CMakeVersion"      ,{"CMakeVersion"      , {"3.0"}}},
        {"ModulesDependency" ,{"ModulesDependency" , {""}}},
        {"MasterName"        ,{"MasterName"        , {""}}},
        {"InstallTargets"    ,{"InstallTargets"    , {""}}}
    };

    mParsers = {
        {"CMakeVersion"       ,&Master::xValue},
        {"ModulesDependency"  ,&Master::xModulesDependency},
        {"MasterName"         ,&Master::xValue},
        {"InstallTargets"     ,&Master::xInstallTargets}
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
    return ErrCode::Implement;
}


int32_t Master::xModulesDependency(File::Variable& Var)
{
    return ErrCode::Implement;
}

int32_t Master::xValue(File::Variable& Var)
{
    LString::List& L = Var.second;
    if(!L.empty()){
        LString::List::iterator I = L.begin();
        mOutFile << *I;
        return ErrCode::Ok;
    }
    return ErrCode::NullValue;
}

Master::~Master()
{
    for(auto VI : mVariables){
        VI.second.second.clear(); // <LString::List>
        VI.second.first.clear();  // <LString  ( UI Label text storage)>
    }
    mVariables.clear();
    mParsers.clear();
}


}
