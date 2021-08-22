////////////////////////////////////////////////////////////
#include "model.cl.hpp"
#include "cli.cl.hpp"
#include "cli.ceeferinc.cl.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
void GhClient::initflec(){
   flector_defstart(2)
      flector_jsonmode;
   flector_defend
}
////////////////////////////////////////////////////////////
GhClient::GhClient(){
   initflec();
   corelevels.resize(env->compvec.size());
   sloopvec(corelevels, moo)
      moo = 5; // let's start with 2 everywhere
   sloopend
   sloopvec(env->occ_requirement_rank, moo)
      auto& joba = analyses.emplace_back();
      joba.occ = moo;
   sloopend
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int GhClient::taskProficiency(TaskCluster * cluster){
   auto it = abilities.find(cluster);
   if(it == abilities.end()){
      return 0;
   }
   return it->second;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
JobAnalysis& GhClient::getJobba(Occupation * occ){
   assert(occ->occ_rr_index > 0 && occ->occ_rr_index < analyses.size());
   auto& ret = analyses[occ->occ_rr_index];
   return ret; // yeah
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void GhClient::unsyncAnal(){
   anal_synced = false;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void GhClient::syncRecommendations(){
   if(anal_synced){
      return;
   }
   anal_synced = true;
   asserts(analyses.size() == env->occ_requirement_rank.size(), "");
   sortedanal.clear();
   sloopvec(analyses, moo)
      moo.occ->sync(*this, moo);
      sortedanal.push_back(&moo);
   sloopend
   sort(sortedanal.begin(), sortedanal.end(), [](auto * a, auto * b){
      return a->final_score < b->final_score;
   });
   sloopveccounta(sortedanal, moo, counta)
      moo->result_index = counta;
   sloopend
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
serVO::ClioBaseSpecifier _svclbspc([](serVO::Servo& srv){ srv.climan.useAcliSubba<GhClient>(); });
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

