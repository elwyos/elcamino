//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
#bodinc model
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croSliders(serFORM& form)
   
   <>
      \\min-width: 280px
      
   \.splitrow \@env->compvec
   
      <>
         \.h1 "Skill Points!"
         <>
            int total = 0;
            \sloop cli.corelevels
               total += moo;
            <u> __toString(total)
            >. " points"
      
      \.radialchart
         `width 100
         \.radchart_titles {"digital", "initiative/innovation", "learning", "numeracy", "oral comms", "planning/org", "problem solving", "reading", "teamwork", "writing" }
         \.radchart_vals "yours", cli.corelevels
            `fg 33_xcoel
   
   <hr>.s3
      
   \assert cli.corelevels.size() == env->compvec.size()
   <> \@env->compvec
      <> "There's ten core competencies to set, from 1-10. Pick what feels right to you!"
      
      \\max-height: 66vh
      \\overflow-y: scroll
      \sloop env->compvec, moo, counta
         
         \.datom moo->name
            \cap counta

            int curval = cli.corelevels[counta];

            \.splitrow
               \.icobutt "minus"
                  \\min-width: 60px
                  /click
                     auto& leint = cli.corelevels[counta];
                     leint = intclampwithin(leint - 1, 1, 10);
                     \syn \\env->compvec\\

               \.col
                  >. curval
                     \\font-size: 60px
                  <> moo->proflevels[curval].levelname

               \.icobutt "plus"
                  \\min-width: 60px
                  /click
                     auto& leint = cli.corelevels[counta];
                     leint = intclampwithin(leint + 1, 1, 10);
                     \syn \\env->compvec\\
            <p>
               <span> "you can "
               <span>.offk moo->proflevels[curval].description
         
         
         \if counta == 0
            \.cenrow
               \.ico "arrow-down"
            \.cenrow
               <>.muted "Make sure to scroll down! There's 9 more numbers!"
            \.cenrow
               \.ico "arrow-down"
               
      <hr>
         
         int totalpoints = 0;
         \sloop cli.corelevels
            totalpoints += moo;
         
         <> "You Have : " + __toString(totalpoints) + " points"
         \if totalpoints == 100
            <>.muted "Do you really have 100 points? Seriously?"
         \elif totalpoints > 90
            <>.offk "More than 90 points? You must be Superman!"
         \elif totalpoints > 80
            <>.offk "80 points, that's pretty amazing..."
         \elif totalpoints > 25
         \else
            <>.alert "Surely you have more points than that?"
         
   
      <hr>.s3
      \.cenrow
         \.butt "SET!"
            /click
               metCLOSEMODAL();
               \syn \\cli.levels_set_up\\ = true;
               cli.unsyncAnal();
               // just reysnc everything, yeah
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croMainThingos(Occupation * occa, JobAnalysis * jobb, serFORM& form)
   
   \cap occa
   \cap jobb;
   
   <> \@jobb->trashed \@jobb->favorited
   
      \.radialchart
         \\float: right
         `width 100
         \.radchart_titles {"digital", "initiative/innovation", "learning", "numeracy", "oral comms", "planning/org", "problem solving", "reading", "teamwork", "writing" }
         auto& occ = *occa;
         \.radchart_vals "required", occ.reqints
            `fg 196_xcoel
         \.radchart_vals "me", cli.corelevels
            `bg 240_xcoel % 0.7f
            `fg 250_xcoel
      
      /*
      .schip "#" + __toString(joba->result_index)
         \\float:left
      */
      
      \if jobb->trashed
         \.h1.alert
            <strike> occa->name
      \else
         \.h1.offk[jobb->favorited].muted[jobb->trashed] occa->name
      <>.muted occa->description
      
      // match scor
      
      \.wrow
         \.datom "match"
            \if jobb->final_score < 1600
               <>.offk "GREAT!"
            \elif jobb->final_score < 1850
               <>.offk "Close!"
            \elif jobb->final_score < 2200
               <> "Suitable"
            \elif jobb->final_score < 3400
               <>.muted "Maybe"
            \elif jobb->final_score < 4400
               <>.muted "Tough Match"
            \elif jobb->final_score < 10000
               <>.alert "mismatched"
            \else
               <>.alert "very  mismatched"
               
         \.datom "wage"
            \if occa->weeklypay_dollars == 0
               <>.muted "unknown"
            \else
               <> "$" + __toString(occa->weeklypay_dollars)
            
         \.datom "ft hours"
            <> __toString(occa->average_fulltime_hours) + "hr"
            
         \.datom "fulltime"
            <> __toString(occa->fulltime_share) + "%"
            
         \.datom "avg age"
            <> __toString(occa->average_age) + "yrs"
            
         \.datom "gender"
            <> __toString(occa->gendershare_female) + "% female"
            
         \.datom "skill"
            \if occa->skill_level == 0
               <>.offk "Entry Lvl"
            \elif occa->skill_level == 1
               <>.muted "Low"
            \elif occa->skill_level == 2
               <> "Medium"
            \elif occa->skill_level == 3
               <>.alert "High"
            \elif occa->skill_level == 4
               <>.alert "V. High"
               
         \.datom "future"
            \if occa->future_growth == -1
               <>.alert "Decline"
            \elif occa->future_growth == 0
               <>.muted "Stable"
            \elif occa->future_growth == 1
               <> "Moderate"
            \elif occa->future_growth == 2
               <>.offk "Strong"
            \elif occa->future_growth == 3
               <>.alert "V. Strong"
               
      
      string debugstr = "MSM : " + __toString(jobb->mismatch_score)
                        + "/ OVQ : " + __toString(jobb->overqualify_pts)
                        + "/ UDQ : " + __toString(jobb->underqualify_pts)
                        + "/ Final : " + __toString(jobb->final_score);
      <>.muted debugstr
         \\font-size: 0.5em
   
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croDetails(Occupation * occa, JobAnalysis * jobb, serFORM& form)
   
   \cap occa
   \cap jobb;
   
   <>
      \\max-height: 70vh
      \\overflow-y: scroll
      \\min-width: 89vw
      
      <>.neuo
         croMainThingos(occa, jobb, form);
      
      <hr>.s3
      
      \.h3 "Training"
      >. "There's places you can find training for this job!"


      \.wrow
         \.butt.sm "myskills"
            @click
               opennewtab("https://www.myskills.gov.au/jobtrainer/jobtrainercoursesearch?js=8&jtoc=\/occa->occucode\/", true);
               
         \.butt.sm "certifications"
            @click
               opennewtab("https://www.google.com/search?q=\/occa->name\/+certification+site%3Aau", true);
               
         \.butt.sm "joblookout"
            @click
               opennewtab("https://joboutlook.gov.au/occupations/software-and-applications-programmers?occupationCode=\/occa->occucode\/", true);
               
         \.butt.sm "youtube summaries"
            @click
               opennewtab("https://www.youtube.com/results?search_query=\/occa->name\/", true);
      
      <hr>.s3
      \.h3 "Find Jobs"
      
      >. "You can quickly access these job search sites for this occupation"
      
      \.wrow
         
         string dashed_job = occa->name;
         \sloop dashed_job
            moo = tolower(moo);
            \if moo == ' '
               moo = '-';
         
         \.butt.sm "jobsearch.gov.au"
            @click
               opennewtab("https://jobsearch.gov.au/job/search/external?occupation=\/occa->occucode\/", true);
         \.butt.sm "seek.com.au"
            @click
               opennewtab("https://www.seek.com.au/\/dashed_job\/-jobs", true);
         \.butt.sm "careerone.com.au"
            @click
               opennewtab("https://www.careerone.com.au/\/dashed_job\/-jobs", true);
         \.butt.sm "jobsearch.com.au"
            @click
               opennewtab("https://www.jobsearch.com.au/\/dashed_job\/-jobs", true);
         \.butt.sm "google"
            @click
               opennewtab("https://www.google.com/search?q=\/occa->name\/+jobs+site%3Aau", true);
      
               
      <>.muted "Note: if only there's a more concrete data for building the above link collection. We'll have to do with these for now!"
            
      \if occa->used_tools.size() != 0
         <hr>.s3
         \.h3 "Used Tools"
         \sloop occa->used_tools
            <>.neuo
               \.splitrow
                  <> moo->name
                  \.endrow
                     \.icobutt "smile"
                     \.icobutt "frown"
         
         
      <hr>.s3
      \.h3 "Tasks"
      
      >. "You can like/dislike these tasks, and we'll use it to recalculate the ideal jobs for you!"
      
      \sloop occa->tasks
         <>.neuo
            \.splitrow
               <>
                  <> moo.desc
                  <>.offk.sm __toString(moo.percent_time) + "% of time"
               \.endrow
                  \.icobutt "smile"
                  \.icobutt "frown"
         
      <hr>.s3
      \.h3 "Tags"
      \sloop occa->tags
         <>.neuo
            \.splitrow
               <>
                  <> moo.tag->name
                  <>.offk.sm __toString(moo.percentage) + "%"
               \.endrow
                  \.icobutt "smile"
                  \.icobutt "frown"
      
      
      // tags, tasks, etc
      // soon..
      
   
   <hr>.s3
   
   \.splitrow
      \.butt "dismiss"
         /click
            metCLOSEMODAL();
            // here here
      \.icobutt.green[jobb->favorited] "star" \@jobb->favorited
         /click
            \syn \\jobb->favorited\\ = !jobb->favorited;
   
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croSimilarity(Occupation *occa, Occupation * occb, eostri tagtype, serFORM& form)

   
   set<Tag*> alltags;
   
   map<Tag*, OccTag*> atags;
   map<Tag*, OccTag*> btags;
   
   \sloop occa->tags
      \if moo.tag->type == tagtype
         alltags.insert(moo.tag);
         atags[moo.tag] = &moo;
      
   \sloop occb->tags
      \if moo.tag->type == tagtype
         alltags.insert(moo.tag);
         btags[moo.tag] = &moo;
      
      
   \cap occa
   \cap occb
   
   \scope
   
      \.splitrow
         \.h1 occa->name
         \.h2.offk "vs"
         \.h1 occb->name
      
      <>
         \\max-height: 66vh
         \\overflow-y: scroll
         \\min-width: 89vw
         
         \sloop alltags
            bool onleft = atags.count(moo);
            bool onright = btags.count(moo);
            bool common = onleft && onright;
            \.splitrow.neuo[common].fadeneuo[!common].muted[!common]
               \.row
                  \if atags.count(moo)
                     auto * thingo = atags[moo];
                     \.ico "check"
                     >.offk.sm thingo->percentage


               \.cenrow
                  <> moo->name

               \.endrow
                  \if btags.count(moo)
                     auto * thingo = btags[moo];
                     >.offk.sm thingo->percentage
                     \.ico "check"

      
         
   \.butt "dismiss"
      /click
         metCLOSEMODAL();
   
   
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croRelated(Occupation * occa, JobAnalysis * jobb, serFORM& form)
   
   \cap occa
   \cap jobb
   
   \scope
   
      \.h1 "related: "
         >.offk occa->name
   
      <>
         \\max-height: 66vh
         \\overflow-y: scroll
         \\min-width: 89vw
         
         
         >. "showing what we think are the 20 most related ones..."
         \.wrow
            \sloop occa->occlinks, moo
               \if !moo.diffo.calculated
                  assert(moo.target);
                  moo.diffo = moo.origin->calcDifference(*moo.target);
                  moo.diffo.calculated = true;
               
               <>.neuo
                  \\max-width: 250px
                  
                  <h3> moo.target->name
                  
                  \.wrow
                  
                     \scope
                        auto * targeto = moo.target;
                        \cap targeto
                        
                        \.datom "core diff " 
                           <h2> __toString(moo.diffo.core_difference)
                        \.datom "tools" 
                           <h2> __toString(moo.diffo.core_difference) + "%"
                        \.datom "tasks"
                           <h2> __toString(moo.diffo.task_commonality) + "%"
                        \.datom "knwldg"
                           <h2> 
                              \.a __toString(moo.diffo.knowledge_commonality) + "%"
                                 /modal
                                    croSimilarity(occa, targeto, `\know, form);
                        \.datom "ability "
                           <h2> 
                              \.a __toString(moo.diffo.ability_commonality) + "%"
                                 /modal
                                    croSimilarity(occa, targeto, `\abil, form);
                        \.datom "skills"
                           <h2> 
                              \.a __toString(moo.diffo.skill_commonality) + "%"
                                 /modal
                                    croSimilarity(occa, targeto, `\skill, form);
                  
                  /*
                  <>.sm "core diff " + __toString(moo.diffo.core_difference)
                  <>.sm "tools " + __toString(moo.diffo.core_difference) + "%"
                  <>.sm "tasks " + __toString(moo.diffo.task_commonality) + "%"
                  <>.sm "knwldg " + __toString(moo.diffo.knowledge_commonality) + "%"
                  <>.sm "ability " + __toString(moo.diffo.ability_commonality) + "%"
                  <>.sm "skills " + __toString(moo.diffo.skill_commonality) + "%"
                  */
                  
                  auto * newocca = moo.target;
                  \cap newocca
                  
                  \.butt "check"
                     /modal
                        auto * newjobb = & cli.getJobba(newocca);
                        croDetails(newocca, newjobb, form);
                  
               
         
         
         // okay so let's se
         
         
      
   \.butt "dismiss"
      /click
         metCLOSEMODAL();
   
   
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croGraph(Occupation * occa, JobAnalysis * jobb, serFORM& form)
   
   \cap occa
   \cap jobb;
   
   \scope
      <>
         \\max-height: 70vh
         \\overflow-y: scroll
         \\min-width: 89vw

         \.h1 "explore"

         // gotta gather the graphs

         set<Occupation*> similars;
         occa->gatherNearby(similars, 1); // let's try 3..
         
         \\/ [196] "SIMILAR COUNT " [250] similars.size()

         vector<OccLinkFinal> edges;
         \sloop similars
            \sloop moo->occlinks, lelink
               \if similars.count(lelink.origin) && similars.count(lelink.target)
                  edges.push_back(lelink);

         auto * simvec = &similars;
         auto * edgevec = &edges;

         \cap simvec
         \cap edgevec

         \.graph
            auto& similars = *simvec;
            \sloopset similars
               \.gnode moo->occindex, Morestring::firstN(moo->name, 10), 1, 33_xcoel

            auto& edges = *edgevec;
            \sloopvec edges
               \.gedge moo.origin->occindex, moo.target->occindex, 1, 33_xcoel
                  // let's try this eh?


         // tags, tasks, etc
         // soon..
      
   
   <hr>.s3
   
   \.butt "dismiss"
      /click
         metCLOSEMODAL();
   
   
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croAnalysis(JobAnalysis& joba, serFORM& form)
   
   auto& occ = *joba.occ;
   
   auto * occa = &occ;
   auto * jobb = &joba;
   \cap occa
   \cap jobb;
   
   
   <>.neuo
      croMainThingos(occa, jobb, form);
            
            
      \.splitrow
         \.row
            \.icobutt "info-circle"
               /modal
                  croDetails(occa, jobb, form);
            \.icobutt "project-diagram"
               /modal
                  croRelated(occa, jobb, form);
                  //croGraph(occa, jobb, form);
   
         \.endrow
            \.icobutt.green[jobb->favorited] "star"
               /click
                  \syn \\jobb->favorited\\ = !jobb->favorited;
            \.icobutt.red "trash"
               /click
                  \syn \\jobb->trashed\\ = !jobb->trashed;
                  \syn \\current_page\\;
      
      

      
//////////////////////////////////////////////////////////////////////////////////////////
CharTabes/croform(serFORM& form)
   
   // two parts
   \.h1 "Project El Camino"
      >.muted " by team " 
      >.alert "JesseWeMustCode"
   >. "Using a magical algorithm, we can (almost) magically determine which jobs are good for you based on your core competency and skills"
   
   <hr>.s3
   
   <> \@cli.levels_set_up \@current_page
      \if !cli.levels_set_up
         
         >. "To start, click here to set your core competency!"
         \.butt "SETUP"
            /modal
               croSliders(form);
         
      \else
      
         \.splitrow
            \.wrow
               \.butt "setup"
                  /modal
                     croSliders(form);
               \.butt "filters"
                  /modal
                     <>.centext
                        \.h1 "filters"

                        \.butt.green[cli.youth_filter] "youth-friendly jobs" \@cli.youth_filter
                           /click
                              cli.youth_filter = !cli.youth_filter;
                              \syn \\cli.youth_filter\\
                              \syn \\current_page\\

                        <> "We have no idea what a youth friendly job is, so it now only filters jobs that have low barrier to entry. Maybe later we'll iterate!"

                        <> "Sorry, only one filter for now, we really ran out of time!!"
                           \.ico "pray"

                        \.cenrow
                           \.butt "dismiss"
                              /click
                                 metCLOSEMODAL();
               
               \.butt "share"
                  /modal
                     \.h1 "sorry.."
                     >. "We ran out of time and this feature is under construction!"
                     
                     \.butt "dismiss"
                        /click
                           metCLOSEMODAL();
               
            \.endrow
               \.icobutt.sm.green[showing_favs] "star"
                  /click
                     showing_favs = !showing_favs;
                     \syn \\current_page\\
               \.icobutt.sm "refresh"
                  /modal
                     \.h1 "whoops, nothing!"
                     >. "originally this is meant to be for resyncing after changing preferences (the smiley faces on skills)"
                     >. "but we ran out of time.. a story as old as time"
                     \.butt "dismiss"
                        /click
                           metCLOSEMODAL();
               
         <hr>.s3
         
         cli.syncRecommendations();
         
         
         \if showing_favs
            int favs_shown = 0;
            \sloop cli.sortedanal
               \if moo->favorited
                  favs_shown++;
                  croAnalysis(*moo, form);
            
            \if favs_shown == 0
               \.h1 "you haven't favorited any items yet!"
            
         \else
         
            \.cenrow
               \.butt "<"
                  /click
                     \syn \\current_page\\--;
                     \if current_page < 0
                        current_page = 0;

               \.datom "page"
                  <> current_page

               \.butt ">"
                  /click
                     \syn \\current_page\\++;
                     \if current_page * 20 > cli.sortedanal.size()
                        current_page--;
         
            int indexstart = current_page * 20;
            int indexend = indexstart + 20;
            \if indexend > cli.sortedanal.size()
               indexend = cli.sortedanal.size();
               
            
            \if cli.youth_filter
               \.h3.offk "youth-friendly jobs filter is on"
            
            for(int i = indexstart; i < indexend; i++){
               auto& moo = *cli.sortedanal[i];
               
               
               \if moo.trashed
                  auto * joba = &moo;;
                  \cap [joba]
                  <>.neuo
                     <>
                        <striked>.offk moo.occ->name
                        >. " item hidden."
                        \.a.offk " undo hide"
                           /click
                              joba->trashed = false;
                              \syn \\current_page\\;
               \elif cli.youth_filter && !moo.occ->youthFriendly()
                  <>.neuo
                     <>
                        >.offk moo.occ->name
                        >. " filtered by youth-friendly jobs filter"
               \else
                  croAnalysis(moo, form);
            }
               
            \.cenrow
               \.butt "<"
                  @click: _scrolltotop();
                  /click
                     \syn \\current_page\\--;
                     \if current_page < 0
                        current_page = 0;

               \.datom "page"
                  <> current_page

               \.butt ">"
                  @click: _scrolltotop();
                  /click
                     \syn \\current_page\\++;
                     \if current_page * 20 > cli.sortedanal.size()
                        current_page--;
         
   \if !cli.levels_set_up && !everpopped
      metOPENMODAL() /form/
         croSliders(form);
      everpopped = true;
   
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

