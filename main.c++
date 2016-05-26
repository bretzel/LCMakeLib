#include <iostream>

#include <Journal++.h>
#include <unistd.h>
#include <Master.h>

using namespace LCMake;

int32_t Test_Master()
{
    Master M("MyProject", "/home/bretzelus/Applications/CMake.App");
    File::Variable& V = M["Author"];
    V =  "Bretzelus-I";
    lfnl << "Variable :`" << V.mLabel << "` = `" << cyellow << V.mValue[0] << creset << "`\n";
    File::Variable& Email = M["Email"];
    Email =  "lussier.serge@gmail.com";
    lfnl << chblue << "Variable :`" << cwhite << Email.mLabel << "` = `" << chcyan << Email.mValue[0] << creset << "`\n";
    
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


