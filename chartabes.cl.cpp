////////////////////////////////////////////////////////////
#include "cli.cl.hpp"
#include "model.cl.hpp"
#include "chartabes.cl.hpp"
#include "chartabes.ceeferinc.cl.hpp"
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
void CharTabes::croSliders(serFORM& form){
   { form.cNODE(":div")
      .cloSTYLEBUILDUP("min-width:""280px")
      .cloSTYLEBFLUSH()
      ;}
   form.iso(env->compvec,[this](auto& form){;{ serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER(":h1"); form.cARGER("n", "Skill Points!");form.cCLOSER();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            int total = 0;
            sloopvec(cli.corelevels, moo)
               total += moo;
            sloopend
            { form.cOPENER(":u"); form.cARGER("n", __toString(total));form.cCLOSER();
            }
            { form.cOPENER(":span"); form.cARGER("n", " points");form.cCLOSER()
               ;}
         _poppa.pop();
         }
      _poppa.pop();
      }
      form.radialchart([this](auto& form){
         form.radchart_titles({"digital", "initiative/innovation", "learning", "numeracy", "oral comms", "planning/org", "problem solving", "reading", "teamwork", "writing" });
         
         form.radchart_vals("yours",cli.corelevels)
         .enFG(33_xcoel)
            ;
      })
      .enWIDTH(100)
         ;
   _poppa.pop()
      .enCLASS("splitrow")
      ;}}, "env->compvec @ nd:+gh_skills/chartabes.ccp:12");
   { form.cNODE(":hr")
      .enCLASS("s3")
      ;}
   asserts(cli.corelevels.size() == env->compvec.size(), "");
   form.iso(env->compvec,[this](auto& form){;{ serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      { form.cOPENER(":div"); form.cARGER("n", "There's ten core competencies to set, from 1-10. Pick what feels right to you!");form.cCLOSER();
      }
      sloopveccounta(env->compvec, moo, counta)
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", moo->name);form.cKIDSTART();
            int curval = cli.corelevels[counta];
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("icb"); form.cARGER("n", "minus");form.cCLOSER()
                  .cloHANDLER(true,0, [this, counta](auto& evt){
                     auto& leint = cli.corelevels[counta];
                     leint = intclampwithin(leint - 1, 1, 10);
                     env->compvec ;
                     syn(env->compvec);
                  })
                  .cloSTYLEBUILDUP("min-width:""60px")
                  .cloSTYLEBFLUSH()
                  ;}
               { serVO::FormPopper _poppa(&form); form.cOPENER("col");form.cKIDSTART();
                  { form.cOPENER(":span"); form.cARGER("n", curval);form.cCLOSER()
                     .cloSTYLEBUILDUP("font-size:""60px")
                     .cloSTYLEBFLUSH()
                     ;}
                  { form.cOPENER(":div"); form.cARGER("n", moo->proflevels[curval].levelname);form.cCLOSER();
                  }
               _poppa.pop();
               }
               { form.cOPENER("icb"); form.cARGER("n", "plus");form.cCLOSER()
                  .cloHANDLER(true,0, [this, counta](auto& evt){
                     auto& leint = cli.corelevels[counta];
                     leint = intclampwithin(leint + 1, 1, 10);
                     env->compvec ;
                     syn(env->compvec);
                  })
                  .cloSTYLEBUILDUP("min-width:""60px")
                  .cloSTYLEBFLUSH()
                  ;}
            _poppa.pop()
               .enCLASS("splitrow")
               ;}
            { serVO::FormPopper _poppa(&form); form.cOPENER(":p");form.cKIDSTART();
               { form.cOPENER(":span"); form.cARGER("n", "you can ");form.cCLOSER();
               }
               { form.cOPENER(":span"); form.cARGER("n", moo->proflevels[curval].description);form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            _poppa.pop();
            }
         _poppa.pop();
         }
         if(counta == 0){
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("ic"); form.cARGER("n", "arrow-down");form.cCLOSER();
               }
            _poppa.pop()
               .enCLASS("cenrow")
               ;}
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER(":div"); form.cARGER("n", "Make sure to scroll down! There's 9 more numbers!");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            _poppa.pop()
               .enCLASS("cenrow")
               ;}
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("ic"); form.cARGER("n", "arrow-down");form.cCLOSER();
               }
            _poppa.pop()
               .enCLASS("cenrow")
               ;}
         }
      sloopend
      { serVO::FormPopper _poppa(&form); form.cOPENER(":hr");form.cKIDSTART();
         int totalpoints = 0;
         sloopvec(cli.corelevels, moo)
            totalpoints += moo;
         sloopend
         { form.cOPENER(":div"); form.cARGER("n", "You Have : " + __toString(totalpoints) + " points");form.cCLOSER();
         }
         if(totalpoints == 100){
            { form.cOPENER(":div"); form.cARGER("n", "Do you really have 100 points? Seriously?");form.cCLOSER()
               .enCLASS("muted")
               ;}
         }
         else if(totalpoints > 90){
            { form.cOPENER(":div"); form.cARGER("n", "More than 90 points? You must be Superman!");form.cCLOSER()
               .enCLASS("offk")
               ;}
         }
         else if(totalpoints > 80){
            { form.cOPENER(":div"); form.cARGER("n", "80 points, that's pretty amazing...");form.cCLOSER()
               .enCLASS("offk")
               ;}
         }
         else if(totalpoints > 25){
         }
         else {
            { form.cOPENER(":div"); form.cARGER("n", "Surely you have more points than that?");form.cCLOSER()
               .enCLASS("alert")
               ;}
         }
      _poppa.pop();
      }
      { form.cNODE(":hr")
         .enCLASS("s3")
         ;}
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER("btn"); form.cARGER("n", "SET!");form.cCLOSER()
            .cloHANDLER(true,0, [this](auto& evt){
               metCLOSEMODAL();
               cli.levels_set_up  = true;;
               syn(cli.levels_set_up);
               cli.unsyncAnal();
            })
            ;}
      _poppa.pop()
         .enCLASS("cenrow")
         ;}
   _poppa.pop()
      .cloSTYLEBUILDUP("max-height:""66vh")
      .cloSTYLEBUILDUP("overflow-y:""scroll")
      .cloSTYLEBFLUSH()
      ;}}, "env->compvec @ nd:+gh_skills/chartabes.ccp:32");
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croMainThingos(Occupation * occa, JobAnalysis * jobb, serFORM& form){
   form.iso(jobb->trashed ,jobb->favorited,[this, occa, jobb](auto& form){;{ serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      form.radialchart([this, occa, jobb](auto& form){
         form.radchart_titles({"digital", "initiative/innovation", "learning", "numeracy", "oral comms", "planning/org", "problem solving", "reading", "teamwork", "writing" });
         
         auto& occ = *occa;
         form.radchart_vals("required",occ.reqints)
         .enFG(196_xcoel)
            ;
         form.radchart_vals("me",cli.corelevels)
         .enBG(240_xcoel % 0.7f)
         .enFG(250_xcoel)
            ;
      })
      .enWIDTH(100)
         .cloSTYLEBUILDUP("float:""right")
         .cloSTYLEBFLUSH()
         ;
      if(jobb->trashed){
         { serVO::FormPopper _poppa(&form); form.cOPENER(":h1");form.cKIDSTART();
            { form.cOPENER(":strike"); form.cARGER("n", occa->name);form.cCLOSER();
            }
         _poppa.pop()
            .enCLASS("alert")
            ;}
      }
      else {
         { form.cOPENER(":h1"); form.cARGER("n", occa->name);form.cCLOSER()
            .enCLASS(string(jobb->favorited ? "offk" : "")+" "+string(jobb->trashed ? "muted" : ""))
            ;}
      }
      { form.cOPENER(":div"); form.cARGER("n", occa->description);form.cCLOSER()
         .enCLASS("muted")
         ;}
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "match");form.cKIDSTART();
            if(jobb->final_score < 1600){
               { form.cOPENER(":div"); form.cARGER("n", "GREAT!");form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            }
            else if(jobb->final_score < 1850){
               { form.cOPENER(":div"); form.cARGER("n", "Close!");form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            }
            else if(jobb->final_score < 2200){
               { form.cOPENER(":div"); form.cARGER("n", "Suitable");form.cCLOSER();
               }
            }
            else if(jobb->final_score < 3400){
               { form.cOPENER(":div"); form.cARGER("n", "Maybe");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            }
            else if(jobb->final_score < 4400){
               { form.cOPENER(":div"); form.cARGER("n", "Tough Match");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            }
            else if(jobb->final_score < 10000){
               { form.cOPENER(":div"); form.cARGER("n", "mismatched");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
            else {
               { form.cOPENER(":div"); form.cARGER("n", "very  mismatched");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "wage");form.cKIDSTART();
            if(occa->weeklypay_dollars == 0){
               { form.cOPENER(":div"); form.cARGER("n", "unknown");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            }
            else {
               { form.cOPENER(":div"); form.cARGER("n", "$" + __toString(occa->weeklypay_dollars));form.cCLOSER();
               }
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "ft hours");form.cKIDSTART();
            { form.cOPENER(":div"); form.cARGER("n", __toString(occa->average_fulltime_hours) + "hr");form.cCLOSER();
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "fulltime");form.cKIDSTART();
            { form.cOPENER(":div"); form.cARGER("n", __toString(occa->fulltime_share) + "%");form.cCLOSER();
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "avg age");form.cKIDSTART();
            { form.cOPENER(":div"); form.cARGER("n", __toString(occa->average_age) + "yrs");form.cCLOSER();
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "gender");form.cKIDSTART();
            { form.cOPENER(":div"); form.cARGER("n", __toString(occa->gendershare_female) + "% female");form.cCLOSER();
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "skill");form.cKIDSTART();
            if(occa->skill_level == 0){
               { form.cOPENER(":div"); form.cARGER("n", "Entry Lvl");form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            }
            else if(occa->skill_level == 1){
               { form.cOPENER(":div"); form.cARGER("n", "Low");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            }
            else if(occa->skill_level == 2){
               { form.cOPENER(":div"); form.cARGER("n", "Medium");form.cCLOSER();
               }
            }
            else if(occa->skill_level == 3){
               { form.cOPENER(":div"); form.cARGER("n", "High");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
            else if(occa->skill_level == 4){
               { form.cOPENER(":div"); form.cARGER("n", "V. High");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "future");form.cKIDSTART();
            if(occa->future_growth == -1){
               { form.cOPENER(":div"); form.cARGER("n", "Decline");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
            else if(occa->future_growth == 0){
               { form.cOPENER(":div"); form.cARGER("n", "Stable");form.cCLOSER()
                  .enCLASS("muted")
                  ;}
            }
            else if(occa->future_growth == 1){
               { form.cOPENER(":div"); form.cARGER("n", "Moderate");form.cCLOSER();
               }
            }
            else if(occa->future_growth == 2){
               { form.cOPENER(":div"); form.cARGER("n", "Strong");form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            }
            else if(occa->future_growth == 3){
               { form.cOPENER(":div"); form.cARGER("n", "V. Strong");form.cCLOSER()
                  .enCLASS("alert")
                  ;}
            }
         _poppa.pop();
         }
      _poppa.pop()
         .enCLASS("wrow")
         ;}
      string debugstr = "MSM : " + __toString(jobb->mismatch_score)
                        + "/ OVQ : " + __toString(jobb->overqualify_pts)
                        + "/ UDQ : " + __toString(jobb->underqualify_pts)
                        + "/ Final : " + __toString(jobb->final_score);
      { form.cOPENER(":div"); form.cARGER("n", debugstr);form.cCLOSER()
         .enCLASS("muted")
         .cloSTYLEBUILDUP("font-size:""0.5em")
         .cloSTYLEBFLUSH()
         ;}
   _poppa.pop();
   }}, "jobb->trashed ,jobb->favorited @ nd:+gh_skills/chartabes.ccp:113");
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croDetails(Occupation * occa, JobAnalysis * jobb, serFORM& form){
   { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         croMainThingos(occa, jobb, form);
      _poppa.pop()
         .enCLASS("neuo")
         ;}
      { form.cNODE(":hr")
         .enCLASS("s3")
         ;}
      { form.cOPENER(":h3"); form.cARGER("n", "Training");form.cCLOSER();
      }
      { form.cOPENER(":span"); form.cARGER("n", "There's places you can find training for this job!");form.cCLOSER()
         ;}
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER("btn"); form.cARGER("n", "myskills");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.myskills.gov.au/jobtrainer/jobtrainercoursesearch?js=8&jtoc="+__toString(occa->occucode)+"\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "certifications");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.google.com/search?q="+__toString(occa->name)+"+certification+site%3Aau\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "joblookout");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://joboutlook.gov.au/occupations/software-and-applications-programmers?occupationCode="+__toString(occa->occucode)+"\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "youtube summaries");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.youtube.com/results?search_query="+__toString(occa->name)+"\", true);\n")
            .enCLASS("sm")
            ;}
      _poppa.pop()
         .enCLASS("wrow")
         ;}
      { form.cNODE(":hr")
         .enCLASS("s3")
         ;}
      { form.cOPENER(":h3"); form.cARGER("n", "Find Jobs");form.cCLOSER();
      }
      { form.cOPENER(":span"); form.cARGER("n", "You can quickly access these job search sites for this occupation");form.cCLOSER()
         ;}
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         string dashed_job = occa->name;
         sloopvec(dashed_job, moo)
            moo = tolower(moo);
            if(moo == ' '){
               moo = '-';
            }
         sloopend
         { form.cOPENER("btn"); form.cARGER("n", "jobsearch.gov.au");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://jobsearch.gov.au/job/search/external?occupation="+__toString(occa->occucode)+"\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "seek.com.au");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.seek.com.au/"+__toString(dashed_job)+"-jobs\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "careerone.com.au");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.careerone.com.au/"+__toString(dashed_job)+"-jobs\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "jobsearch.com.au");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.jobsearch.com.au/"+__toString(dashed_job)+"-jobs\", true);\n")
            .enCLASS("sm")
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "google");form.cCLOSER()
         .onmCLICK(true,"\nopennewtab(\"https://www.google.com/search?q="+__toString(occa->name)+"+jobs+site%3Aau\", true);\n")
            .enCLASS("sm")
            ;}
      _poppa.pop()
         .enCLASS("wrow")
         ;}
      { form.cOPENER(":div"); form.cARGER("n", "Note: if only there's a more concrete data for building the above link collection. We'll have to do with these for now!");form.cCLOSER()
         .enCLASS("muted")
         ;}
      if(occa->used_tools.size() != 0){
         { form.cNODE(":hr")
            .enCLASS("s3")
            ;}
         { form.cOPENER(":h3"); form.cARGER("n", "Used Tools");form.cCLOSER();
         }
         sloopvec(occa->used_tools, moo)
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", moo->name);form.cCLOSER();
                  }
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     { form.cOPENER("icb"); form.cARGER("n", "smile");form.cCLOSER();
                     }
                     { form.cOPENER("icb"); form.cARGER("n", "frown");form.cCLOSER();
                     }
                  _poppa.pop()
                     .enCLASS("endrow")
                     ;}
               _poppa.pop()
                  .enCLASS("splitrow")
                  ;}
            _poppa.pop()
               .enCLASS("neuo")
               ;}
         sloopend
      }
      { form.cNODE(":hr")
         .enCLASS("s3")
         ;}
      { form.cOPENER(":h3"); form.cARGER("n", "Tasks");form.cCLOSER();
      }
      { form.cOPENER(":span"); form.cARGER("n", "You can like/dislike these tasks, and we'll use it to recalculate the ideal jobs for you!");form.cCLOSER()
         ;}
      sloopvec(occa->tasks, moo)
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", moo.desc);form.cCLOSER();
                  }
                  { form.cOPENER(":div"); form.cARGER("n", __toString(moo.percent_time) + "% of time");form.cCLOSER()
                     .enCLASS("offk"" ""sm")
                     ;}
               _poppa.pop();
               }
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER("icb"); form.cARGER("n", "smile");form.cCLOSER();
                  }
                  { form.cOPENER("icb"); form.cARGER("n", "frown");form.cCLOSER();
                  }
               _poppa.pop()
                  .enCLASS("endrow")
                  ;}
            _poppa.pop()
               .enCLASS("splitrow")
               ;}
         _poppa.pop()
            .enCLASS("neuo")
            ;}
      sloopend
      { form.cNODE(":hr")
         .enCLASS("s3")
         ;}
      { form.cOPENER(":h3"); form.cARGER("n", "Tags");form.cCLOSER();
      }
      sloopvec(occa->tags, moo)
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", moo.tag->name);form.cCLOSER();
                  }
                  { form.cOPENER(":div"); form.cARGER("n", __toString(moo.percentage) + "%");form.cCLOSER()
                     .enCLASS("offk"" ""sm")
                     ;}
               _poppa.pop();
               }
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER("icb"); form.cARGER("n", "smile");form.cCLOSER();
                  }
                  { form.cOPENER("icb"); form.cARGER("n", "frown");form.cCLOSER();
                  }
               _poppa.pop()
                  .enCLASS("endrow")
                  ;}
            _poppa.pop()
               .enCLASS("splitrow")
               ;}
         _poppa.pop()
            .enCLASS("neuo")
            ;}
      sloopend
   _poppa.pop()
      .cloSTYLEBUILDUP("max-height:""70vh")
      .cloSTYLEBUILDUP("overflow-y:""scroll")
      .cloSTYLEBUILDUP("min-width:""89vw")
      .cloSTYLEBFLUSH()
      ;}
   { form.cNODE(":hr")
      .enCLASS("s3")
      ;}
   { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
         .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
            metCLOSEMODAL();
         })
         ;}
      form.iso(jobb->favorited,[this, occa, jobb](auto& form){;{ form.cOPENER("icb"); form.cARGER("n", "star" );form.cCLOSER()
         .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
            jobb->favorited  = !jobb->favorited;;
            syn(jobb->favorited);
         })
         .enCLASS(string(jobb->favorited ? "green" : ""))
         ;}}, "jobb->favorited @ nd:+gh_skills/chartabes.ccp:328");
   _poppa.pop()
      .enCLASS("splitrow")
      ;}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croSimilarity(Occupation * occa, Occupation * occb, eostri tagtype, serFORM& form){
   set<Tag*> alltags;
   map<Tag*, OccTag*> atags;
   map<Tag*, OccTag*> btags;
   sloopvec(occa->tags, moo)
      if(moo.tag->type == tagtype){
         alltags.insert(moo.tag);
         atags[moo.tag] = &moo;
      }
   sloopend
   sloopvec(occb->tags, moo)
      if(moo.tag->type == tagtype){
         alltags.insert(moo.tag);
         btags[moo.tag] = &moo;
      }
   sloopend
   {
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER(":h1"); form.cARGER("n", occa->name);form.cCLOSER();
         }
         { form.cOPENER(":h2"); form.cARGER("n", "vs");form.cCLOSER()
            .enCLASS("offk")
            ;}
         { form.cOPENER(":h1"); form.cARGER("n", occb->name);form.cCLOSER();
         }
      _poppa.pop()
         .enCLASS("splitrow")
         ;}
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         sloopvec(alltags, moo)
            bool onleft = atags.count(moo);
            bool onright = btags.count(moo);
            bool common = onleft && onright;
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { serVO::FormPopper _poppa(&form); form.cOPENER("row");form.cKIDSTART();
                  if(atags.count(moo)){
                     auto * thingo = atags[moo];
                     { form.cOPENER("ic"); form.cARGER("n", "check");form.cCLOSER();
                     }
                     { form.cOPENER(":span"); form.cARGER("n", thingo->percentage);form.cCLOSER()
                        .enCLASS("offk"" ""sm")
                        ;}
                  }
               _poppa.pop();
               }
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", moo->name);form.cCLOSER();
                  }
               _poppa.pop()
                  .enCLASS("cenrow")
                  ;}
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  if(btags.count(moo)){
                     auto * thingo = btags[moo];
                     { form.cOPENER(":span"); form.cARGER("n", thingo->percentage);form.cCLOSER()
                        .enCLASS("offk"" ""sm")
                        ;}
                     { form.cOPENER("ic"); form.cARGER("n", "check");form.cCLOSER();
                     }
                  }
               _poppa.pop()
                  .enCLASS("endrow")
                  ;}
            _poppa.pop()
               .enCLASS("splitrow"" "+string(common ? "neuo" : "")+" "+string(!common ? "fadeneuo" : "")+" "+string(!common ? "muted" : ""))
               ;}
         sloopend
      _poppa.pop()
         .cloSTYLEBUILDUP("max-height:""66vh")
         .cloSTYLEBUILDUP("overflow-y:""scroll")
         .cloSTYLEBUILDUP("min-width:""89vw")
         .cloSTYLEBFLUSH()
         ;}
   }
   { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
      .cloHANDLER(true,0, [this, occa, occb](auto& evt){
         metCLOSEMODAL();
      })
      ;}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croRelated(Occupation * occa, JobAnalysis * jobb, serFORM& form){
   {
      { serVO::FormPopper _poppa(&form); form.cOPENER(":h1"); form.cARGER("n", "related: ");form.cKIDSTART();
         { form.cOPENER(":span"); form.cARGER("n", occa->name);form.cCLOSER()
            .enCLASS("offk")
            ;}
      _poppa.pop();
      }
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER(":span"); form.cARGER("n", "showing what we think are the 20 most related ones...");form.cCLOSER()
            ;}
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            sloopvec(occa->occlinks, moo)
               if(!moo.diffo.calculated){
                  assert(moo.target);
                  moo.diffo = moo.origin->calcDifference(*moo.target);
                  moo.diffo.calculated = true;
               }
               { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                  { form.cOPENER(":h3"); form.cARGER("n", moo.target->name);form.cCLOSER();
                  }
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     {
                        auto * targeto = moo.target;
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "core diff " );form.cKIDSTART();
                           { form.cOPENER(":h2"); form.cARGER("n", __toString(moo.diffo.core_difference));form.cCLOSER();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "tools" );form.cKIDSTART();
                           { form.cOPENER(":h2"); form.cARGER("n", __toString(moo.diffo.core_difference) + "%");form.cCLOSER();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "tasks");form.cKIDSTART();
                           { form.cOPENER(":h2"); form.cARGER("n", __toString(moo.diffo.task_commonality) + "%");form.cCLOSER();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "knwldg");form.cKIDSTART();
                           { serVO::FormPopper _poppa(&form); form.cOPENER(":h2");form.cKIDSTART();
                              { form.cOPENER("a"); form.cARGER("n", __toString(moo.diffo.knowledge_commonality) + "%");form.cCLOSER()
                                 .cloHANDLER(true,0, [this, occa, jobb, targeto](auto& evt){
                                 metOPENMODAL() / [this, occa, jobb, targeto](serFORM& form){
                                    croSimilarity(occa, targeto, e__(know), form);
                                 };
                                 })
                                 ;}
                           _poppa.pop();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "ability ");form.cKIDSTART();
                           { serVO::FormPopper _poppa(&form); form.cOPENER(":h2");form.cKIDSTART();
                              { form.cOPENER("a"); form.cARGER("n", __toString(moo.diffo.ability_commonality) + "%");form.cCLOSER()
                                 .cloHANDLER(true,0, [this, occa, jobb, targeto](auto& evt){
                                 metOPENMODAL() / [this, occa, jobb, targeto](serFORM& form){
                                    croSimilarity(occa, targeto, e__(abil), form);
                                 };
                                 })
                                 ;}
                           _poppa.pop();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "skills");form.cKIDSTART();
                           { serVO::FormPopper _poppa(&form); form.cOPENER(":h2");form.cKIDSTART();
                              { form.cOPENER("a"); form.cARGER("n", __toString(moo.diffo.skill_commonality) + "%");form.cCLOSER()
                                 .cloHANDLER(true,0, [this, occa, jobb, targeto](auto& evt){
                                 metOPENMODAL() / [this, occa, jobb, targeto](serFORM& form){
                                    croSimilarity(occa, targeto, e__(skill), form);
                                 };
                                 })
                                 ;}
                           _poppa.pop();
                           }
                        _poppa.pop();
                        }
                     }
                  _poppa.pop()
                     .enCLASS("wrow")
                     ;}
                  auto * newocca = moo.target;
                  { form.cOPENER("btn"); form.cARGER("n", "check");form.cCLOSER()
                     .cloHANDLER(true,0, [this, occa, jobb, newocca](auto& evt){
                     metOPENMODAL() / [this, occa, jobb, newocca](serFORM& form){
                        auto * newjobb = & cli.getJobba(newocca);
                        croDetails(newocca, newjobb, form);
                     };
                     })
                     ;}
               _poppa.pop()
                  .enCLASS("neuo")
                  .cloSTYLEBUILDUP("max-width:""250px")
                  .cloSTYLEBFLUSH()
                  ;}
            sloopend
         _poppa.pop()
            .enCLASS("wrow")
            ;}
      _poppa.pop()
         .cloSTYLEBUILDUP("max-height:""66vh")
         .cloSTYLEBUILDUP("overflow-y:""scroll")
         .cloSTYLEBUILDUP("min-width:""89vw")
         .cloSTYLEBFLUSH()
         ;}
   }
   { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
      .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
         metCLOSEMODAL();
      })
      ;}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croGraph(Occupation * occa, JobAnalysis * jobb, serFORM& form){
   {
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { form.cOPENER(":h1"); form.cARGER("n", "explore");form.cCLOSER();
         }
         set<Occupation*> similars;
         occa->gatherNearby(similars, 1); // let's try 3..
         croust>>(196)<<"SIMILAR COUNT ">>(250)<<(similars.size()) << ozendl;
         vector<OccLinkFinal> edges;
         sloopvec(similars, moo)
            sloopvec(moo->occlinks, lelink)
               if(similars.count(lelink.origin) && similars.count(lelink.target)){
                  edges.push_back(lelink);
               }
            sloopend
         sloopend
         auto * simvec = &similars;
         auto * edgevec = &edges;
         form.graph([this, occa, jobb, simvec, edgevec](auto& form){
            auto& similars = *simvec;
            sloopvec(similars, moo)
               form.gnode(moo->occindex,Morestring::firstN(moo->name, 10),1,33_xcoel);
               
            sloopend
            auto& edges = *edgevec;
            sloopvec(edges, moo)
               form.gedge(moo.origin->occindex,moo.target->occindex,1,33_xcoel);
               
            sloopend
         });
         
      _poppa.pop()
         .cloSTYLEBUILDUP("max-height:""70vh")
         .cloSTYLEBUILDUP("overflow-y:""scroll")
         .cloSTYLEBUILDUP("min-width:""89vw")
         .cloSTYLEBFLUSH()
         ;}
   }
   { form.cNODE(":hr")
      .enCLASS("s3")
      ;}
   { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
      .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
         metCLOSEMODAL();
      })
      ;}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croAnalysis(JobAnalysis& joba, serFORM& form){
   auto& occ = *joba.occ;
   auto * occa = &occ;
   auto * jobb = &joba;
   { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      croMainThingos(occa, jobb, form);
      { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
         { serVO::FormPopper _poppa(&form); form.cOPENER("row");form.cKIDSTART();
            { form.cOPENER("icb"); form.cARGER("n", "info-circle");form.cCLOSER()
               .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
               metOPENMODAL() / [this, occa, jobb](serFORM& form){
                  croDetails(occa, jobb, form);
               };
               })
               ;}
            { form.cOPENER("icb"); form.cARGER("n", "project-diagram");form.cCLOSER()
               .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
               metOPENMODAL() / [this, occa, jobb](serFORM& form){
                  croRelated(occa, jobb, form);
               };
               })
               ;}
         _poppa.pop();
         }
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            { form.cOPENER("icb"); form.cARGER("n", "star");form.cCLOSER()
               .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
                  jobb->favorited  = !jobb->favorited;;
                  syn(jobb->favorited);
               })
               .enCLASS(string(jobb->favorited ? "green" : ""))
               ;}
            { form.cOPENER("icb"); form.cARGER("n", "trash");form.cCLOSER()
               .cloHANDLER(true,0, [this, occa, jobb](auto& evt){
                  jobb->trashed  = !jobb->trashed;;
                  syn(jobb->trashed);
                  current_page ;;
                  syn(current_page);
               })
               .enCLASS("red")
               ;}
         _poppa.pop()
            .enCLASS("endrow")
            ;}
      _poppa.pop()
         .enCLASS("splitrow")
         ;}
   _poppa.pop()
      .enCLASS("neuo")
      ;}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void CharTabes::croform(serFORM& form){
   { serVO::FormPopper _poppa(&form); form.cOPENER(":h1"); form.cARGER("n", "Project El Camino");form.cKIDSTART();
      { form.cOPENER(":span"); form.cARGER("n", " by team " );form.cCLOSER()
         .enCLASS("muted")
         ;}
      { form.cOPENER(":span"); form.cARGER("n", "JesseWeMustCode");form.cCLOSER()
         .enCLASS("alert")
         ;}
   _poppa.pop();
   }
   { form.cOPENER(":span"); form.cARGER("n", "Using a magical algorithm, we can (almost) magically determine which jobs are good for you based on your core competency and skills");form.cCLOSER()
      ;}
   { form.cNODE(":hr")
      .enCLASS("s3")
      ;}
   form.iso(cli.levels_set_up ,current_page,[this](auto& form){;{ serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
      if(!cli.levels_set_up){
         { form.cOPENER(":span"); form.cARGER("n", "To start, click here to set your core competency!");form.cCLOSER()
            ;}
         { form.cOPENER("btn"); form.cARGER("n", "SETUP");form.cCLOSER()
            .cloHANDLER(true,0, [this](auto& evt){
            metOPENMODAL() / [this](serFORM& form){
               croSliders(form);
            };
            })
            ;}
      }
      else {
         { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("btn"); form.cARGER("n", "setup");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                  metOPENMODAL() / [this](serFORM& form){
                     croSliders(form);
                  };
                  })
                  ;}
               { form.cOPENER("btn"); form.cARGER("n", "filters");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                  metOPENMODAL() / [this](serFORM& form){
                     { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                        { form.cOPENER(":h1"); form.cARGER("n", "filters");form.cCLOSER();
                        }
                        form.iso(cli.youth_filter,[this](auto& form){;{ form.cOPENER("btn"); form.cARGER("n", "youth-friendly jobs" );form.cCLOSER()
                           .cloHANDLER(true,0, [this](auto& evt){
                              cli.youth_filter = !cli.youth_filter;
                              cli.youth_filter ;
                              syn(cli.youth_filter);
                              current_page ;
                              syn(current_page);
                           })
                           .enCLASS(string(cli.youth_filter ? "green" : ""))
                           ;}}, "cli.youth_filter @ nd:+gh_skills/chartabes.ccp:605");
                        { form.cOPENER(":div"); form.cARGER("n", "We have no idea what a youth friendly job is, so it now only filters jobs that have low barrier to entry. Maybe later we'll iterate!");form.cCLOSER();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER(":div"); form.cARGER("n", "Sorry, only one filter for now, we really ran out of time!!");form.cKIDSTART();
                           { form.cOPENER("ic"); form.cARGER("n", "pray");form.cCLOSER();
                           }
                        _poppa.pop();
                        }
                        { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                           { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
                              .cloHANDLER(true,0, [this](auto& evt){
                                 metCLOSEMODAL();
                              })
                              ;}
                        _poppa.pop()
                           .enCLASS("cenrow")
                           ;}
                     _poppa.pop()
                        .enCLASS("centext")
                        ;}
                  };
                  })
                  ;}
               { form.cOPENER("btn"); form.cARGER("n", "share");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                  metOPENMODAL() / [this](serFORM& form){
                     { form.cOPENER(":h1"); form.cARGER("n", "sorry..");form.cCLOSER();
                     }
                     { form.cOPENER(":span"); form.cARGER("n", "We ran out of time and this feature is under construction!");form.cCLOSER()
                        ;}
                     { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
                        .cloHANDLER(true,0, [this](auto& evt){
                           metCLOSEMODAL();
                        })
                        ;}
                  };
                  })
                  ;}
            _poppa.pop()
               .enCLASS("wrow")
               ;}
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("icb"); form.cARGER("n", "star");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                     showing_favs = !showing_favs;
                     current_page ;
                     syn(current_page);
                  })
                  .enCLASS("sm"" "+string(showing_favs ? "green" : ""))
                  ;}
               { form.cOPENER("icb"); form.cARGER("n", "refresh");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                  metOPENMODAL() / [this](serFORM& form){
                     { form.cOPENER(":h1"); form.cARGER("n", "whoops, nothing!");form.cCLOSER();
                     }
                     { form.cOPENER(":span"); form.cARGER("n", "originally this is meant to be for resyncing after changing preferences (the smiley faces on skills)");form.cCLOSER()
                        ;}
                     { form.cOPENER(":span"); form.cARGER("n", "but we ran out of time.. a story as old as time");form.cCLOSER()
                        ;}
                     { form.cOPENER("btn"); form.cARGER("n", "dismiss");form.cCLOSER()
                        .cloHANDLER(true,0, [this](auto& evt){
                           metCLOSEMODAL();
                        })
                        ;}
                  };
                  })
                  .enCLASS("sm")
                  ;}
            _poppa.pop()
               .enCLASS("endrow")
               ;}
         _poppa.pop()
            .enCLASS("splitrow")
            ;}
         { form.cNODE(":hr")
            .enCLASS("s3")
            ;}
         cli.syncRecommendations();
         if(showing_favs){
            int favs_shown = 0;
            sloopvec(cli.sortedanal, moo)
               if(moo->favorited){
                  favs_shown++;
                  croAnalysis(*moo, form);
               }
            sloopend
            if(favs_shown == 0){
               { form.cOPENER(":h1"); form.cARGER("n", "you haven't favorited any items yet!");form.cCLOSER();
               }
            }
         }
         else {
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("btn"); form.cARGER("n", "<");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                     current_page --;;
                     syn(current_page);
                     if(current_page < 0){
                        current_page = 0;
                     }
                  })
                  ;}
               { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "page");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", current_page);form.cCLOSER();
                  }
               _poppa.pop();
               }
               { form.cOPENER("btn"); form.cARGER("n", ">");form.cCLOSER()
                  .cloHANDLER(true,0, [this](auto& evt){
                     current_page ++;;
                     syn(current_page);
                     if(current_page * 20 > cli.sortedanal.size()){
                        current_page--;
                     }
                  })
                  ;}
            _poppa.pop()
               .enCLASS("cenrow")
               ;}
            int indexstart = current_page * 20;
            int indexend = indexstart + 20;
            if(indexend > cli.sortedanal.size()){
               indexend = cli.sortedanal.size();
            }
            if(cli.youth_filter){
               { form.cOPENER(":h3"); form.cARGER("n", "youth-friendly jobs filter is on");form.cCLOSER()
                  .enCLASS("offk")
                  ;}
            }
            for(int i = indexstart; i < indexend; i++){
               auto& moo = *cli.sortedanal[i];
               if(moo.trashed){
                  auto * joba = &moo;;
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                        { form.cOPENER(":striked"); form.cARGER("n", moo.occ->name);form.cCLOSER()
                           .enCLASS("offk")
                           ;}
                        { form.cOPENER(":span"); form.cARGER("n", " item hidden.");form.cCLOSER()
                           ;}
                        { form.cOPENER("a"); form.cARGER("n", " undo hide");form.cCLOSER()
                           .cloHANDLER(true,0, [this, joba](auto& evt){
                              joba->trashed = false;
                              current_page ;;
                              syn(current_page);
                           })
                           .enCLASS("offk")
                           ;}
                     _poppa.pop();
                     }
                  _poppa.pop()
                     .enCLASS("neuo")
                     ;}
               }
               else if(cli.youth_filter && !moo.occ->youthFriendly()){
                  { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                     { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
                        { form.cOPENER(":span"); form.cARGER("n", moo.occ->name);form.cCLOSER()
                           .enCLASS("offk")
                           ;}
                        { form.cOPENER(":span"); form.cARGER("n", " filtered by youth-friendly jobs filter");form.cCLOSER()
                           ;}
                     _poppa.pop();
                     }
                  _poppa.pop()
                     .enCLASS("neuo")
                     ;}
               }
               else {
                  croAnalysis(moo, form);
               }
            }
            { serVO::FormPopper _poppa(&form); form.cOPENER(":div");form.cKIDSTART();
               { form.cOPENER("btn"); form.cARGER("n", "<");form.cCLOSER()
               .onmCLICK(true,"_scrolltotop();\n")
                  .cloHANDLER(true,0, [this](auto& evt){
                     current_page --;;
                     syn(current_page);
                     if(current_page < 0){
                        current_page = 0;
                     }
                  })
                  ;}
               { serVO::FormPopper _poppa(&form); form.cOPENER("datom"); form.cARGER("n", "page");form.cKIDSTART();
                  { form.cOPENER(":div"); form.cARGER("n", current_page);form.cCLOSER();
                  }
               _poppa.pop();
               }
               { form.cOPENER("btn"); form.cARGER("n", ">");form.cCLOSER()
               .onmCLICK(true,"_scrolltotop();\n")
                  .cloHANDLER(true,0, [this](auto& evt){
                     current_page ++;;
                     syn(current_page);
                     if(current_page * 20 > cli.sortedanal.size()){
                        current_page--;
                     }
                  })
                  ;}
            _poppa.pop()
               .enCLASS("cenrow")
               ;}
         }
      }
   _poppa.pop();
   }}, "cli.levels_set_up ,current_page @ nd:+gh_skills/chartabes.ccp:585");
   if(!cli.levels_set_up && !everpopped){
      metOPENMODAL()/ [this] (auto& form){
         croSliders(form);
      };
      everpopped = true;
   }
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
CharTabes::CharTabes() : CrocMetaBase(serVO::acSESH(), NULL, "nuffer")
,cli(*(GhClient*)0x88888888)
{}
CharTabes::CharTabes(vector<string>& rargs, serVO::acSESH& leacsesh, serVO::Servo& leservo, const shringer& pather) : CrocMetaBase(leacsesh, &leservo, "CharTabes")
,cli(leacsesh.acli->template as<GhClient>())
{metainit(leservo); metasetup(leacsesh, rargs); }
void CharTabes::croc_init(serVO::Connection& conn){
linkConn(conn);
}
shringer CharTabes::metabase_name(){
return shringer("CharTabes");
}
void CharTabes::croc_rpc(serVO::Connection& conn, Shing::RPC ){
}
void CharTabes::croc_proc(serVO::CrocContext& cro){
linkConn(cro.conn);
{ serVO::CrocForm form(this, cro.stringer, "form");
croform(form);
}
}
serVO::RouteSpecifier _routespec_CharTabes("/chara", "bundle/stdweb.dir/stdweb.hpl", [](auto& pather, auto& reqr){
CharTabes * meta = new CharTabes(reqr->routeargs, reqr->acsesh, reqr->conn->servo.ref(), pather);
reqr->conn->croc_meta_schref <<= meta;
reqr->conn->metabase = meta;
meta->croc_init(reqr->conn.ref());
meta->crocfunc = [](serVO::CrocContext& cro){ cro.conn.croc_meta_schref.val<CharTabes>().croc_proc(cro); };
meta->crocification(reqr->conn.ref(), reqr.record);
reqr->conn->rpchandler = [](serVO::Connection& conn, Shing::RPC r){ conn.croc_meta_schref.val<CharTabes>().croc_rpc(conn, r); };
meta->unlinkConn(reqr->conn.ref());
reqr->fin();
}, [](auto& pather, auto& conn){
CharTabes * meta = new CharTabes(conn.routeargs, conn.acseshhold, conn.servo.ref(), pather);
conn.croc_meta_schref <<= meta;
conn.metabase = meta;
meta->croc_init(conn);
meta->crocfunc = [](serVO::CrocContext& cro){ cro.conn.croc_meta_schref.val<CharTabes>().croc_proc(cro); };
conn.rpchandler = [](serVO::Connection& conn, Shing::RPC r){ conn.croc_meta_schref.val<CharTabes>().croc_rpc(conn, r); };
meta->linkConnFromReroute(conn);
});
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

