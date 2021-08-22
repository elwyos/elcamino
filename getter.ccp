//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#bodinc syscom asynca cyavex cyano shing.consolearg schfile scraper telepatia.tcpstation oust csvlooper 
#bodinc sqlite.kv_impl
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
--/real_estate_analyze(const string& dumpedfile)
   
   string fullstr = schfile(dumpedfile).contents();
   
   Cyano cyano;
   cyano.parseHTMLString(fullstr);
   
   // well, let's just print quickly
   //cyano.print();
   
   Cyavex vex(cyano);
   
   vex /&/
      \if vex == "li" && Morestring::beginsWith(vex["data-testid"], "listing-")
         vex /&/
            \if vex == "a"
               string addresser = vex["href"];
               vex /&/
                  \if vex == "h2" && vex.inside("a")
                     string contents = vex.contents();
                     \\/[33] contents
                     \\/[240] "   -> " [250] addresser
               
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
Env/Env()
   checkAllIds();
//////////////////////////////////////////////////////////////////////////////////////////
Env/checkAllIds()
   
   \scope
      Shing::CSVLooper looper("/home/yose/dev/govhack/skills/occs_details.csv", true);
      
      \while true
         auto liner = looper.getLine();
         \if liner
            \if !liner.is_header
               occids.push_back(liner[0]);
         \else
            break;
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/maybeCallStarters()
   \sloop occids
      
      \if suspensions.activesuspendercount > 8
         break;
      
      \if !rawhtmls.has(moo)
         goScrape(moo);
         
   __casynca(500) /
      maybeCallStarters();
      
//////////////////////////////////////////////////////////////////////////////////////////
Env/dump_analysis(string jobid, const string& thedump)
   
   Cyano cyano;
   cyano.parseHTMLString(thedump);
   
   Cyavex vex(cyano);
   
   map<string, string> outdata;
   
   set<string> you_may_also_likes;
   map<string, string> statepercs;
   // the data to export, I guess
   
   map<string, string> knowledge_reqs;
   map<string, string> skill_reqs;
   map<string, string> ability_reqs;
   
   bool got_related_yet = false;
   bool gottitle = false;
   
   string titler;
   
   
   vex /&/
      
      \if vex == "title" && !gottitle
         gottitle = true;
         titler = __chompends(EasyParser(vex.contents()).parseUntil('|', false));
         \\/ [33] "@ " [250] titler
      
      \if vex == "span" && vex.isclass("snapshot-title")
         \if vex.contains("Weekly Pay")
            outdata["weeklypay"] = vex--.contents();
         \if vex.contains("Future Growth")
            outdata["futuregrowth"] = vex--.contents();
         \if vex.contains("Employment Size")
            outdata["empsize"] = vex--.contents();
         \if vex.contains("Skill level rating")
            outdata["skill_lvl"] = vex--.contents();
         \if vex.contains("Full-Time Share")
            outdata["ftshare"] = vex--.contents();
         \if vex.contains("Average full-time")
            outdata["avg_ftime"] = vex--.contents();
         \if vex.contains("Average age")
            outdata["avg_age"] = vex--.contents();
         \if vex.contains("Gender Share")
            outdata["gendershare"] = vex--.contents();
      
      \elif vex == "h5" && vex.contains("You may also like") && !got_related_yet
         got_related_yet = true;
         auto kidder = vex.par()++;
         kidder /&/
            \if kidder == "span" && kidder.par() == "a"
               string name = kidder.contents();
               string link = kidder.par()["href"];
               vector<string> parts;
               __splitOn(link, '=', parts);
               you_may_also_likes.insert(parts.back());
            
      \elif vex.isclass("state-percentage")
         string actualstate = vex.par()--.contents();
         statepercs[actualstate] = vex.contents();
         
      \elif vex["id"] == "knowledge-1" && vex.insideclass("tab-content")
      
         vex /&/
            \if vex == "span" && vex.par().isclass("work-heading")
               string knowledgename = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               
               knowledge_reqs[knowledgename] = skilllevel;
               
      \elif vex["id"] == "skills-1" && vex.insideclass("tab-content")
      
         vex /&/
            \if vex == "span" && vex.par().isclass("work-heading")
               string skillname = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               //\\/ [112] skillname [250] " => " [88] skilllevel
               skill_reqs[skillname] = skilllevel;
               
      \elif vex["id"] == "abilities-1" && vex.insideclass("tab-content")
      
         vex /&/
            \if vex == "span" && vex.par().isclass("work-heading")
               string abilname = vex----.contents();
               string skilllevel = EasyParser(vex.contents()).parseUntil('%', true);
               \\/ [112] abilname [250] " => " [88] skilllevel
               ability_reqs[abilname] = skilllevel;
            
         
         
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
   \\/[33] titler [250] " @ " jobid
   \sloopmap outdata
      \\/[33] eh [250] " => " [220] moo
      
   \scope
      int counta = 0;
      \sloopmap knowledge_reqs
         \if counta != 0
            \\/ [250] ", " \
         counta++;
         \\/[33] eh [250] ":" [220] moo \
      \\/
      
   \scope
      int counta = 0;
      \sloopmap skill_reqs
         \if counta != 0
            \\/ [250] ", " \
         counta++;
         \\/[112] eh [250] ":" [220] moo \
      \\/
      
   \scope
      int counta = 0;
      \sloopmap ability_reqs
         \if counta != 0
            \\/ [250] ", " \
         counta++;
         \\/[202] eh [250] ":" [220] moo \
      \\/
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
Env/goScrape(string jobid)
   
   \\/ [33] "Scraping : " [250] jobid [240] " | progress : " rawhtmls.kv().count() " => " (dumpkv.kv().count()) " / " occids.size()
   
   \if rawhtmls.has(jobid)
      string rawer = rawhtmls.get(jobid);
      dump_analysis(jobid, rawer);
   \else
      auto sus = suspensions++;
      
      Shing::scrape("joboutlook.gov.au/occupations/software-and-applications-programmers?occupationCode=" + jobid) /=res/
         
         sus; // very sus, let's see if this works
         rawhtmls.set(jobid, res.contents);
         
         dump_analysis(jobid, res.contents);
      
         
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/reparse()

   \sloop occids, jobid
      \if rawhtmls.has(jobid)
         string rawer = rawhtmls.get(jobid);
         dump_analysis(jobid, rawer);

