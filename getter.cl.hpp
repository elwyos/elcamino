////////////////////////////////////////////////////////////
#pragma once
namespace std{}; using namespace std;
////////////////////////////////////////////////////////////
#include "cloth_classdef.cl.hpp"
#include "../shing/schdangler.hpp"
#include "../sqlite/kvmap.hpp"
#include "../shing/suspension.hpp"
#include "../sqlite/kv.hpp"
#include "../shing/eostri.hpp"
#include "../shing/schmap.hpp"
#include "../shing/consolearg.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class Dump{
   public:
   //-------------------------------------------------------
   int jobid = 0;
   string title;
   map<string,string> outdata;
   map<string,string> state_percs;
   map<string,string> knowledge_reqs;
   map<string,string> skill_reqs;
   map<string,string> ability_reqs;
   //-------------------------------------------------------
   flector_subbie_decl;
   Dump();
   void initflec();
};
////////////////////////////////////////////////////////////
class Tag{
   public:
   //-------------------------------------------------------
   string name;
   eostri type;
   int tagindex = 0;
   int usagecount = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class Env{
   public:
   //-------------------------------------------------------
   vector<string> occids;
   Shing::Suspension suspensions;
   nameschmap<Tag> knowledges;
   nameschmap<Tag> skills;
   nameschmap<Tag> abilities;
   vector<Tag*> alltags;
   map<string,int> tagmappings;
   //-------------------------------------------------------
   Env();
   void checkAllIds();
   void maybeCallStarters();
   void dump_analysis(string jobid, const string& thedump);
   void goScrape(string jobid);
   void reparse();
   void processTags();
   int getTagNum(const string& thestr);
   void process();
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
DECLschdangler(env, Env);
DECLsqlkv(rawhtmls, "dumps.db", "rawhtmls")
DECLsqlkvmap(dumpkv, string, Dump, "dumps.db", "ledumps");
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

