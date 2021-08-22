////////////////////////////////////////////////////////////
#pragma once
namespace std{}; using namespace std;
////////////////////////////////////////////////////////////
#include "cloth_classdef.cl.hpp"
#include "../servo/routespecifier.hpp"
#include "../servo/connection.hpp"
#include "../servo/request.hpp"
#include "../shing/restracker.hpp"
#include "../servo/servo.hpp"
#include "../servo/settingsspecifier.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
class EntryTabes:public serVO::CrocMetaBase, public Shing::Tracked<EntryTabes>{
   public:
   //-------------------------------------------------------
   string login_uname;
   string login_pass;
   string login_email;
   string testfield;
   string projname;
   //-------------------------------------------------------
   GhClient& cli;
   EntryTabes();
   EntryTabes(vector<string>& rargs, serVO::acSESH& leacsesh, serVO::Servo& leservo, const shringer& pather);
   void croc_init(serVO::Connection& conn);
   void croc_rpc(serVO::Connection& conn, Shing::RPC r);
   void croc_proc(serVO::CrocContext& cro);
   shringer metabase_name();
   void croform(serVO::Form& form);
   //-------------------------------------------------------
};
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