//////////////////////////////////////////////////////////////////////////////////////////
Env/processTags()
   
   dumpkv.loadAll();
   
   auto& lemap = dumpkv.obmap();
   
   \sloopmap lemap, eh, dump
   
      \sloopmap dump.knowledge_reqs, knowle, req
         knowledges[knowle].usagecount++;
         
      \sloopmap dump.skill_reqs, skille, req
         skills[skille].usagecount++;
         
      \sloopmap dump.ability_reqs, abile, req
         abilities[abile].usagecount++;
   
   
   
   int counter = 0;
   
   \sloopmap knowledges
      moo.tagindex = counter++;
      moo.type = `\know;
      alltags.push_back(&moo);
      
   \sloopmap skills
      moo.tagindex = counter++;
      moo.type = `\skill;
      alltags.push_back(&moo);
      
   \sloopmap abilities
      moo.tagindex = counter++;
      moo.type = `\abil;
      alltags.push_back(&moo);
      
   
   string tagsfile;
   
   \sloop alltags, moo, counta
      \assert moo->tagindex == counta
      tagsfile.append(moo->name + "|" + moo->type.toString() + "|" + __toString(moo->usagecount) + "\n");
      
      tagmappings[moo->name] = counta;
      
   
   schfile("tags.strext") <<= tagsfile;
   
   
   /*
   vector<Tag*> sortedtags = alltags;
   sort(sortedtags.begin(), sortedtags.end(), [](auto * a, auto * b){
      return a->usagecount < b->usagecount;
   });
   
   \sloop sortedtags
      oustoust.otag(moo->type.toString());
      oustoust[240 ] << " " << moo->name >> 250 << " : " >> 33 << moo->usagecount << ozendl;
   */
   
   
   
//////////////////////////////////////////////////////////////////////////////////////////
Env/getTagNum(const string& thestr) -> int
   auto it = tagmappings.find(thestr);
   \if it != tagmappings.end()
      return it->second;
   
   \assert 0
   return -1;
//////////////////////////////////////////////////////////////////////////////////////////
Env/process()
   
   processTags();
   // first process the tags
   
   string lines;
   
   set<string> skill_levels;
   set<string> future_growths;
   
   \sloop occids
      \if dumpkv.has(moo)
         auto ledump = dumpkv.get(moo);
         
         string thispart;
         thispart.append(moo + "\n");
         
         thispart.append(" d\n");
         \sloopmap ledump.outdata
            \if eh == "futuregrowth"
               future_growths.insert(moo);
            \elif eh == "skill_lvl"
               skill_levels.insert(moo);
            thispart.append("  " + eh + ":" + moo + "\n");
            
         thispart.append(" st\n");
         \sloopmap ledump.state_percs
            thispart.append("  " + eh + ":" + moo + "\n");
            
         thispart.append(" k\n");
         \sloopmap ledump.knowledge_reqs
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
            
         thispart.append(" s\n");
         \sloopmap ledump.skill_reqs
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
            
         thispart.append(" a\n");
         \sloopmap ledump.ability_reqs
            thispart.append("  " + __toString(getTagNum(eh)) + ":" + moo + "\n");
         
         
         lines.append(thispart);
         
   schfile("occs.strext") <<= lines;
   
   \sloopset skill_levels
      \\/ [33] "SKILL LVL " [250] moo
      
   \sloopset future_growths
      \\/ [33] "future_growths " [250] moo
   
   
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
\main
   
   
   \if parsa("process")
      
      env->process();
      
   \elif parsa("reparse")
      env->reparse();
      
   \elif parsa("run")
      env->maybeCallStarters();
      __asynca.runWithHarbors2();
   
   \else
      parsa.unhandled();
   
   
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
