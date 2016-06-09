#include <iostream>

#include <Journal++.h>
#include <unistd.h>
#include <CMakeTemplate.h>

using namespace LCMake;

int32_t Test_Master()
{
    ///home/bretzelus/Applications/LCMake.App/LCMake.Src
    LCMakeLists M("MyProject", "/home/bretzelus/Applications/LCMake.App/LCMake.Src");

    M["CMakeVersion"]   =  "3.0";
    M["Author"]         =  "Bretzelus-I";
    M["Email"]          =  "lussier.serge@gmail.com";
    M["ProjectName"]    =  "CMakeTest-Application";
    M["MasterName"]     =  "CMake.Test.App";
    M["ModulesDependency"].Clear()  << "Lus" <<  "L++";
    
    M.OpenInput();
    M.OpenOutput();
    M.Generate();
    
    return ErrCode::Ok;
}


int main (int argc, char **argv)
{

    try{

        Journal::set_file("LCMake.app.log");
        Journal::init(Journal::ansi, "LCMake.app :", true);
        Journal::reset_stamp(), Journal::white, Journal::hour24, ':', Journal::minute, ':', Journal::seconds;
        JFnDebug << " me :-) " << ends;
        JCInfo <<   "  ------ " <<  ends;
        JCDebug <<  "  ------ " <<  ends;
        JCError <<  "  ------ " <<  ends;
       // sleep(1);
        JCCritical <<  "  ------ " <<  ends;
        JCFatal <<  "  ------ " <<  ends;
       // sleep(1);
        JCExcep <<  "  ------ " <<  ends;
        JCNote <<   "  ------ " <<  ends;
       // sleep(1);
        JCWarning <<  "  ------ " <<  ends;
        LString t = "\nif Response == ( 1 << 2 * --r) + 4! then {\n    cout \"cool!\", x++; return 0xffd2;\n}\nelse {\n    return \"allo\";\n}";
        JCNote << " Code mode:" <<  Journal::lf << Journal::code << t << Journal::endcode << Journal::lf
              << Journal::lf << Journal::white << "end code mode..." << ends;
        
        Test_Master();
        LexerMsg E;
        while(LexerMsg::Pop(E)){
            std::cerr << E.cc() << "\n";
        }
        Journal::close();
    }
    catch(const char* err){
        std::cerr << err << "\n";
        //Journal::close();
        return 1;
    }
    catch(LexerMsg E){
        std::cerr << E.cc() << "\n";
    }
    return 0;
}


