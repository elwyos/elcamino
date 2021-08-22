//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#bodinc shinglooper oust csvlooper shing.easyparser
//////////////////////////////////////////////////////////////////////////////////////////
#bodinc <algorithm>
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/gatherNearby(set<Occupation*>& ret, int depth)
   
   \if ret.count(this) != 0
      // already visited
      return;
   
   ret.insert(this);
   
   \if depth <= 0
      return;
      
   \sloop occlinks
      moo.target->gatherNearby(ret, depth - 1);
      // sounds cool
   
   
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/add(OccLink lelink)
   
   occlinks_forsort.insert(pair<int, OccLink>(-lelink.score, lelink));
   
   \if occlinks_forsort.size() > 20
      occlinks_forsort.erase(occlinks_forsort.begin());
   
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/youthFriendly() -> bool
   return skill_level <= 1;
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/syncLinks()
   \sloopmap occlinks_forsort
      auto& leback = occlinks.emplace_back();
      leback.origin = this;
      \if moo.a == this
         leback.target = moo.b;
      \else
         leback.target = moo.a;
      leback.score = moo.score;
      
   sort(occlinks.begin(), occlinks.end(), [](auto& a, auto& b){
      return a.score < b.score;
   });
   
   float curvisscore = 1;
   \sloop occlinks
      moo.visscore = curvisscore;
      curvisscore -= 0.1f; // reduce, yeah
   
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/calcDifference(Occupation& rhs) -> OccDifference
   
   OccDifference ret;
   
   int basestat_diff = 0;
   
   assert(rhs.reqints.size() == reqints.size());
   \sloop reqints, moo, counta
      int rhsmoo = rhs.reqints[counta];
      
      int diff = abs(rhsmoo - moo);
      basestat_diff += diff * diff;
      
      ret.core_difference += diff;
      
   
   
   
   int common_count = 0;
   int uncommon_count = 0;
   
   
   int comm_tools = 0;
   int total_tools = 0;
   
   int comm_know = 0;
   int total_know = 0;
   int comm_abil = 0;
   int total_abil = 0;
   int comm_skill = 0;
   int total_skill = 0;
   int comm_task = 0;
   int total_task = 0;
   
   
   map<TaskCluster*, int> common_clusters;
   map<Tool*, int> common_tools;
   map<Tag*, int> common_tags;
   
   \sloop used_tools
      common_tools[moo]++;
      
   \sloop tags
      common_tags[moo.tag]++;
      
   \sloop tasks
      common_clusters[moo.cluster]++;
      
      
   \sloop rhs.used_tools
      common_tools[moo]++;
      
   \sloop rhs.tags
      common_tags[moo.tag]++;
      
   \sloop rhs.tasks
      common_clusters[moo.cluster]++;
   
   
   
   \sloopmap common_tools
      \if moo == 1
         //uncommon_count++;
         // don't penalize different tools (yet)
      \else
         
         comm_tools++;
         
         common_count+= 2;
   
   \sloopmap common_tags
      \if moo == 1
         uncommon_count++;
      \else
         common_count++;
         
         \if eh->type == `\abil
            comm_abil++;
         \elif eh->type == `\know
            comm_know++;
         \elif eh->type == `\skill
            comm_skill++;
            
            
      \if eh->type == `\abil
         total_abil++;
      \elif eh->type == `\know
         total_know++;
      \elif eh->type == `\skill
         total_skill++;
         
         
   \sloopmap common_clusters
      \if moo == 1
         uncommon_count++;
      \else
         comm_task++;
         common_count++;
   
   
   int final_score = basestat_diff + (uncommon_count * 2) - (common_count * 2);
   ret.score = final_score;
   \if common_tools.size() != 0
      ret.tool_commonality = comm_tools * 100 / common_tools.size();
   \else
      ret.tool_commonality = 0;
   
   \if common_clusters.size() != 0
      ret.task_commonality = comm_task * 100 / common_clusters.size();
   \else
      ret.task_commonality = 0;
   
   ret.knowledge_commonality = comm_know * 100 / max(total_know, 1);
   ret.ability_commonality = comm_abil * 100 / max(total_abil, 1);
   ret.skill_commonality = comm_skill * 100 / max(total_skill, 1);
   
   return ret;
   
