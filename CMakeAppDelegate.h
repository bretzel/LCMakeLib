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

//#ifndef CMAKEAPPDELEGATE_H
//#define CMAKEAPPDELEGATE_H
// Disabled protected include, using pragma:
#pragma once

#include <map>
#include <LString++.h>



class CMakeAppDelegate
{
public:
    CMakeAppDelegate();
    CMakeAppDelegate(const CMakeAppDelegate& aCMAD);
    ~CMakeAppDelegate();
    CMakeAppDelegate& operator=(const CMakeAppDelegate& aCMAD);
    bool operator==(const CMakeAppDelegate& aCMAD) const;


};

// disabled include protection, using pragma instead
//#endif // CMAKEAPPDELEGATE_H
