////////////////////////////////////////////////////////////
#pragma once
namespace std{}; using namespace std;
////////////////////////////////////////////////////////////
#include "cloth_classdef.cl.hpp"
#include "../shing/schdangler.hpp"
#include "../shing/schmap.hpp"
#include "../shing/eostri.hpp"
#include "model.cl.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class ProfLevel{
   public:
   //-------------------------------------------------------
   int levelnum = 0;
   string levelname;
   string description;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class CoreCompetency{
   public:
   //-------------------------------------------------------
   string name;
   map<int,ProfLevel> proflevels;
   int index = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class Tool{
   public:
   //-------------------------------------------------------
   string name;
   vector<string> examples;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class TaskCluster{
   public:
   //-------------------------------------------------------
   string name;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class TaskClusterGroup{
   public:
   //-------------------------------------------------------
   string name;
   nameschmap<TaskCluster> clusters;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class Tag{
   public:
   //-------------------------------------------------------
   string name;
   eostri type;
   int vecindex = 0;
   int frequency = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class SpecialistTask{
   public:
   //-------------------------------------------------------
   string desc;
   TaskCluster* cluster = NULL;
   TaskClusterGroup* clustergroup = NULL;
   int percent_time = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class OccupationReq{
   public:
   //-------------------------------------------------------
   CoreCompetency* compe = NULL;
   ProfLevel* prole = NULL;
   int levelnum = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class OccTag{
   public:
   //-------------------------------------------------------
   Tag* tag = NULL;
   int percentage = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class OccLink{
   public:
   //-------------------------------------------------------
   int score = 0;
   Occupation* a = NULL;
   Occupation* b = NULL;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class OccDifference{
   public:
   //-------------------------------------------------------
   bool calculated = false;
   int core_difference = 0;
   int tool_commonality = 0;
   int task_commonality = 0;
   int knowledge_commonality = 0;
   int ability_commonality = 0;
   int skill_commonality = 0;
   int score = 0;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class OccLinkFinal{
   public:
   //-------------------------------------------------------
   Occupation* origin = NULL;
   Occupation* target = NULL;
   int score = 0;
   float visscore = 0;
   OccDifference diffo;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class Occupation{
   public:
   //-------------------------------------------------------
   int occindex = 0;
   int occ_rr_index = 0;
   int occucode = 0;
   string name;
   string description;
   vector<OccupationReq> reqs;
   vector<int> reqints;
   int total_level_req = 0;
   vector<SpecialistTask> tasks;
   vector<Tool*> used_tools;
   vector<int> state_percs;
   vector<OccTag> tags;
   int average_age = 0;
   int average_fulltime_hours = 0;
   int employee_size = 0;
   int fulltime_share = 0;
   int gendershare_female = 0;
   int weeklypay_dollars = 0;
   int future_growth = 0;
   int skill_level = 0;
   multimap<int,OccLink> occlinks_forsort;
   vector<OccLinkFinal> occlinks;
   //-------------------------------------------------------
   void gatherNearby(set<Occupation*>& ret, int depth);
   void add(OccLink lelink);
   bool youthFriendly();
   void syncLinks();
   OccDifference calcDifference(Occupation& rhs);
   void sync(GhClient& cli, JobAnalysis& joba);
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class Env{
   public:
   //-------------------------------------------------------
   schmap<int,Occupation> occupations;
   nameschmap<CoreCompetency> corecomps;
   nameschmap<TaskClusterGroup> clustergroups;
   map<pair<eostri,string>,Tag> tags;
   vector<Tag*> tagvec;
   map<string,int> statemap;
   nameschmap<Tool> tools;
   vector<Occupation*> occ_requirement_rank;
   vector<CoreCompetency*> compvec;
   //-------------------------------------------------------
   Env();
   CoreCompetency& competency(const string& thestr);
   void checkLevels();
   void load();
   void postProcess();
   void syncGraph();
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
DECLschdangler(env, Env);
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

