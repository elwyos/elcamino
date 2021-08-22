////////////////////////////////////////////////////////////
#include "../shing/asynca.hpp"
#include "../shing/consoline.hpp"
#include "../servo/compressor.hpp"
#include "../shing/consolearg.hpp"
#include "model.cl.hpp"
#include "cli.cl.hpp"
#include "main.cl.hpp"
#include "main.ceeferinc.cl.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
void EntryTabes::croform(serVO::Form& form){
   { form.cNODE(":span")
      .enCLASS("pattern-diagonal-stripes-md")
      .cloSTYLEBUILDUP("position:""absolute")
      .cloSTYLEBUILDUP("z-index:""-20")
      .cloSTYLEBUILDUP("width:""96%")
      .cloSTYLEBUILDUP("height:""35px")
      .cloSTYLEBUILDUP("color:""#333")
      .cloSTYLEBFLUSH()
      ;}
   { serVO::FormPopper _poppa(&form); form.cOPENER(":span");form.cKIDSTART();
      { serVO::FormPopper _poppa(&form); form.cOPENER(":h1"); form.cARGER("n", "Project El Camino");form.cKIDSTART();
         { form.cOPENER(":span"); form.cARGER("n", " by team " );form.cCLOSER()
            .enCLASS("muted")
            ;}
         { form.cOPENER(":span"); form.cARGER("n", "JesseWeMustCode");form.cCLOSER()
            .enCLASS("alert")
            ;}
      _poppa.pop();
      }
   _poppa.pop()
      .enCLASS("row")
      ;}
   form.ruler();
   
   { serVO::FormPopper _poppa(&form); form.cOPENER(":span");form.cKIDSTART();
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { serVO::FormPopper _poppa(&form); form.cOPENER(":h1");form.cKIDSTART();
            form.raw("Set your character stats, we recommend jobs!");
            
         _poppa.pop();
         }
         { form.cOPENER(":h2"); form.cARGER("n", "Could you have been an engineer? A school principal? A CEO??");form.cCLOSER()
            .enCLASS("offk")
            ;}
         { form.cOPENER(":p"); form.cARGER("n", "Let our AI think about it for you!!!");form.cCLOSER();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER(":span");form.cKIDSTART();
            { form.cOPENER("btn"); form.cARGER("n", "How does it work?");form.cCLOSER()
               .cloHANDLER(true,0, [this](auto& evt){
               metOPENMODAL() / [this](serFORM& form){
                  { form.cOPENER(":div"); form.cARGER("n", "There's ten numbers to set, just like the typical role playing games available these days");form.cCLOSER()
                     .cloSTYLEBUILDUP("min-width:""80vw")
                     .cloSTYLEBFLUSH()
                     ;}
                  { form.cOPENER(":div"); form.cARGER("n", "Set these, and then our AI will think up what your ideal job is! It's fun and you can share it with others!!");form.cCLOSER();
                  }
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     { form.cOPENER("btn"); form.cARGER("n", "TRY IT NOW");form.cCLOSER()
                        .cloHANDLER(true,0, [this](auto& evt){
                           reroute("/chara");
                        })
                        .enCLASS("red")
                        ;}
                  _poppa.pop()
                     .enCLASS("cenrow")
                     ;}
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     { form.cOPENER("btn"); form.cARGER("n", "I'd rather procrastinate..");form.cCLOSER()
                        .cloHANDLER(true,0, [this](auto& evt){
                           reroute("https://www.reddit.com");
                        })
                        ;}
                  _poppa.pop()
                     .enCLASS("cenrow")
                     ;}
               };
               })
               ;}
            { form.cOPENER("btn"); form.cARGER("n", "TRY IT NOW");form.cCLOSER()
               .cloHANDLER(true,0, [this](auto& evt){
                  reroute("/chara");
               })
               .enCLASS("red")
               ;}
         _poppa.pop()
            .enCLASS("cenrow")
            .cloSTYLEBUILDUP("justify-content:""center")
            .cloSTYLEBFLUSH()
            ;}
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            { form.cOPENER("btn"); form.cARGER("n", "YOUTH JOBS");form.cCLOSER()
               .cloHANDLER(true,0, [this](auto& evt){
                  cli.youth_filter = true;
                  reroute("/chara");
               })
               .enCLASS("green")
               ;}
            { serVO::FormPopper _poppa(&form); form.cOPENER(":span");form.cKIDSTART();
               { form.cOPENER("ic"); form.cARGER("n", "hand-point-left");form.cCLOSER();
               }
               { form.cOPENER(":span"); form.cARGER("n", "youth friendly jobs!!");form.cCLOSER()
                  ;}
            _poppa.pop()
               .enCLASS("chip")
               ;}
         _poppa.pop()
            .enCLASS("cenrow")
            ;}
      _poppa.pop()
         .cloSTYLEBUILDUP("text-align:""center")
         .cloSTYLEBUILDUP("padding:""10%")
         .cloSTYLEBFLUSH()
         ;}
   _poppa.pop()
      .enCLASS("row")
      ;}
   { form.cOPENER(":span"); form.cARGER("n", "TESTING");form.cCLOSER()
      .enCLASS("sepper"" ""s4")
      ;}
   { serVO::FormPopper _poppa(&form); form.cOPENER("fst"); form.cARGER("n", "govhack stuff");form.cKIDSTART();
      { form.cOPENER(":p"); form.cARGER("n", "I guess this is where other things will come someday");form.cCLOSER();
      }
      { form.cOPENER(":p"); form.cARGER("n", "disclaimers, info etc. This is a govhack project for team JesseWeNeedToCode");form.cCLOSER()
         .enCLASS("offk")
         ;}
   _poppa.pop();
   }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
