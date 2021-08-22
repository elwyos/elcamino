////////////////////////////////////////////////////////////
#include "../shing/syscom.hpp"
#include "../shing/asynca.hpp"
#include "../shing/cyavex.hpp"
#include "../shing/cyano.hpp"
#include "../shing/consolearg.hpp"
#include "../shing/schfile.hpp"
#include "../shing/scraper.hpp"
#include "../telepatia/tcpstation.hpp"
#include "../shing/oust.hpp"
#include "../shing/csvlooper.hpp"
#include "../sqlite/kv_impl.hpp"
#include "getter.cl.hpp"
#include "getter.ceeferinc.cl.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void real_estate_analyze(const string& dumpedfile);
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
Dump::Dump(){
   initflec();
}
////////////////////////////////////////////////////////////
void Dump::initflec(){
   flector_defstart(2)
      flector_field(jobid).fromVersion(2);
      flector_field(title).fromVersion(2);
      flector_mapfield(outdata).fromVersion(2);
      flector_mapfield(state_percs).fromVersion(2);
      flector_mapfield(knowledge_reqs).fromVersion(2);
      flector_mapfield(skill_reqs).fromVersion(2);
      flector_mapfield(ability_reqs).fromVersion(2);
   flector_defend
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
Env::Env(){
   checkAllIds();
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::checkAllIds(){
   {
      Shing::CSVLooper looper("/home/yose/dev/govhack/skills/occs_details.csv", true);
      while(true){
         auto liner = looper.getLine();
         if(liner){
            if(!liner.is_header){
               occids.push_back(liner[0]);
            }
         }
         else {
            break;
         }
      }
   }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::maybeCallStarters(){
   sloopvec(occids, moo)
      if(suspensions.activesuspendercount > 8){
         break;
      }
      if(!rawhtmls.has(moo)){
         goScrape(moo);
      }
   sloopend
   __casynca(500)/ [this]{
      maybeCallStarters();
   };
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::dump_analysis(string jobid, const string& thedump){
   Cyano cyano;
   cyano.parseHTMLString(thedump);
   Cyavex vex(cyano);
   map<string, string> outdata;
   set<string> you_may_also_likes;
   map<string, string> statepercs;
   map<string, string> knowledge_reqs;
   map<string, string> skill_reqs;
   map<string, string> ability_reqs;
   bool got_related_yet = false;
   bool gottitle = false;
   string titler;
   vex/ [&] {
      if(vex == "title" && !gottitle){
         gottitle = true;
         titler = __chompends(EasyParser(vex.contents()).parseUntil('|', false));
         croust>>(33)<<"@ ">>(250)<<(titler) << ozendl;
      }
      if(vex == "span" && vex.isclass("snapshot-title")){
         if(vex.contains("Weekly Pay")){
            outdata["weeklypay"] = vex--.contents();
         }
         if(vex.contains("Future Growth")){
            outdata["futuregrowth"] = vex--.contents();
         }
         if(vex.contains("Employment Size")){
            outdata["empsize"] = vex--.contents();
         }
         if(vex.contains("Skill level rating")){
            outdata["skill_lvl"] = vex--.contents();
         }
         if(vex.contains("Full-Time Share")){
            outdata["ftshare"] = vex--.contents();
         }
         if(vex.contains("Average full-time")){
            outdata["avg_ftime"] = vex--.contents();
         }
         if(vex.contains("Average age")){
            outdata["avg_age"] = vex--.contents();
         }
         if(vex.contains("Gender Share")){
            outdata["gendershare"] = vex--.contents();
         }
      }
      else if(vex == "h5" && vex.contains("You may also like") && !got_related_yet){
         got_related_yet = true;
         auto kidder = vex.par()++;
         kidder/ [&] {
            if(kidder == "span" && kidder.par() == "a"){
               string name = kidder.contents();
               string link = kidder.par()["href"];
               vector<string> parts;
               __splitOn(link, '=', parts);
               you_may_also_likes.insert(parts.back());
            }
         };
      }
      else if(vex.isclass("state-percentage")){
         string actualstate = vex.par()--.contents();
         statepercs[actualstate] = vex.contents();
      }
      else if(vex["id"] == "knowledge-1" && vex.insideclass("tab-content")){
         vex/ [&] {
            if(vex == "span" && vex.par().isclass("work-heading")){
               string knowledgename = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               knowledge_reqs[knowledgename] = skilllevel;
            }
         };
      }
      else if(vex["id"] == "skills-1" && vex.insideclass("tab-content")){
         vex/ [&] {
            if(vex == "span" && vex.par().isclass("work-heading")){
               string skillname = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               skill_reqs[skillname] = skilllevel;
            }
         };
      }
      else if(vex["id"] == "abilities-1" && vex.insideclass("tab-content")){
         vex/ [&] {
            if(vex == "span" && vex.par().isclass("work-heading")){
               string abilname = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               croust>>(112)<<(abilname )>>(250)<<" => ">>(88)<<(skilllevel) << ozendl;
               ability_reqs[abilname] = skilllevel;
            }
         };
      }
   };
   Dump dump;
   dump.jobid = Morestring::toInt(jobid);
   dump.title = titler;
   dump.outdata = outdata;
   dump.state_percs = statepercs;
   dump.knowledge_reqs = knowledge_reqs;
   dump.skill_reqs = skill_reqs;
   dump.ability_reqs = ability_reqs;
   dumpkv.set(jobid, dump);
   oustoust[220].ruler();
   croust>>(33)<<(titler )>>(250)<<" @ "<<(jobid) << ozendl;
   sloopmapex(outdata, eh, moo)
      croust>>(33)<<(eh )>>(250)<<" => ">>(220)<<(moo) << ozendl;
   sloopend
   {
      int counta = 0;
      sloopmapex(knowledge_reqs, eh, moo)
         if(counta != 0){
            croust>>(250)<<", ";
         }
         counta++;
         croust>>(33)<<(eh )>>(250)<<":">>(220)<<(moo );
      sloopend
      croust << ozendl;
   }
   {
      int counta = 0;
      sloopmapex(skill_reqs, eh, moo)
         if(counta != 0){
            croust>>(250)<<", ";
         }
         counta++;
         croust>>(112)<<(eh )>>(250)<<":">>(220)<<(moo );
      sloopend
      croust << ozendl;
   }
   {
      int counta = 0;
      sloopmapex(ability_reqs, eh, moo)
         if(counta != 0){
            croust>>(250)<<", ";
         }
         counta++;
         croust>>(202)<<(eh )>>(250)<<":">>(220)<<(moo );
      sloopend
      croust << ozendl;
   }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::goScrape(string jobid){
   croust>>(33)<<"Scraping : ">>(250)<<(jobid )>>(240)<<" | progress : "<<(rawhtmls.kv().count() )<<" => "<<(dumpkv.kv().count())<<" / "<<(occids.size()) << ozendl;
   if(rawhtmls.has(jobid)){
      string rawer = rawhtmls.get(jobid);
      dump_analysis(jobid, rawer);
   }
   else {
      auto sus = suspensions++;
      Shing::scrape("joboutlook.gov.au/occupations/software-and-applications-programmers?occupationCode=" + jobid)/ [=] (auto& res){
         sus; // very sus, let's see if this works
         rawhtmls.set(jobid, res.contents);
         dump_analysis(jobid, res.contents);
      };
   }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::reparse(){
   sloopvec(occids, jobid)
      if(rawhtmls.has(jobid)){
         string rawer = rawhtmls.get(jobid);
         dump_analysis(jobid, rawer);
      }
   sloopend
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::processTags(){
   dumpkv.loadAll();
   auto& lemap = dumpkv.obmap();
   sloopmapex(lemap, eh, dump)
      sloopmapex(dump.knowledge_reqs, knowle, req)
         knowledges[knowle].usagecount++;
      sloopend
      sloopmapex(dump.skill_reqs, skille, req)
         skills[skille].usagecount++;
      sloopend
      sloopmapex(dump.ability_reqs, abile, req)
         abilities[abile].usagecount++;
      sloopend
   sloopend
   int counter = 0;
   sloopmapex(knowledges, eh, moo)
      moo.tagindex = counter++;
      moo.type = e__(know);
      alltags.push_back(&moo);
   sloopend
   sloopmapex(skills, eh, moo)
      moo.tagindex = counter++;
      moo.type = e__(skill);
      alltags.push_back(&moo);
   sloopend
   sloopmapex(abilities, eh, moo)
      moo.tagindex = counter++;
      moo.type = e__(abil);
      alltags.push_back(&moo);
   sloopend
   string tagsfile;
   sloopveccounta(alltags, moo, counta)
      asserts(moo->tagindex == counta, "");
      tagsfile.append(moo->name + "|" + moo->type.toString() + "|" + __toString(moo->usagecount) + "\n");
      tagmappings[moo->name] = counta;
   sloopend
   schfile("tags.strext") <<= tagsfile;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int Env::getTagNum(const string& thestr){
   auto it = tagmappings.find(thestr);
   if(it != tagmappings.end()){
      return it->second;
   }
   asserts(0, "");
   return -1;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void Env::process(){
   processTags();
   string lines;
   set<string> skill_levels;
   set<string> future_growths;
   sloopvec(occids, moo)
      if(dumpkv.has(moo)){
         auto ledump = dumpkv.get(moo);
         string thispart;
         thispart.append(moo + "\n");
         thispart.append(" d\n");
         sloopmapex(ledump.outdata, eh, moo)
            if(eh == "futuregrowth"){
               future_growths.insert(moo);
            }
            else if(eh == "skill_lvl"){
               skill_levels.insert(moo);
            }
            thispart.append("  " + eh + ":" + moo + "\n");
         sloopend
         thispart.append(" st\n");
         sloopmapex(ledump.state_percs, eh, moo)
            thispart.append("  " + eh + ":" + moo + "\n");
         sloopend
         thispart.append(" k\n");
         sloopmapex(ledump.knowledge_reqs, eh, moo)
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
         sloopend
         thispart.append(" s\n");
         sloopmapex(ledump.skill_reqs, eh, moo)
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
         sloopend
         thispart.append(" a\n");
         sloopmapex(ledump.ability_reqs, eh, moo)
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
         sloopend
         lines.append(thispart);
      }
   sloopend
   schfile("occs.strext") <<= lines;
   sloopvec(skill_levels, moo)
      croust>>(33)<<"SKILL LVL ">>(250)<<(moo) << ozendl;
   sloopend
   sloopvec(future_growths, moo)
      croust>>(33)<<"future_growths ">>(250)<<(moo) << ozendl;
   sloopend
}
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
void real_estate_analyze(const string& dumpedfile){
   string fullstr = schfile(dumpedfile).contents();
   Cyano cyano;
   cyano.parseHTMLString(fullstr);
   Cyavex vex(cyano);
   vex/ [&] {
      if(vex == "li" && Morestring::beginsWith(vex["data-testid"], "listing-")){
         vex/ [&] {
            if(vex == "a"){
               string addresser = vex["href"];
               vex/ [&] {
                  if(vex == "h2" && vex.inside("a")){
                     string contents = vex.contents();
                     croust>>(33)<<(contents) << ozendl;
                     croust>>(240)<<"   -> ">>(250)<<(addresser) << ozendl;
                  }
               };
            }
         };
      }
   };
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
int main(int argc, char * argv[]){ CargParser parsa(argc, argv);
   if(parsa("process")){
      env->process();
   }
   else if(parsa("reparse")){
      env->reparse();
   }
   else if(parsa("run")){
      env->maybeCallStarters();
      __asynca.runWithHarbors2();
   }
   else {
      parsa.unhandled();
   }
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