//////////////////////////////////////////////////////////////////////////////////////////
Occupation/sync(GhClient& cli, JobAnalysis& joba)
   
   int mismatch_score = 0;
   
   int overqualify_pts = 0;
   int underqualify_pts = 0;
   
   \sloopvec reqs
      int theirnum = cli.corelevels[moo.compe->index];
      int reqnum = moo.levelnum;
      
      \if theirnum > reqnum
         // overqualified
         int diff = theirnum - reqnum;
         overqualify_pts += diff;
         mismatch_score += diff;
      \elif theirnum < reqnum
         int diff = reqnum - theirnum;
         
         underqualify_pts += diff;
         mismatch_score += diff;
         
      
   float skillmatch_mass = 0;
   int skillmatch_total = 0;
   
   
   \sloop tasks
      int profi = cli.taskProficiency(moo.cluster);
      \if profi == -1
         skillmatch_mass += 1.4;
         skillmatch_total += 2;
      \elif profi == -2
         skillmatch_mass += 2.4f;
         skillmatch_total += 4;
      \elif profi == 1
         skillmatch_mass += 0.8f;
         skillmatch_total += 2;
      \elif profi == 2
         skillmatch_mass += 0.5f;
         skillmatch_total += 2;
      \else
         skillmatch_mass += 1.0f;
         skillmatch_total += 0;
         
   
   float penalty_mult = 1;
   \if skillmatch_total != 0
      penalty_mult = skillmatch_mass / skillmatch_total;
      
   int penalty_base = max(10, mismatch_score);
   
   int final_score = mismatch_score * 100 + (int)((penalty_base * penalty_mult) * 100);
   
   
   joba.mismatch_score = mismatch_score;
   joba.overqualify_pts = overqualify_pts;
   joba.underqualify_pts = underqualify_pts;
   joba.skill_penalty = (penalty_base * penalty_mult);
   joba.final_score = final_score;
   
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
Env/Env()

   occupations /leocc, leindex/
      leocc.occucode = leindex;
      

   statemap["ACT"] = 0;
   statemap["NSW"] = 0;
   statemap["NT"] = 0;
   statemap["QLD"] = 0;
   statemap["SA"] = 0;
   statemap["TAS"] = 0;
   statemap["VIC"] = 0;
   statemap["WA"] = 0;
   

   load();
   
   postProcess();
   
   syncGraph();
   
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/competency(const string& thestr) -> CoreCompetency&
   return corecomps[thestr];
      
//////////////////////////////////////////////////////////////////////////////////////////
Env/checkLevels()
   \sloop occ_requirement_rank
      oustoust.printSmartColored(moo->name) >> 250 << " : " >> 220 << moo->total_level_req << ozendl;
