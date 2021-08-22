////////////////////////////////////////////////////////////
#pragma once
namespace std{}; using namespace std;
////////////////////////////////////////////////////////////
#include "cloth_classdef.cl.hpp"
#include "../shing/intrange.hpp"
#include "../servo/servo.hpp"
#include "../servo/cliobase.hpp"
#include "../shing/restracker.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class SkillStatement{
   public:
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class JobAnalysis{
   public:
   //-------------------------------------------------------
   int result_index = 0;
   Occupation* occ = NULL;
   int mismatch_score = 0;
   int overqualify_pts = 0;
   int underqualify_pts = 0;
   float skill_penalty = 0;
   int final_score = 0;
   bool trashed = false;
   bool favorited = false;
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
class GhClient:public Shing::Tracked<GhClient>, public serVO::ActiveClient{
   public:
   //-------------------------------------------------------
   string name;
   string profile;
   string age;
   string contact_details;
   vector<int> corelevels;
   bool levels_set_up = false;
   map<TaskCluster*,int> abilities;
   vector<JobAnalysis> analyses;
   vector<JobAnalysis*> sortedanal;
   bool anal_synced = false;
   bool youth_filter = false;
   //-------------------------------------------------------
   flector_subbie_decl;
   void initflec();
   GhClient();
   int taskProficiency(TaskCluster * cluster);
   JobAnalysis& getJobba(Occupation * occ);
   void unsyncAnal();
   void syncRecommendations();
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

