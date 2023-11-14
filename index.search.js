var relearn_search_index = [
  {
    "breadcrumb": "Example \u003e online_analysis",
    "content": "last modified: 2023-11-05 by Kodai Okawa ",
    "description": "",
    "tags": [],
    "title": "Check raw data",
    "uri": "/artemis_crib/example/online_analysis/check_rawdata/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-05 by Kodai Okawa If you installed with “curl” command explained previous chapter, you should have artnew command. This command will make new experiment directory interactively.\nBefore using this command, please check and make the directory structure!\nrawdata directory (like /mnt/data or /data? Create it to suit your situation.) output rootfile directory (like /data/art_output?) git repository local repository: suit for online analysis remote repository: suit for offline analysis Let’s start “artnew” command! The word after “:” is your input.\n\u003e artnew Input the experiment name create new artemis work directory? (y/n): y Input experimental name: test Is it OK? (y/n): y Input value: test Check the base directory (default value is fine!) If there are no input, the default value will be used. artnew: If no input is provided, the default value is used. Input repository path or URL (default: https://github.com/okawak/artemis_crib.git): Is it OK? (y/n): y Input value: https://github.com/okawak/artemis_crib.git Input the rawdata directory Input rawdata directory path (default: /data/test/ridf): Is it OK? (y/n): y Input value: /data/test/ridf Input the output directory Input output data directory path (default: /data/test/user): Is it OK? (y/n): y Input value: /data/test/user Input the git setting (PLEASE MAKE your own repository. Local repository will be fine) Based on the repository, do you make your own repository? (y/n): y is it local repository (y/n): y artnew: making LOCAL repository of test Input the local repository path (default: $HOME/repos/exp): Is it OK? (y/n): y Input value: /home/crib/repos/exp -- snip -- art_analysis setting for test is finished!The initial setting is completed!!\n",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "New experiment",
    "uri": "/artemis_crib/setting/new_experiment/index.html"
  },
  {
    "breadcrumb": "Processors",
    "content": "last modified: 2023-08-20 by Kodai Okawa under develop (possibly we will update this data class)\nTTelescopeData Data members TVector3 fPos; // detected position (x, y, z) // simulation: actual position // from data: calculated from strip ID Int_t fXID; // X strip ID Int_t fYID; // Y strip ID Double_t fdE; // total energy deposit of dE detector Double_t fE; // total energy deposit of E detector Double_t fEtotal; // total energy deposit of the telescope DoubleVec_t fEnergyArray; // energy array of all the telescope // DoubleVec_t fTimingArray; // not impremented //=============================================================== // no need?? // kMAXNPARAMETER = 4 (can be settable) Int_t fNE; // number of thick E detector Double_t fdEX; // energy of the first dE detector Double_t fdEY; // energy of the seconde dE detector Double_t fdEXTiming; // timing of the first dE detector Double_t fdEYTiming; // timing of the second dE detector Double_t fEvec[kMAXNPARAMETER]; // energy array of the E detector Double_t fETimingvec[kMAXNPARAMETER]; // timing array of the E detector Methods TVector3 GetPosition() const { return fPos; } void SetPosition(TVector3 vec) { fPos = vec; } void SetPosition(Double_t x, Double_t y, Double_t z) { fPos.SetXYZ(x, y, z); } Int_t GetXID() const {return fXID;} void SetXID(Int_t arg) { fXID = arg; } Int_t GetYID() const {return fYID;} void SetYID(Int_t arg) { fYID = arg; } Double_t GetdEX() const {return fdEX;} void SetdEX(Double_t arg) { fdEX = arg; } Double_t GetdEY() const {return fdEY;} void SetdEY(Double_t arg) { fdEY = arg; } Double_t GetdEXTiming() const {return fdEXTiming;} void SetdEXTiming(Double_t arg) { fdEXTiming = arg; } Double_t GetdEYTiming() const {return fdEYTiming;} void SetdEYTiming(Double_t arg) { fdEYTiming = arg; } Double_t GetEvec(Int_t idx) const { return fEvec[idx]; } void SetEvec(Int_t idx, Double_t val) { fEvec[idx] = val; } Int_t GetEvecSize() { return fNE; } Double_t GetETimingvec(Int_t idx) const { return fETimingvec[idx]; } void SetETimingvec(Int_t idx, Double_t val) { fETimingvec[idx] = val; } Double_t GetdE() const {return fdE;} void SetdE(Double_t arg) { fdE = arg; } Double_t GetE() const {return fE;} void SetE(Double_t arg) { fE = arg; } Double_t GetEtotal() const {return fEtotal;} void SetEtotal(Double_t arg) { fEtotal = arg; } DoubleVec_t GetEnergyArray() const {return fEnergyArray;} void SetEnergyArray(Double_t arg) { fEnergyArray.emplace_back(arg); }",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TTelescopeData",
    "uri": "/artemis_crib/processors/telescope/ttelescopedata/index.html"
  },
  {
    "breadcrumb": "Processors",
    "content": "last modified: 2023-08-20 by Kodai Okawa TReactionInfo Data member // center of the mass system Double_t fEnergy; // kinetic energy Double_t fTheta; // theta Double_t fPhi; // phi // reaction position Double_t fX; Double_t fY; Double_t fZ; // if you define excited statas, the information stored this value Int_t fExcitedID; Methods Double_t GetEnergy() const { return fEnergy; } void SetEnergy(Double_t arg) { fEnergy = arg; } Double_t GetTheta() const { return fTheta; } void SetTheta(Double_t arg) { fTheta = arg; } Double_t GetPhi() const { return fPhi; } void SetPhi(Double_t arg) { fPhi = arg; } Double_t GetX() const { return fX; } Double_t GetY() const { return fY; } Double_t GetZ() const { return fZ; } void SetXYZ(Double_t x, Double_t y, Double_t z) { fX = x; fY = y; fZ = z; } Int_t GetExID() const { return fExcitedID; } void SetExID(Int_t arg) { fExcitedID = arg; }",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TReactionInfo",
    "uri": "/artemis_crib/processors/simulation/treactioninfo/index.html"
  },
  {
    "breadcrumb": "Processors",
    "content": "last modified: 2023-08-20 by Kodai Okawa TParticleInfo Data member ​ TParticleInfo.cc TParticleInfo.cc 1Int_t fMassNumber; // A: particle mass number 2Int_t fAtomicNumber; // Z: particle atomic number 3Int_t fCharge; // Q: particle charge 4 5Double_t fCurrentZ; // particle z position 6Double_t fEnergy; // particle \"kinetic\" energy 7 8TTrack fTrack; // tracking information 9TLorentzVector fVec; // relativistic momentum and energy Method (Getter and Setter) ​ TParticleInfo.cc TParticleInfo.cc 1void SetMassNumber(Int_t val) { fMassNumber = val; } 2Int_t GetMassNumber() const { return fMassNumber; } 3void SetAtomicNumber(Int_t val) { fAtomicNumber = val; } 4Int_t GetAtomicNumber() const { return fAtomicNumber; } 5void SetCharge(Int_t val) { fCharge = val; } 6Int_t GetCharge() const { return fCharge; } 7 8void SetCurrentZ(Double_t val) { fCurrentZ = val; } 9Double_t GetCurrentZ() const { return fCurrentZ; } 10void SetEnergy(Double_t val) { fEnergy = val; } 11Double_t GetEnergy() const { return fEnergy; } 12 13void SetLorentzVector(Double_t x, Double_t y, Double_t z, Double_t t) { fVec.SetXYZT(x, y, z, t); } 14void SetLorentzVector(TLorentzVector val) { fVec = val; } 15TLorentzVector GetLorentzVector() const { return fVec; } 16 17void SetTrack(Double_t x, Double_t y, Double_t z, Double_t a, Double_t b) 18{ 19 fTrack.SetPos(x, y, z); 20 fTrack.SetAngle(a, b); 21} 22TTrack GetTrack() const { return fTrack; } ",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TParticleInfo",
    "uri": "/artemis_crib/processors/simulation/tparticleinfo/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa The following machines have been tested for operation.\n1. Writer’s (Okawa’s) machine Almalinux 9.2 zsh 5.8 gcc 11.3.1 cmake 3.20.2 ROOT 6.28/04 yaml-cpp 0.7.0 2. CRIB’s analysis machine CentOS Linux release 7.9.2009 (Core) zsh 5.5.1 gcc 9.3.1 (using devtoolset-9) cmake 3.28 (install manually) ROOT 6.28/06 yaml-cpp 0.8.0 NOTE:\nFrom 2023/10, Ubuntu system is also avaliable. (issue48) Scripts for some automate operation are written in zsh format. Installation seems to be difficult on macOS (because of clang not gcc) in the current version. ",
    "description": "",
    "tags": null,
    "title": "Requirements",
    "uri": "/artemis_crib/installation/requirements/index.html"
  },
  {
    "breadcrumb": "",
    "content": "This chapter describes how to set up the artemis environment for the CRIB experiment. See from here for initial settings.\n",
    "description": "",
    "tags": null,
    "title": "Installation",
    "uri": "/artemis_crib/installation/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-05 by Kodai Okawa After artnew command, you can see new directory of config files.\n\u003e tree -a art_analysis art_analysis ├── .conf │ ├── artlogin.sh +│ └── test.sh ├── bin │ ├── art_check │ ├── art_setting │ └── artnew +└── test This is experiment name “test” example. In order to load this script test.sh, please modify “EXP_NAME” environment valiable in .zshrc.\n​ .bashrc/.zshrc .bashrc/.zshrc export EXP_NAME=\"test\" # your experiment And load the config file.\n\u003e source ~/.zshrcThen you can make your own work directory by using artlogin command!\nLet’s start “artlogin” command! For example, let’s make default user (user name is the same with experiment name)!\n\u003e artloginIf you want to make your own directory, the following will work.\n\u003e artlogin yourname Check if you really want to make your work directory artlogin: user 'test' not found. create new user? (y/n): y Cloning into '/Users/okawa/art_analysis/test/test'... done. Git setting artlogin: making local git config Input fullname: KodaiOkawa Is it Okay? (y/n): y Input email address: okawa@cns.s.u-tokyo.ac.jp Is it Okay? (y/n): y Symbolic link setting. If there are no problem, the current directory move to your artemis work directory \u003e pwd /home/crib/art_analysis/test/test \u003e ls -lIf your synbolic link seems okay, the setting is all!\nIf artnew setting have problem, the error message will appear. Typical examples are as follows.\nmkdir: /data: Read-only file systemThis is a case of the directory permissions not being set correctly. Use the chmod command or similar to set them correctly and try again.\n",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "New user",
    "uri": "/artemis_crib/setting/new_user/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa Generally, dnf install cmake or brew install cmake support latest version of the cmake, but for some older machine like CentOS7, it is too old to install ROOT.\nThe latest ROOT require CMake 3.16 or higher, and if your system doesn’t support this version, you need to install manually.\nYou can get more information from here.\ncd hoge git clone https://github.com/Kitware/Cmake.git cd Cmake ./bootstrap make -j8 sudo make installIf you want to set the version, you can change the branch (tag). The default branch is master.\n",
    "description": "",
    "tags": [],
    "title": "cmake",
    "uri": "/artemis_crib/installation/cmake/index.html"
  },
  {
    "breadcrumb": "",
    "content": "This chapter describes how to prepare the configuration file for the experiment. If you have already some CRIB artemis environment, Please see from here for initial settings.\n",
    "description": "",
    "tags": null,
    "title": "Setting",
    "uri": "/artemis_crib/setting/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa Before starting analysis, you need to build. The current version of the artemis use “cmake” so the following steps must be taken.\n\u003e artlogin (username) \u003e mkdir build \u0026\u0026 cd build \u003e cmake .. \u003e make -j4 \u003e make install \u003e acdacd is the alias command that is definded after artlogin command. (acd = cd your_work_directory) Also if you changed some processor, you need to do these process.\nThen some important configuration files are automatically created.\n\u003e tree -L 1 . +├── artemislogon.C +├── thisartemis-crib.sh -- snip -- └── run_artemis.cpp Before starting artemis, you need to load the thisartemis-crib.sh. The artlogin command is also used to read this script, so run this command again after the build.\n\u003e artlogin (usename) \u003e aThen you can start artemis by using a command!\n",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "Build",
    "uri": "/artemis_crib/setting/build/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa Artemis uses ROOT library.\nWe confirmed that version 6.28 of the ROOT will work well, but if the ROOT updates, we are not sure that the ARTEMIS will work well, so we recommend to build from the sources.\nFor detailded information, please refer Installing ROOT Recommendations are described below.\n# The latest stable branch gets updated automatically on each release. # You may update your local copy by issuing a `git pull` command from within `root_src/`. cd hoge git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src mkdir root_build root_install \u0026\u0026 cd root_build cmake -DCMAKE_INSTALL_PREFIX=../root_install ../root_src # \u0026\u0026 check cmake configuration output for warnings or errors cmake --build . -- install -j4 # if you have 4 cores available for compilation source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}If there are any problems at the compile, additional packages may need to be installed. See also dependencies.\nInfo If errors related to xrootd, TBB and clad occur, the cmake options -Dxrootd=OFF, -Dimt=OFF and -Dclad=OFF may work respectively.\nI recommend to write source thisroot.sh part in the .bashrc/.zshrc to load this library.\n",
    "description": "",
    "tags": null,
    "title": "ROOT",
    "uri": "/artemis_crib/installation/root/index.html"
  },
  {
    "breadcrumb": "",
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "CRIB_parts",
    "uri": "/artemis_crib/crib_parts/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa Before configuring the settings according to your experiment, let’s check that artemis is working!\n\u003e artlogin (username) \u003e a # start the artemis!Then the prompt change to the artemis [0]. This means you are in artemis console!\nAnalysis using artemis use event loop. It is therefore necessary to load a file that specifies what kind of analysis is to be performed. This file is called the steering file. As an example, let’s check the operation using a steering file that only generates random numbers!\nThe command to load the steering file is add.\nartemis [0] add steering/example/example.tmpl.yaml NUM=0001 MAX=10This means that 10000 random numbers from 0 to MAX=10 are generated (10000 event loops). NUM=0001 is the ID, so any number is okay (related to outputed file name).\nAnd the command to start the event loop is resume. (Often abbreviated as “resume” or “re”. The abbreviated form will also run without problems if there are no conflicts with other commands.)\nartemis [1] res artemis [2] Info in \u003cart::TTimerProcessor::PostLoop\u003e: real = 0.02, cpu = 0.02 sec, total 10000 events, rate 500000.00 evts/secWhen the time taken for such an analysis is displayed, it means that all event loops have been completed. If you are doing a time-consuming analysis and want to suspend the event loop in the middle, suspend command is used. (Often “sus” or “su” is used.)\nartemis [2] susThis event loop creates histogram objects (inherit from TH1 or TH2) and a TTree object. Let’s look at how to access each of these.\nHistogram Details are given in the Histograms section, but histograms are created in an internal directory. To access it, you need to use the same commands as for the linux command, such as “ls” or “cd”, to get to that directory.\nartemis [2] ls artemis \u003e 0 art::TTreeProjGroup test2 test (2) # the first \"\u003e\" means your current position 1 art::TTreeProjGroup test test 2 art::TAnalysisInfo analysisInfo # then let's move to the \"test\" directory! artemis [3] cd 1 artemis [4] ls test \u003e 0 art::TH1FTreeProj hRndm random valueYou can use the command ht [ID] to display a histogram. The ID can be omitted if it is already represented by \u003e.\nartemis [5] zone # make artemis canvas artemis [6] ht 0 Next, let’s also check the histogram in “test2” directory and display two histograms vertically at the same time!\nartemis [7] zone 2 1 # row=2, column=1 artemis [8] ht 0 # show the current hist artemis [9] cd .. artemis [10] ls artemis \u003e 0 art::TTreeProjGroup test2 test (2) 1 art::TTreeProjGroup test test 2 art::TAnalysisInfo analysisInfo artemis [11] cd 0 test2 \u003e 0 art::TH1FTreeProj hRndm2 random number artemis [12] ht 0 TTree Now consider displaying a diagram from a TTree object. The file is created at here.\nartemis [13] fls files 0 TFile output/0001/example_0001.tree.root (CREATE)We use the fcd command to navigate to this root file.\nartemis [14] fcd 0 artemis [15] ls output/0001/example_0001.tree.root \u003e 0 art::TAnalysisInfo analysisInfo 1 art::TArtTree tree treeThe command branchinfo (“br”) displays a list of the branches stored in this tree.\nartemis [16] br random art::TSimpleDataAt the same time, the ROOT command can be used.\nartemis [17] tree-\u003ePrint() ****************************************************************************** *Tree :tree : tree * *Entries : 10000 : Total = 600989 bytes File Size = 86144 * * : : Tree compression factor = 7.00 * ****************************************************************************** *Br 0 :random : art::TSimpleData * *Entries : 10000 : Total Size= 600582 bytes File Size = 85732 * *Baskets : 1 : Basket Size= 3200000 bytes Compression= 7.00 * *............................................................................* Info What is stored in the branch is not the usual type like “double” or “int”, but a class defined in artemis. Therefore, the “artemis” root file cannot be opened by usual ROOT.\nAccessing data in a branch’s data class requires the use of public variables and methods, which can be examined by providing arguments to branchinfo [branch name] or classinfo [class name].\nartemis [18] br random art::TSimpleData Data Members Methods Bool_t CheckTObjectHashConsistency TSimpleData\u0026 operator= TSimpleData\u0026 operator= See also art::TSimpleDataBase\u003cdouble\u003e artemis [19] cl art::TSimpleDataBase\u003cdouble\u003e art::TSimpleDataBase\u003cdouble\u003e Data Members double fValue Methods void SetValue double GetValue Bool_t CheckTObjectHashConsistency TSimpleDataBase\u003cdouble\u003e\u0026 operator= See also art::TDataObject base class for data objectTherefore, it can be seen that it can be accessed by the value fValue.\nartemis [20] zone artemis [21] tree-\u003eDraw(\"random.fValue\u003e\u003e(100,0.,10.)\")Other useful commands artemis [*] help # show the commands we can use artemis [*] save # save the current canvas artemis [*] print # print the current canvas (send to the printer, need to configure) artemis [*] unzoom artemis [*] lgy, lgz, lny, lnz # linear or log scale",
    "description": "",
    "tags": [],
    "title": "artemis commands",
    "uri": "/artemis_crib/setting/artemis_commands/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa Info The yaml-cpp can be installed by some package manager like apt or dnf, but I’m not sure it will work or not in the installation of the artemis.\nCurrent version of the artemis use yaml-cpp-0.7 or higher. In order to use this library, please install from the repository.\nSee also Github repo and README of the artemis Please install it as a shared object like below commands.\ncd hoge git clone https://github.com/jbeder/yaml-cpp.git cd yaml-cpp mkdir build \u0026\u0026 cd build cmake -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF .. make sudo make installDefault install path is /usr/local/lib or /usr/local/lib64. If you do not want to pollute the general environment, specify CMAKE_INSTALL_PREFIX and set PATH environment variable.\ncmake -DCMAKE_INSTALL_PREFIX=/foo/bar -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..",
    "description": "",
    "tags": null,
    "title": "yaml-cpp",
    "uri": "/artemis_crib/installation/yaml-cpp/index.html"
  },
  {
    "breadcrumb": "",
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Processors",
    "uri": "/artemis_crib/processors/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa From this section, we start to configure the settings according to the actual experimental setup. The setting files are followings:\n\u003e tree . ├── mapper.conf ├── conf │ ├── map │ │ ├── ppac │ │ │ ├── dlppac.map -- snip -- │ └── seg │ ├── modulelist.yaml │ └── seglist.yaml -- snip --1. What is the map file? The data obtained from an ADC/TDC is in the form of, for example, “The data coming into channel 10 of an ADC with an ID of 1 is 100”.\n--- title: Data flow example --- graph LR; A{detector} --\u003e|signal| B(TDC/ADC\u003cbr\u003e\u003c/br\u003eID=1, ch=10) B --\u003e|value=100| C[\u003cstrong\u003eData build\u003c/strong\u003e\\nridf file] The role of the map file is to map this value of “100” to an ID that is easy to analyse. An ID that is easy to analyse means, for example, that even if signals from the same detector are acquired with different ADCs/TDCs, the same ID is easier to handle in the analysis.\n--- title: Data flow example --- graph LR; A(TDC/ADC\u003cbr\u003e\u003c/br\u003eID=1, ch=10) --\u003e|value=100| B[\u003cstrong\u003eData build\u003c/strong\u003e\\nridf file] B --\u003e|value=100 mapping to| C(analysis\u003cbr\u003e\u003c/br\u003eID=2, ch=20) After mapping, we can check the data of this “100” from ID=2 and ch=20. This ID and channel (2, 20) are provided for convenience, so you can freely set them.\nSo, in summary, the map file role is like this:\n--- title: role of the map file --- graph LR; A(DAQ ID\u003cbr\u003e\u003c/br\u003eID=1, ch=10) \u003c--\u003e|mapping| B(analysis ID\u003cbr\u003e\u003c/br\u003eID=2, ch=20) 2. map files CRIB is using Babirl for the DAQ system. In this system, the DAQ ID represented in the example is determined by five parameters.\ndevice ID (dev) focal plane (fp) detector ID (det) geometry ID (geo) channel (ch) The dev, fp, det and geo parameters can be set from DAQ setting. For the CRIB experiment, conventionally we set dev=12, fp=0–2 (for each MPV), det=6,7 (6=energy, 7=timing) and geo=from 0. But you can change it freely.\nAnd analysis ID represented in the example is determined by two parameters.\nCategory ID (CatID, cid) id (fID) Of cource you can also set the value freely.\nThe format of the map file is followings:\n# [category] [id] [[device] [focus] [detector] [geo] [ch]] .... 1, 0, 12, 1, 6, 0, 0 Note The id should start from “0”. The ADC/TDC channel start from “0”. The leading “#” is treated as a comment statement. you can set several “DAQ ID” to one “analysis ID” like this: # map for SSD # [category] [id] [[device] [focus] [detector] [geo] [ch]] .... # # Map: energy, timing # #-------------------------------------------------------------------- 1, 0, 12, 1, 6, 0, 0, 12, 2, 7, 0, 0 Please create map files for all detectors like this!\n3. mapper.conf You can select the map file to be loaded with this file. This is especially useful when separating map files for testing from map files for the experiment.\nThe format is followings: (path/to/the/map/file number)\n# file path for configuration, relative to the working directory # (path to the map file) (Number of columns) # cid = 1: rf conf/map/rf/rf.map 1In the note example above, the number is 2.\nPlease do not forget to add to the mapper.conf after you add some map files.\n4. (option) segment files This conf files are used when you use “chkseg.yaml” steering file. This steering file create raw data 2D histograms. I will describe in the Example: online_analysis/Check raw data in detail.\n",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "Map configuration",
    "uri": "/artemis_crib/setting/map_config/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa From the current situation, CRIB experiment doesn’t use GET system, so we describe how to install it without linking it to GET decoder.\nAlso, it can link to openMPI, but the below commands assume not using openMPI. See artemis repo for more information.\ncd hoge git clone https://github.com/artemis-dev/artemis.git -b develop cd artemis mkdir build cd build cmake -DCMAKE_INSTALL_PREFIX=../install .. make -j8 make install source ../install/bin/thisartemis.shThen, \u003cCMAKE_INSTALL_PREFIX\u003e/bin/thisartemis.sh will be created and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.\nAlso, I recommend to write source thisartemis.sh part in the .bashrc/.zshrc to load this library.\nAnother option is to use module command to manage the environment. It is also written in artemis repo.\nNote This is 2023/10/29 current information\nOkawa think there is a grammatical error in the sources/main/thisartemis.sh.in, so I changed like:\n-if [ \"@BUILD_GET@\" == \"ON\" ]; then +if [[ \"@BUILD_GET@\" == \"ON\" ]]; then export LD_LIBRARY_PATH=@GET_LIB_DIR@:$LD_LIBRARY_PATH fi -if [ \"@MPI_CXX_FOUND@\" == \"TRUE\" ]; then +if [[ \"@MPI_CXX_FOUND@\" == \"TRUE\" ]]; then dir=@MPI_CXX_LIBRARIES@ libdir=\"$(dirname $dir)\" ",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "artemis",
    "uri": "/artemis_crib/installation/artemis/index.html"
  },
  {
    "breadcrumb": "",
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Example",
    "uri": "/artemis_crib/example/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa The steering file (yaml format) is a file that directs the process of how the obtained data is to be processed. The artemis is an object-oriented program whose components are called processors, which are combined to process data.\nThe main role of the “processor” is to process data from an input data called InputCollection and create an output data called OutputCollection. This “OutputCollection” will be stored into the root file as a “tree”. Complex processing can be performed by using “processor” in multiple steps.\nI will explain how to create this “steering” file using Si detector data as an example.\n--- title: example of the data process structure --- graph TD; subgraph event loop A--\u003eB(mapping processor\u003cbr\u003e\u003c/br\u003eInputCollection: decoded data\\nOutputCollection: Si raw data) B--\u003eC(calibration processor\u003cbr\u003e\u003c/br\u003eInputCollection: Si raw data\\nOutputCollection: Si calibrated data) C--\u003eX((event end)) X--\u003eA end subgraph DAQ D(Raw binary data)--\u003eA(decode processor\u003cbr\u003e\u003c/br\u003eInputCollection: raw data\\nOutputCollection: decoded data) end Steering file: Silicon data case First, I describe what is the Anchor and how to use command line arguments. See example here.\n​ chkssd.yaml chkssd.yaml Anchor: - \u0026input ridf/@NAME@@NUM@.ridf - \u0026output output/@NAME@/@NUM@/chkssd@NAME@@NUM@.root - \u0026histout output/@NAME@/@NUM@/chkssd@NAME@@NUM@.hist.root You can use variables from elsewhere in the steering file by declaring them as such. For example if you write:\nsomething: *inputThis unfolds as follows:\nsomething: ridf/@NAME@@NUM@.ridfVariables enclosed in @ can also be specified by command line arguments. For example, If you command like the following in the artemis console,\nartemis [1] add steering/chkssd.yaml NAME=run NUM=0000it is considered as\n​ chkssd.yaml chkssd.yaml Anchor: - \u0026input ridf/run0000.ridf - \u0026output output/run/0000/chkssdrun0000.root - \u0026histout output/run/0000/chkssdrun0000.hist.root 1. General processor When using the “Babirl”, the data file will be in the form of “ridf”. In this case, the beginning and end of the steering file is usually as follows.\n​ chkssd.yaml chkssd.yaml Processor: - name: timer type: art::TTimerProcessor - name: ridf type: art::TRIDFEventStore parameter: OutputTransparency: 1 InputFiles: - *input SHMID: 0 - name: mapper type: art::TMappingProcessor parameter: OutputTransparency: 1 # -- snip -- - name: outputtree type: art::TOutputTreeProcessor parameter: FileName: - *output TTimerProcessor: measure the time taken to process data TRIDFEventStore: decode the ridf file and store the value in EventStore (see below) TMappingProcessor: read mapper.conf for mapping TOutputTreeProcessor: writes data to the root file OutputTransparency is set to 1, indicating that “OutputCollection” is not exported to the root file.\n2. Mapping processor The “mapping processor” puts the data stored in the “EventStore” into a certain data class based on “mapper.conf”. Assume the following map file is used.\n# map for SSD # [category] [id] [[device] [focus] [detector] [geo] [ch]] .... # # Map: energy, timing # #-------------------------------------------------------------------- 1, 0, 12, 1, 6, 0, 0, 12, 2, 7, 0, 0In this case, since we are assuming data from the Si detector, let’s consider putting it in a data class that stores energy and timing data, “TTimingChargeData”! The processor mapping to this data class is “TTimingChargeMappingProcessor”.\n​ chkssd.yaml chkssd.yaml Processor: - name: proc_ssd_raw type: art::TTimingChargeMappingProcessor parameter: CatID: 1 ChargeType: 1 ChargeTypeID: 0 TimingTypeID: 1 Sparse: 1 OutputCollection: ssd_raw CatID: enter here the same number as the cid (category ID) in the map file. ChargeType: there are various ways to store energy (charge) and timing using this processor, but this time “1” is specified to use the processing method using ADC and TDC. Charge/TimingTypeID: The map file has two sets of five parameters that specify the DAQ ID. Which of these parameters specifies which represents the energy (charge) and timing. (it start from “0”) Sparse: parameter for the output data structure OutputCollection: name of the data class to be output Then, you can access the ssd_raw data by using like tree-\u003eDraw(\"ssd_raw.fCharge\")\n3. Calibration processor While the data in the “ssd_raw” are raw channel of the ADC and TDC, it is important to see the data calibrated to energy and time. I will explain the details in Example: preparation/macro, but here I will discuss the calibration processors assuming that the following appropriate calibration files have been created.\nprm/ssd/ch2MeV.dat prm/ssd/ch2ns.dat Now, let’s load these files.\n​ chkssd.yaml chkssd.yaml Processor: - name: proc_ssd_ch2MeV type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2MeV Type: art::TAffineConverter FileName: prm/ssd/ch2MeV.dat OutputTransparency: 1 - name: proc_ssd_ch2ns type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2ns Type: art::TAffineConverter FileName: prm/ssd/ch2ns.dat OutputTransparency: 1 To calibrate data contained in a TTimingChargeData class, a TTimingChargeCalibrationProcessor processor is used.\n​ chkssd.yaml chkssd.yaml Processor: - name: proc_ssd type: art::TTimingChargeCalibrationProcessor parameter: InputCollection: ssd_raw OutputCollection: ssd_cal ChargeConverterArray: prm_ssd_ch2MeV TimingConverterArray: prm_ssd_ch2ns Note here that “InputCollection”, “ChargeConverterArray”, and “TimingConverterArray” use the same names as the highlighted lines in the code block above.\nInfo The arguments to be used will vary depending on the processor used, so please check and write them according to the situation. If you want to check from artemis console, you can use “processordescription” command like this\n\u003e artlogin (username) \u003e a artemis [0] processordescription art::TTimingChargeCalibrationProcessor Processor: - name: MyTTimingChargeCalibrationProcessor type: art::TTimingChargeCalibrationProcessor parameter: ChargeConverterArray: no_conversion # [TString] normally output of TAffineConverterArrayGenerator InputCollection: plastic_raw # [TString] array of objects inheriting from art::ITiming and/or art::ICharge InputIsDigital: 1 # [Bool_t] whether input is digital or not OutputCollection: plastic # [TString] output class will be the same as input OutputTransparency: 0 # [Bool_t] Output is persistent if false (default) TimingConverterArray: no_conversion # [TString] normally output of TAffineConverterArrayGenerator Verbose: 1 # [Int_t] verbose level (default 1 : non quiet) 4. Split files If you want to analyse a large number of detectors, not just Si detectors, writing everything in one steering file will result in a large amount of content that is difficult to read.\nIn that case, we can use “include” node!\nIn the examples we have written so far, let’s only use a separate file for the part related to the analysis of the Si detector.\n​ chkssd.yaml chkssd.yaml # -- snip -- Processor: # -- snip -- - include: ssd/ssd_single.yaml # -- snip -- ​ ssd/ssd_single.yaml ssd/ssd_single.yaml Processor: # parameter files - name: proc_ssd_ch2MeV type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2MeV Type: art::TAffineConverter FileName: prm/ssd/ch2MeV.dat OutputTransparency: 1 - name: proc_ssd_ch2ns type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2ns Type: art::TAffineConverter FileName: prm/ssd/ch2ns.dat OutputTransparency: 1 # data process - name: proc_ssd_raw type: art::TTimingChargeMappingProcessor parameter: CatID: 1 ChargeType: 1 ChargeTypeID: 0 TimingTypeID: 1 Sparse: 1 OutputCollection: ssd_raw - name: proc_ssd type: art::TTimingChargeCalibrationProcessor parameter: InputCollection: ssd_raw OutputCollection: ssd_cal ChargeConverterArray: prm_ssd_ch2MeV TimingConverterArray: prm_ssd_ch2ns In this way, the contents of “chkssd.yaml” can be kept concise, while the same process is carried out. Note that the file paths here are relative to the paths from the steering directory. Parameter files, for example, are relative paths from the working directory (one level down).\nUtilising file splitting also makes it easier to check the steering files that analyse a large number of detectors like this.\n​ chkall.yaml chkall.yaml # -- snip -- Processor: # -- snip -- - include: rf/rf.yaml - include: ppac/f1ppac.yaml - include: ppac/dlppac.yaml - include: mwdc/mwdc.yaml - include: ssd/ssd_all.yaml # -- snip -- Info When you include other files, you can set arguments. This can be used, for example, to share variables. Details will be introduced in the example section.\nSummary The whole steering file is as follows:\n​ chkssd.yaml chkssd.yaml Anchor: - \u0026input ridf/@NAME@@NUM@.ridf - \u0026output output/@NAME@/@NUM@/chkssd@NAME@@NUM@.root - \u0026histout output/@NAME@/@NUM@/chkssd@NAME@@NUM@.hist.root Processor: - name: timer type: art::TTimerProcessor - name: ridf type: art::TRIDFEventStore parameter: OutputTransparency: 1 InputFiles: - *input SHMID: 0 - name: mapper type: art::TMappingProcessor parameter: OutputTransparency: 1 - include: ssd/ssd_single.yaml # output root file - name: outputtree type: art::TOutputTreeProcessor parameter: FileName: - *output ​ ssd/ssd_single.yaml ssd/ssd_single.yaml Processor: # parameter files - name: proc_ssd_ch2MeV type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2MeV Type: art::TAffineConverter FileName: prm/ssd/ch2MeV.dat OutputTransparency: 1 - name: proc_ssd_ch2ns type: art::TParameterArrayLoader parameter: Name: prm_ssd_ch2ns Type: art::TAffineConverter FileName: prm/ssd/ch2ns.dat OutputTransparency: 1 # data process - name: proc_ssd_raw type: art::TTimingChargeMappingProcessor parameter: CatID: 1 ChargeType: 1 ChargeTypeID: 0 TimingTypeID: 1 Sparse: 1 OutputCollection: ssd_raw - name: proc_ssd type: art::TTimingChargeCalibrationProcessor parameter: InputCollection: ssd_raw OutputCollection: ssd_cal ChargeConverterArray: prm_ssd_ch2MeV TimingConverterArray: prm_ssd_ch2ns \u003e acd \u003e a artemis [0] add steering/chkssd.yaml NAME=run NUM=0000",
    "description": "",
    "tags": [],
    "title": "Steering",
    "uri": "/artemis_crib/setting/steering/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-02 by Kodai Okawa For the convinience, we use one directory to store raw data (ridf files) and make symbolic link to each user work directory. So first, we need to make raw data directory.\nThere are three option to do so.\nuse the default SSD/HDD of analysis PC use the external SSD/HDD of analysis PC (need to mount it) use network file system (NFS) and mount it 1 and 2 options are mainly used for offline analysis, while 3 option is used for online analysis.\n1. use the default SSD/HDD of analysis PC If you have large size of main storage, the one option is easiest way. Just like:\ncd ~ mkdir data (or where you want to put) cd data rsync hoge (cp or scp to put the raw data)The symbolic link process will be done in the next process.\n2. use the external SSD/HDD of analysis PC (need to mount it) When your main storage is not so large, you may think to use external storage. For example, main storage is used for OS installation and external storage is used for experimental data. (I think this case is for personal analysis using your own PC.)\nIn that case, you need to do:\nmount the external storage check and set the file permission to be able to read or write it. The format and mount process is very depend on the situation, so please check the way in other place. One important point is that we have output root file when we start to analysis, so it may need to make the directory for outputed root files in the external storage.\n3. use network file system (NFS) and mount it For online analysis, the best option is to get the data via a file server, as there is no time to transfer the raw data files each time.\nThis is example of CRIB system.\n--- title: Network system of CRIB --- graph LR; A(MPV E7) --\u003e D{\u003cstrong\u003eDAQ main PC\u003c/strong\u003e\u003cbr\u003e\u003c/br\u003efile server} B(MPV1 J1) --\u003e D C(MPV2 J1) --\u003e D D --\u003e E[Analysis PC] As this figure, we use file server in the DAQ main PC.\n3.1 server setting The OS of the DAQ PC is CentOS7, but I think it can be applied for current OS. (like yum -\u003e dnf) First, please install required package.\nsudo yum install -y rpcbind nfs-utilsThen prepare the raw data file directory for sharing.\nmkdir /data (any location) And setting file for nfs is /etc/exports, and here is the example.\n/data 192.168.1.5 /data 192.168.2.0/24(rw)The first one means the host of 192.168.1.5 can access the shared directory “/data”. In the default setting, users cannot write to this directory.\nThe host of the second line means the range that can access. If we add rw option, users can write to this directory. For the other options, please check the official site.\nFinally, the following command is used to reflect the settings.\nfirewall-cmd --permanent --zone=public --add-service=nfs firewall-cmd --reload systemctl start rpcbind systemctl enable rpcbind systemctl start nfs systemctl enable nfsIf you do not have a firewall set up, you do not need the relevant commands.\n3.2 client setting The package is also needed for client PC.\nsudo yum install -y nfs-utilsPrepare the mounted directory and mount it.\nmkdir /mnt/data sudo mount -t nfs host_IP_address:/data /mnt/data df -hIf you see the mounted configuration, your nfs configuration is complete.\nTo reflect the mount settings when the system is rebooted, add a setting to /etc/fstab.\n​ /etc/fstab /etc/fstab + host_IP_address:/data /mnt/data nfs defaults 0 0 sudo mount -a",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "mount setting",
    "uri": "/artemis_crib/installation/mount/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa In the online analysis, it is important to have immediate access to data. The artemis can produce TTree object but long commands are needed to access, for example,\nartemis [1] fcd 0 # move to the created rootfile artemis [2] zone 2 2 # make a \"artemis\" 2x2 canvas artemis [3] tree-\u003eDraw(\"ssd_cal.fCharge:ssd_cal.fTiming\u003e(100,0.,100., 100,0.,100)\",\"ssd_cal.fCharge \u003e 1.0\",\"colz\")This would take time if there are some histograms that you want to display immediately…\nTherefore, if you know in advance the diagram you want to see, it is useful to predefine its histogram! The processor used is TTreeProjectionProcessor. I would like to explain how to use this one.\n1. Steering file Let’s look at how histograms are defined when looking at SSD data. First, let’s prepare the steering file as follows! please see previous section for omissions.\n​ chkssd.yaml chkssd.yaml # -- snip -- - include: ssd/ssd_single.yaml # Histogram - name: projection_ssd type: art::TTreeProjectionProcessor parameter: FileName: hist/ssd/ssd.yaml Type: art::TTreeProjection OutputFilename: *histout # output root file - name: outputtree type: art::TOutputTreeProcessor parameter: FileName: - *output The histogram is created based on the TTree object, so describe the processing of the histogram after the part that represents the data processing and before the part that outputs the TTree (TOutputTreeProcessor).\nThere are three points to note here.\nIt is possible to create a root file containing only a histogram as well as a root file containing a TTree. (Look at the node part of the OutputFilename.) The histogram itself is defined in a separate file to this one, written on the highlighted line above. The file paths are relative to the working directory. Therefore, I would now like to show the histogram definition file.\n2. Histogram file First please look at this example.\n​ hist/ssd/ssd.yaml hist/ssd/ssd.yaml 1anchor: 2 - \u0026energy [\"ssd_cal.fCharge\",100,0.,100.] 3 - \u0026timing [\"ssd_cal.fTiming\",100,0.,100.] 4alias: 5 energy_cut: ssd_cal.fCharge\u003e1.0; 6group: 7 - name: ssd_test 8 title: ssd_test 9 contents: 10 - name: ssd_energy 11 title: ssd_energy 12 x: *energy 13 14 - name: ssd_timing 15 title: ssd_timing 16 x: *timing 17 18 - name: ssd_energy and timing 19 title: ssd_energy and timing 20 x: *timing 21 y: *energy 22 cut: energy_cut This definition file consists of three parts.\n2.1 anchor The actual core part is the “2.3 group”, but “2.1 anchor” and “2.2 alias” are often used to make this part easier to write. The anchor defines the first argument of tree-\u003eDraw(\"ssd_cal.fCharge\u003e(100,0.,100.)\",\"ssd_cal.fCharge \u003e 1.0\")\nThe array stored in the variable named “energy” in the second line looks like [str, int, float, float] and has the following meanings\nstr: Name of the object (need double quote “”) int: Number of bins of histogram float: Minimum value of histogram range float: Maximum value of histogram range As you might imagine, inside the first argument you can also add operations such as TMath::Sqrt(ssd_cal.fCharge) or ssd_cal.fCharge-ssd_cal.fTiming, because it is the same with “tree-\u003eDraw”.\nNote, however, that the definition here is for one-dimensional histograms. Two-dimensional histograms will be presented in Section 2.3. It is very simple to write!\n2.2 alias This part is used when applying gates to events (often we call it as “cut” or “selection”). For example, if you only want to see events with energies above 1.0 MeV, you would write something like tree-\u003eDraw(\"energy\",\"energy\u003e1.0\").\nThe alias node is used to define the part of energy\u003e1.0\nNote A semicolon “;” at the end of the sentence may be needed…? please check the source.\n2.3 group The histogram is defined here and the object is stored in a directory in artemis (ROOT, TDirectory). In the example shown above, the directory structure would look like this:\n(It is not actually displayed in this way).\n# in artemis . └── ssd_test ├── ssd_energy (1D hist) ├── ssd_timing (1D hist) └── ssd_energy and timing (2D hist)The first “name” and “title” nodes are arguments of TDirectory instance. Also the second “name” and “title” nodes are arguments of instance of TH1 or TH2 object. The other “x”, “y” and “cut” is the important node!\nIf there are only “x” nodes -\u003e 1D histogram If there are both “x” and “y” nodes -\u003e 2D histogram In any case, it can be gated by adding a “cut” node. 3. Commands for histograms There are many useful command for checking the histogram objects. These are similar to the ANAPAW commands.\nls : check the artemis directory \u003e artlogin (username) \u003e a artemis [0] add steering/chkssd.yaml NAME=hoge NUM=0000 artemis [1] res artemis [2] sus artemis [3] ls # check the artemis directory artemis \u003e 0 art::TTreeProjGroup ssd_test ssd_test 1 art::TAnalysisInfo analysisInfo cd [ID] : move to the directory of the ID artemis [4] cd 0 artemis [5] ls ssd_test \u003e 0 art::TH1FTreeProj ssd_energy ssd_energy 1 art::TH1FTreeProj ssd_timing ssd_timing 2 art::TH2FTreeProj ssd_energy and timing ssd_energy and timing ht [ID] [option] : draw the histogram of the ID artemis [6] ht 0 artemis [7] ht 2 colz hn : draw the next ID histogram hb : draw the prev ID histogram 4. Template hist file When setting up several detectors of the same type and wanting to set up a histogram with the same content, it is tedious to create several files with only the names of the objects changed. In such cases, it is useful to allow the histogram definition file to have arguments.\nPlease look here first.\n​ chkssd.yaml chkssd.yaml # -- snip -- - include: ssd/ssd_single.yaml # Histogram - name: projection_ssd type: art::TTreeProjectionProcessor parameter: FileName: hist/ssd/ssd.yaml Type: art::TTreeProjection OutputFilename: *histout Replace: | name: ssd_cal # -- snip -- We add the highlighted lines. Then the “name” can be used at hist file by @name@! The “name” can be freely set.\n​ hist/ssd/ssd.yaml hist/ssd/ssd.yaml anchor: - \u0026energy [\"@name@.fCharge\",100,0.,100.] - \u0026timing [\"@name@.fTiming\",100,0.,100.] alias: energy_cut: @name@.fCharge\u003e1.0; group: - name: ssd_test title: ssd_test contents: - name: ssd_energy title: ssd_energy x: *energy - name: ssd_timing title: ssd_timing x: *timing - name: ssd_energy and timing title: ssd_energy and timing x: *timing y: *energy cut: energy_cut This is useful when there are more objects to check!\n​ chkssd.yaml chkssd.yaml # -- snip -- - include: ssd/ssd_single.yaml # Histogram - name: projection_ssd type: art::TTreeProjectionProcessor parameter: FileName: hist/ssd/ssd.yaml Type: art::TTreeProjection OutputFilename: *histout Replace: | name: ssd_cal - name: projection_ssd type: art::TTreeProjectionProcessor parameter: FileName: hist/ssd/ssd.yaml Type: art::TTreeProjection Replace: | name: ssd_raw # and so on! # -- snip -- File splitting using “include” nodes, as described in the section on steeling, can also be used in the same way.\n",
    "description": "",
    "tags": [],
    "title": "Histograms",
    "uri": "/artemis_crib/setting/histograms/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-05 by Kodai Okawa Some CRIB-specific files use energy loss libraries. In particular, a library called SRIMlib has been developed by Okawa and some processors need to load this library.\ngit clone https://github.com/okawak/SRIMlib.git cd SRIMlib mkdir build cd build cmake .. make make installBefore using this library, you need to make database file (just .root file)\ncd .. source thisSRIMlib.sh updateIf you want to make energy loss figures, “f” option will work.\nupdate -fAlso, I recommend to write source thisSRIMlib.sh part in the .bashrc/.zshrc to load this library.\n",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "energyloss calculator",
    "uri": "/artemis_crib/installation/energyloss_calculator/index.html"
  },
  {
    "breadcrumb": "Setting",
    "content": "last modified: 2023-11-14 by Kodai Okawa need to consider…\n",
    "description": "",
    "tags": [],
    "title": "VNC server",
    "uri": "/artemis_crib/setting/vncserver/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-11-14 by Kodai Okawa With this command, all initial settings of “art_analysis” are made.\ncurl --proto '=https' --tlsv1.2 -sSf https://okawak.github.io/artemis_crib/bin/init.sh | shAfter that, please add the following lines to the .bashrc/.zshrc.\n​ .bashrc/.zshrc .bashrc/.zshrc # this is option source ${HOME}/Cern/root/root_install/bin/thisroot.sh \u0026\u003e /dev/null source ${HOME}/repos/artemis/install/bin/thisartemis.sh \u0026\u003e /dev/null source ${HOME}/repos/SRIMlib/thisSRIMlib.sh \u0026\u003e /dev/null # need from this line! export EXP_NAME=\"expname\" # your experiment export EXP_NAME_OLD=\"expname\" # this is option export PATH=\"${HOME}/art_analysis/bin:${PATH}\" source ${HOME}/art_analysis/bin/art_setting -q The setting is all!\nThen, the following commands (shellscript) will be downloaded.\nartlogin.sh This is loaded when you command artlogin. This command is described in the next chapter.\nartnew With this command, new artemis environment will be created interactively.\nart_setting This is like a library. The shellscript function artlogin, a etc. are written.\nart_check Checking these shellscript is updatable or not.\n",
    "description": "",
    "tags": [
      "CRIB",
      "unsettled"
    ],
    "title": "art_analysis",
    "uri": "/artemis_crib/installation/art_analysis/index.html"
  },
  {
    "breadcrumb": "Example",
    "content": "This section explain the example of preparation by using some useful macro.\n",
    "description": "",
    "tags": null,
    "title": "preparation",
    "uri": "/artemis_crib/example/preparation/index.html"
  },
  {
    "breadcrumb": "Example",
    "content": "This section explain the example of the online analysis in the CRIB experiment.\nCheck raw data ",
    "description": "",
    "tags": null,
    "title": "online_analysis",
    "uri": "/artemis_crib/example/online_analysis/index.html"
  },
  {
    "breadcrumb": "Example",
    "content": "This section explain the example of the offline analysis (some useful processors).\n",
    "description": "",
    "tags": null,
    "title": "offline_analysis",
    "uri": "/artemis_crib/example/offline_analysis/index.html"
  },
  {
    "breadcrumb": "Example",
    "content": "This section explain the example of the simulation by using artemis.\nBeam_generator Nbodyreaction Geometry Detect_particle Solidangle ",
    "description": "",
    "tags": null,
    "title": "Simulation",
    "uri": "/artemis_crib/example/simulation/index.html"
  },
  {
    "breadcrumb": "Example \u003e Simulation",
    "content": "last modified: 2023-09-29 by Kodai Okawa The previous sections have described how to loop events from a ridf file or root file, but now I will describe how to generate events to use as a simulation.\nRequirements:\nsrc-crib/simulation/TRandomBeamGenerator src-crib/simulation/TTreeBeamGenerator src-crib/simulation/TParticleInfo As you know, an “event store” must be used to analyse the event loop. For example, in the online analysis, we used TRIDFEventStore, and in the offline analysis, we used TTreeEventStore.\nBut when we want to simulate something, there are no data file. In that case, we can use TCounterEventStore or TRandomNumberEventStore.\nTCounterEventStore: generate numbers in sequence from 0 to N. TRandomNumberEventStore: generate number from 0.0 to 1.0 randomly. Here I will simply describe a simulation using TCounterEventStore.\nInfo As I explained in CRIB_parts before, in the current artemis version, the TCounterEventStore does not seem to be recognised as EventStore. So if we use this EventStore, “no event store” comments will output. I don’t think it makes problem, so it is okay comment out the part of TLoop.cc that prints “no event store”. (Possibly a problem with your environment).\n",
    "description": "",
    "tags": [],
    "title": "Beam_generator",
    "uri": "/artemis_crib/example/simulation/beam_generator/index.html"
  },
  {
    "breadcrumb": "Example \u003e Simulation",
    "content": "last modified: 2023-09-29 by Kodai Okawa ",
    "description": "",
    "tags": [],
    "title": "Nbodyreaction",
    "uri": "/artemis_crib/example/simulation/nbodyreaction/index.html"
  },
  {
    "breadcrumb": "Example \u003e Simulation",
    "content": "last modified: 2023-09-29 by Kodai Okawa In this page, I will explain how to determine the detecter geometry configration.\nRequirement:\nsrc-crib/geo/TUserGeoInitializer src-crib/geo/TDetectorParameter Firstly, let’s prepare the parameter file like this:\n​ prm/geo/example.yaml prm/geo/example.yaml material: - name: Vaccum # id=0 atomic_mass: 0.0 atomic_num: 0.0 density: 0.0 # g/cm3 - name: Si # id=1 atomic_mass: 28.084 atomic_num: 14.0 density: 2.321 # Note: beam axis -\u003e z, upper direction -\u003e y conposition: detector: - name: tel1 strip: [16, 16] center_rotation: [0., 0., 322.0] # mm offset: [0., 0., 0.] distance: 244.0 angle: -4.0 # deg thickness: [0.02, 0.301, 1.494, 1.486] material: [Si] - name: tel2 strip: [16, 16] center_rotation: [0., 0., 322.0] offset: [0., 0., 0.] distance: 154.5 angle: 27.0 thickness: [0.02, 0.300, 1.494, 1.485] material: [Si] volume: top: # detector world name: TOP type: box # now only box is available material: 0 size: [400.0, 200.0, 1288.0] # mm detector: - name: tel1 type: box material: 1 size: [50.0, 50.0, 1.0] # mm - name: tel2 type: box material: 1 size: [50.0, 50.0, 1.0] # mm There are many components to explain! The material node is used to define TGeoMaterial and TGeoMedium classes. (But they are not directly used.) From name to density node are used to make a instance of this object. This values are not used in the current processors.\nThe next conposition node define the detector configuration! General telescopes of the CRIB experiment consist of DSSSD and SSD (single-pad), and the node below defines the SSD of the telescope.\nname: Name of the telescope. For example tel1, tel2, and so on. strip: X x Y strip number. It is defined as an array like [16, 32], this means X:16 strips and Y:32 strips thickness: Thickness of the each layer. If there are two layer, the size of the array become two. You can add to any size. The unit is mm. material: material of the each layer. The string is used in SRIMlib calculation. This node is defined as a array for each layer, but if it is one, the same material is applied. For example, in example.yaml, [Si] means [Si, Si, Si, Si]. (You need to prepare SRIMlib setting beforehand!) Let’s move on to the geometry part! The node is center_rotation, offset, distance and angle. Please look at this figure.\nPlease not that the center_rotation and offset are defined in (x, y, z) coordinate (-\u003e [x, y, z]), but distance and angle is scalar value. The unit of length is mm, angle is deg.\nInfo The sign of the angle is defined as positive at this figure. And generally, we set z=0 at target position. (For the gas target, we set 0 at window position.)\nThe last part is volume node! In this parts, the shape of the detector will be defined by using TGeoVolume class. The TGeoVolume needs name, type, material and size. For the type, I only prepared “box”. (It means the code use only vol-\u003eMakeBox method.)\nThe first top node must be set because it defined “detector world”. Generally, the material is okay to set vaccum. And the material is defined in the material node, and the id (the order) can be used. So the format is like material: 0. And the size is generally set to the size of the scattering chamber, but for the safety, it is okay to set larger number. Also the unit is mm and format is (x, y, z).\nNext, at the volume/detector node, we can define the detector size. Please NOTE that the name should be the same with conposition/detector/name node.\nThen, let’s check if the parameter file can be correctly used! Please prepare the steering file.\n​ steering/geo_example.yaml steering/geo_example.yaml Anchor: Processor: - name: detector_initialize type: art::TUserGeoInitializer parameter: Name: prm_detector FileName: prm/geo/example.yaml OutputTransparency: 1 This steering file doesn’t use event loop. Just we want to check the parameter file works well or not.\nThen let’s see in the artemis!\nacd a -- snip -- artemis [0] add steering/geo_example.yaml -- snip -- artemis [1] ls artemis \u003e 0 TGeoVolume TOP Top volume artemis [2]The detector geometry object is successfully generated! In order to check the object, please use draw command for example. (It is defined only in CRIB artemis, to draw not only histogram object. This is under development.)\nartemis [2] draw 0 The red box is the TOP, and the black boxes are detectors. If the detector is placed where you expect it to be, the parameters have been successfully set!\nIn the event loop process, if you want to use the detector geometry information, you can use prm_detector in the steering files. I will explain the next session!\n",
    "description": "",
    "tags": [],
    "title": "Geometry",
    "uri": "/artemis_crib/example/simulation/geometry/index.html"
  },
  {
    "breadcrumb": "Example \u003e Simulation",
    "content": "last modified: 2023-09-29 by Kodai Okawa ",
    "description": "",
    "tags": [],
    "title": "Detect_particle",
    "uri": "/artemis_crib/example/simulation/detect_particle/index.html"
  },
  {
    "breadcrumb": "Example \u003e Simulation",
    "content": "last modified: 2023-09-29 by KodaiOkawa Beam_generator Nbodyreaction Geometry Detect_particle As an application of the above four sections, I would like to explain how to calculate solid angles using Monte Carlo methods!\n",
    "description": "",
    "tags": [],
    "title": "Solidangle",
    "uri": "/artemis_crib/example/simulation/solidangle/index.html"
  },
  {
    "breadcrumb": "Tags",
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tag :: CRIB",
    "uri": "/artemis_crib/tags/crib/index.html"
  },
  {
    "breadcrumb": "",
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tags",
    "uri": "/artemis_crib/tags/index.html"
  },
  {
    "breadcrumb": "Tags",
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tag :: data_class",
    "uri": "/artemis_crib/tags/data_class/index.html"
  },
  {
    "breadcrumb": "Tags",
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tag :: unsettled",
    "uri": "/artemis_crib/tags/unsettled/index.html"
  },
  {
    "breadcrumb": "",
    "content": "",
    "description": "",
    "tags": null,
    "title": "Categories",
    "uri": "/artemis_crib/categories/index.html"
  }
]
