////////////////////////////////////////////////////////////
#pragma once
namespace std{}; using namespace std;
////////////////////////////////////////////////////////////
#include "cloth_classdef.cl.hpp"
#include "../servo/routespecifier.hpp"
#include "../servo/connection.hpp"
#include "../servo/request.hpp"
#include "../shing/restracker.hpp"
#include "../shing/eostri.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class CharTabes:public serVO::CrocMetaBase, public Shing::Tracked<CharTabes>{
   public:
   //-------------------------------------------------------
   bool everpopped = false;
   bool showing_favs = false;
   int current_page = 0;
   //-------------------------------------------------------
   GhClient& cli;
   CharTabes();
   CharTabes(vector<string>& rargs, serVO::acSESH& leacsesh, serVO::Servo& leservo, const shringer& pather);
   void croc_init(serVO::Connection& conn);
   void croc_rpc(serVO::Connection& conn, Shing::RPC r);
   void croc_proc(serVO::CrocContext& cro);
   shringer metabase_name();
   void croSliders(serFORM& form);
   void croMainThingos(Occupation * occa, JobAnalysis * jobb, serFORM& form);
   void croDetails(Occupation * occa, JobAnalysis * jobb, serFORM& form);
   void croSimilarity(Occupation * occa, Occupation * occb, eostri tagtype, serFORM& form);
   void croRelated(Occupation * occa, JobAnalysis * jobb, serFORM& form);
   void croGraph(Occupation * occa, JobAnalysis * jobb, serFORM& form);
   void croAnalysis(JobAnalysis& joba, serFORM& form);
   void croform(serFORM& form);
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

