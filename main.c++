#include <iostream>

#include <Journal++.h>
#include <unistd.h>
#include <CMakeAppDelegate.h>




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
        
        Journal::close();
    }
    catch(const char* err){
        std::cerr << err << "\n";
        //Journal::close();
        return 1;
    }
    return 0;
}