//////////////////////////////////////////////////////////////////////////////////////////
Env/load()
   
   // --------------------------------------------------------------------
   
   \scope
      Shing::CSVLooper looper("bundle/csvs.dir/occs_details.csv", true);
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               int code = Morestring::toInt(liner[0]);
               string title = liner[1];
               string desc = liner[2];

               auto& occ = occupations[code];
               occ.name = title;
               occ.description = desc;
         \else
            break;
            
   // --------------------------------------------------------------------
   
   \scope
      Shing::CSVLooper looper("bundle/csvs.dir/comps_details.csv", true);
      // core competition
      
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               auto& comp = competency(liner[0]);

               int scorer = Morestring::toInt(liner[2]);

               auto& prole = comp.proflevels[scorer];
               prole.levelnum = scorer;
               prole.levelname = liner[3];
               prole.description = liner[4];
               \if prole.description.size() != 0
                  prole.description[0] = tolower(prole.description[0]);
         \else
            break;
            
   // --------------------------------------------------------------------
            
   \scope
      Shing::CSVLooper looper("bundle/csvs.dir/occs_comps.csv", true);
      
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               int code = Morestring::toInt(liner[0]);
               string title = liner[1];
            
               auto& occ = occupations[code];
               
               auto& comp = competency(liner[2]);
               
               int proflevel = Morestring::toInt(liner[3]);
               
               auto& req = occ.reqs.emplace_back();
               req.compe = &comp;
               req.prole = & comp.proflevels[proflevel];
               req.levelnum = proflevel; // I guess that's it
               occ.total_level_req += req.levelnum;
         \else
            break;
            
   // --------------------------------------------------------------------
            
   \scope
      Shing::CSVLooper looper("bundle/csvs.dir/occs_specialist_tasks.csv", true);
      
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               int code = Morestring::toInt(liner[0]);
               string title = liner[1];
               auto& occ = occupations[code];
               
               
               string spectask = liner[2];
               
               int percentage_time = EasyParser(liner[3])--.parseNumber();
               
               auto& clustergroup = clustergroups[liner[6]];
               auto& specclust = clustergroup.clusters[liner[4]];
               
               auto& task = occ.tasks.emplace_back();
               task.desc = spectask;
               task.cluster = &specclust;
               task.clustergroup = &clustergroup;
               task.percent_time = percentage_time;
               
         \else
            break;
            
   
   // --------------------------------------------------------------------
            
   \scope
      Shing::CSVLooper looper("bundle/csvs.dir/tech_tools.csv", true);
      
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               int code = Morestring::toInt(liner[0]);
               string title = liner[1];
               auto& occ = occupations[code];
               
               auto& letool = tools[liner[2]];
               occ.used_tools.push_back(&letool);
               
         \else
            break;
   
   // --------------------------------------------------------------------
   
   // load tag strext
   \scope
      Strext lestrext;
      lestrext.loadFile("bundle/csvs.dir/tags.strext");
      
      int counta = 0;
      \sloop lestrext
         \if moo
            vector<string> parts;
            __splitOn(moo.tag, '|', parts);
            assert(parts.size() == 3); // of course
            
            eostri typehere = eostri::head(parts[1]);
            
            auto& letag = tags[pair<eostri, string>(typehere, parts[0])];
            letag.name = parts[0];
            letag.vecindex = counta++;
            letag.type = typehere;
            letag.frequency = Morestring::toInt(parts[2]);
      
      tagvec.resize(tags.size());
      
      \assert tags.size() > 0
      
      \sloopmap tags
         asserts(moo.vecindex >= 0 && moo.vecindex < tagvec.size(), "What : " + __toString(moo.vecindex));
         assert(tagvec[moo.vecindex] == NULL);
         tagvec[moo.vecindex] = &moo;
         
      \sloopvec tagvec
         \assert moo != NULL;
      
   // --------------------------------------------------------------------
   
   // load occ strext
   \scope
      Strext lestrext;
      lestrext.loadFile("bundle/csvs.dir/occs.strext");
      \sloop lestrext
         \if moo.tag.size() != 0
            int ider = Morestring::toInt(moo.tag);
            auto it = occupations.find(ider);
            \if it != occupations.end()
               auto& occ = it->second;
               
               \sloop moo, da
                  \if da.tag == "d"
                     \sloop da, va
                        EasyParser parsa(va.tag);
                        string dom = parsa.parseLabel();
                        parsa << ':';
                        \if dom == "avg_age"
                           occ.average_age = parsa.parseNumber();
                        \elif dom == "avg_ftime"
                           occ.average_fulltime_hours = parsa.parseNumber();
                        \elif dom == "ftshare"
                           occ.fulltime_share = parsa.parseNumber();
                        \elif dom == "empsize"
                           occ.employee_size = parsa.parseCommaedNumber();
                        \elif dom == "weeklypay"
                           parsa-- << "$";
                           occ.weeklypay_dollars = parsa.parseCommaedNumber();
                        \elif dom == "futuregrowth"
                           string code = parsa.parseUntilEnd();
                           \if code == "Decline"
                              occ.future_growth = -1;
                           \elif code == "Stable"
                              occ.future_growth = 0;
                           \elif code == "Moderate"
                              occ.future_growth = 1;
                           \elif code == "Strong"
                              occ.future_growth = 2;
                           \elif code == "Very strong"
                              occ.future_growth = 3;
                        \elif dom == "gendershare"
                           occ.gendershare_female = parsa.parseNumber();
                        \elif dom == "skill_lvl"
                           string code = parsa.parseUntilEnd();
                           \if code == "Entry level"
                              occ.skill_level = 0;
                           \elif code == "Lower skill"
                              occ.skill_level = 1;
                           \elif code == "Medium skill"
                              occ.skill_level = 2;
                           \elif code == "High skill"
                              occ.skill_level = 3;
                           \elif code == "Very high skill"
                              occ.skill_level = 4;
                        
                  \elif da.tag == "st"
                     // screw this for now
                  \elif da.tag == "k" || da.tag == "s" || da.tag == "a"
                     \sloop da, va
                        \if va.tag.size() != 0
                           EasyParser parsa(va.tag);
                           int tagnum = parsa.parseNumber();
                           parsa << ':';
                           int percentage = parsa.parseNumber();
                           assert(tagnum >= 0 && tagnum < tagvec.size());
                           auto& leocctag = occ.tags.emplace_back();
                           leocctag.tag = tagvec[tagnum];
                           leocctag.percentage = percentage;
                           // cool, finally
               
            \else
               \\/[196] "Missing occ : " [250] ider
            
         
   
   // --------------------------------------------------------------------
   
   
   \sloopmap occupations
      occ_requirement_rank.push_back(&moo);
   
   sort(occ_requirement_rank.begin(), occ_requirement_rank.end(), [](auto * a, auto * b){
      return a->total_level_req < b->total_level_req;
   });
   
   \sloop occ_requirement_rank, moo, counta
      moo->occ_rr_index = counta;
   
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/postProcess()
   
   // eh..
   compvec.clear();
   int counta = 0;
   \sloopmap corecomps
      compvec.push_back(&moo);
      moo.index = counta;
      counta++;
   
   \sloopmap occupations
      
      moo.reqints.resize(compvec.size());
      \sloopvec moo.reqs, lereq
         moo.reqints[lereq.compe->index] = lereq.levelnum;
         
         
   
   // so now it's alphabetical
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/syncGraph()
   
   // okay here we go..
   
   int counta = 0;
   \sloopmap occupations
      moo.occindex = counta++;
   
   
   \if schfile(".graphlinks").exists()
      Strext strext;
      strext.loadFile(".graphlinks");
      
      \sloop strext, moo
         \if moo
            int number = Morestring::toInt(moo.tag);
            assert(occupations.count(number));
            
            auto& myoccu = occupations[number];
            
            \sloop moo, submoo
               EasyParser subpar(submoo.tag);
               int target = subpar.parseNumber();
               
               OccLinkFinal link;
               assert(occupations.count(target));
               link.target = &occupations[target];
               link.origin = &myoccu;
               link.score = myoccu.calcDifference(*link.target).score;
               myoccu.occlinks.push_back(link);
               // cool, I guess
      
      
   
   \else
      \sloopmap occupations, eha, occa
         \sloopmap occupations, ehb, occb
            
            \if &occa < &occb
               // okay, so different and only one way..
               int difference_score = occa.calcDifference(occb).score;
               OccLink ocli;
               ocli.a = &occa;
               ocli.b = &occb;
               ocli.score = difference_score;
               
               occa.add(ocli);
               occb.add(ocli);
            
      
      \sloopmap occupations
         moo.syncLinks();
         
      
      string filecont;
      
      \sloopmap occupations
         filecont.append(__toString(moo.occucode) + "\n");
         \sloop moo.occlinks, lelink
            filecont.append(" " + __toString(lelink.target->occucode) + " | " + __toString(lelink.score) + "\n");
      
      schfile(".graphlinks") <<= filecont;
      
      
   \\/ [33] "Graph Links Synced!"
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