EntryTabes::EntryTabes() : CrocMetaBase(serVO::acSESH(), NULL, "nuffer")
,cli(*(GhClient*)0x88888888)
{}
EntryTabes::EntryTabes(vector<string>& rargs, serVO::acSESH& leacsesh, serVO::Servo& leservo, const shringer& pather) : CrocMetaBase(leacsesh, &leservo, "EntryTabes")
,cli(leacsesh.acli->template as<GhClient>())
{metainit(leservo); metasetup(leacsesh, rargs); }
void EntryTabes::croc_init(serVO::Connection& conn){
linkConn(conn);
}
shringer EntryTabes::metabase_name(){
return shringer("EntryTabes");
}
void EntryTabes::croc_rpc(serVO::Connection& conn, Shing::RPC r){
      croust<<"What : "<<(r->strarg(0)) << ozendl;
}
void EntryTabes::croc_proc(serVO::CrocContext& cro){
linkConn(cro.conn);
{ serVO::CrocForm form(this, cro.stringer, "form");
croform(form);
}
}
serVO::RouteSpecifier _routespec_EntryTabes("/", "bundle/stdweb.dir/stdweb.hpl", [](auto& pather, auto& reqr){
EntryTabes * meta = new EntryTabes(reqr->routeargs, reqr->acsesh, reqr->conn->servo.ref(), pather);
reqr->conn->croc_meta_schref <<= meta;
reqr->conn->metabase = meta;
meta->croc_init(reqr->conn.ref());
meta->crocfunc = [](serVO::CrocContext& cro){ cro.conn.croc_meta_schref.val<EntryTabes>().croc_proc(cro); };
meta->crocification(reqr->conn.ref(), reqr.record);
reqr->conn->rpchandler = [](serVO::Connection& conn, Shing::RPC r){ conn.croc_meta_schref.val<EntryTabes>().croc_rpc(conn, r); };
meta->unlinkConn(reqr->conn.ref());
reqr->fin();
}, [](auto& pather, auto& conn){
EntryTabes * meta = new EntryTabes(conn.routeargs, conn.acseshhold, conn.servo.ref(), pather);
conn.croc_meta_schref <<= meta;
conn.metabase = meta;
meta->croc_init(conn);
meta->crocfunc = [](serVO::CrocContext& cro){ cro.conn.croc_meta_schref.val<EntryTabes>().croc_proc(cro); };
conn.rpchandler = [](serVO::Connection& conn, Shing::RPC r){ conn.croc_meta_schref.val<EntryTabes>().croc_rpc(conn, r); };
meta->linkConnFromReroute(conn);
});
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main(int argc, char * argv[]){ CargParser parsa(argc, argv); 
   env();
; return serVO::servomain(argc, argv); }
serVO::SettingsSpecifier _srvstspc0("devport", 80);
serVO::SettingsSpecifier _srvstspc1("devsslport", 4431);
serVO::SettingsSpecifier _srvstspc2("title", "El Camino");
serVO::SettingsSpecifier _srvstspc3("desc", "Good ending for everyone, from the start!");
////////////////////////////////////////////////////////////

