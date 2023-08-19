var relearn_search_index = [
  {
    "content": "under develop (possibly we will update this data class)\nTTelescopeData Data members TVector3 fPos; // detected position (x, y, z) // simulation: actual position // from data: calculated from strip ID Int_t fXID; // X strip ID Int_t fYID; // Y strip ID Double_t fdE; // total energy deposit of dE detector Double_t fE; // total energy deposit of E detector Double_t fEtotal; // total energy deposit of the telescope DoubleVec_t fEnergyArray; // energy array of all the telescope // DoubleVec_t fTimingArray; // not impremented //=============================================================== // no need?? // kMAXNPARAMETER = 4 (can be settable) Int_t fNE; // number of thick E detector Double_t fdEX; // energy of the first dE detector Double_t fdEY; // energy of the seconde dE detector Double_t fdEXTiming; // timing of the first dE detector Double_t fdEYTiming; // timing of the second dE detector Double_t fEvec[kMAXNPARAMETER]; // energy array of the E detector Double_t fETimingvec[kMAXNPARAMETER]; // timing array of the E detector Methods TVector3 GetPosition() const { return fPos; } void SetPosition(TVector3 vec) { fPos = vec; } void SetPosition(Double_t x, Double_t y, Double_t z) { fPos.SetXYZ(x, y, z); } Int_t GetXID() const {return fXID;} void SetXID(Int_t arg) { fXID = arg; } Int_t GetYID() const {return fYID;} void SetYID(Int_t arg) { fYID = arg; } Double_t GetdEX() const {return fdEX;} void SetdEX(Double_t arg) { fdEX = arg; } Double_t GetdEY() const {return fdEY;} void SetdEY(Double_t arg) { fdEY = arg; } Double_t GetdEXTiming() const {return fdEXTiming;} void SetdEXTiming(Double_t arg) { fdEXTiming = arg; } Double_t GetdEYTiming() const {return fdEYTiming;} void SetdEYTiming(Double_t arg) { fdEYTiming = arg; } Double_t GetEvec(Int_t idx) const { return fEvec[idx]; } void SetEvec(Int_t idx, Double_t val) { fEvec[idx] = val; } Int_t GetEvecSize() { return fNE; } Double_t GetETimingvec(Int_t idx) const { return fETimingvec[idx]; } void SetETimingvec(Int_t idx, Double_t val) { fETimingvec[idx] = val; } Double_t GetdE() const {return fdE;} void SetdE(Double_t arg) { fdE = arg; } Double_t GetE() const {return fE;} void SetE(Double_t arg) { fE = arg; } Double_t GetEtotal() const {return fEtotal;} void SetEtotal(Double_t arg) { fEtotal = arg; } DoubleVec_t GetEnergyArray() const {return fEnergyArray;} void SetEnergyArray(Double_t arg) { fEnergyArray.emplace_back(arg); }",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TTelescopeData",
    "uri": "/artemis_crib/processors/telescope/ttelescopedata/index.html"
  },
  {
    "content": "TReactionInfo Data member // center of the mass system Double_t fEnergy; // kinetic energy Double_t fTheta; // theta Double_t fPhi; // phi // reaction position Double_t fX; Double_t fY; Double_t fZ; // if you define excited statas, the information stored this value Int_t fExcitedID; Methods Double_t GetEnergy() const { return fEnergy; } void SetEnergy(Double_t arg) { fEnergy = arg; } Double_t GetTheta() const { return fTheta; } void SetTheta(Double_t arg) { fTheta = arg; } Double_t GetPhi() const { return fPhi; } void SetPhi(Double_t arg) { fPhi = arg; } Double_t GetX() const { return fX; } Double_t GetY() const { return fY; } Double_t GetZ() const { return fZ; } void SetXYZ(Double_t x, Double_t y, Double_t z) { fX = x; fY = y; fZ = z; } Int_t GetExID() const { return fExcitedID; } void SetExID(Int_t arg) { fExcitedID = arg; }",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TReactionInfo",
    "uri": "/artemis_crib/processors/simulation/treactioninfo/index.html"
  },
  {
    "content": "TParticleInfo Data member ​ TParticleInfo.cc TParticleInfo.cc 1Int_t fMassNumber; // A: particle mass number 2Int_t fAtomicNumber; // Z: particle atomic number 3Int_t fCharge; // Q: particle charge 4 5Double_t fCurrentZ; // particle z position 6Double_t fEnergy; // particle \"kinetic\" energy 7 8TTrack fTrack; // tracking information 9TLorentzVector fVec; // relativistic momentum and energy Method (Getter and Setter) ​ TParticleInfo.cc TParticleInfo.cc 1void SetMassNumber(Int_t val) { fMassNumber = val; } 2Int_t GetMassNumber() const { return fMassNumber; } 3void SetAtomicNumber(Int_t val) { fAtomicNumber = val; } 4Int_t GetAtomicNumber() const { return fAtomicNumber; } 5void SetCharge(Int_t val) { fCharge = val; } 6Int_t GetCharge() const { return fCharge; } 7 8void SetCurrentZ(Double_t val) { fCurrentZ = val; } 9Double_t GetCurrentZ() const { return fCurrentZ; } 10void SetEnergy(Double_t val) { fEnergy = val; } 11Double_t GetEnergy() const { return fEnergy; } 12 13void SetLorentzVector(Double_t x, Double_t y, Double_t z, Double_t t) { fVec.SetXYZT(x, y, z, t); } 14void SetLorentzVector(TLorentzVector val) { fVec = val; } 15TLorentzVector GetLorentzVector() const { return fVec; } 16 17void SetTrack(Double_t x, Double_t y, Double_t z, Double_t a, Double_t b) 18{ 19 fTrack.SetPos(x, y, z); 20 fTrack.SetAngle(a, b); 21} 22TTrack GetTrack() const { return fTrack; } ",
    "description": "",
    "tags": [
      "data_class"
    ],
    "title": "TParticleInfo",
    "uri": "/artemis_crib/processors/simulation/tparticleinfo/index.html"
  },
  {
    "content": "This chapter describes how to set up the artemis environment for the CRIB experiment.\n",
    "description": "",
    "tags": null,
    "title": "Installation",
    "uri": "/artemis_crib/installation/index.html"
  },
  {
    "content": "The following machines have been tested for operation.\nAlmalinux 9.2 zsh 5.8 gcc 11.3.1 cmake 3.20.2 ROOT 6.28/04 yaml-cpp 0.7.0 Scripts for some automate operation are written in zsh format.\nAs for the Ubuntu 22.04 (LTS), there appeared to be a linking problem and a dummy file had to be set up to force the link.\n",
    "description": "",
    "tags": "environment",
    "title": "Requirements",
    "uri": "/artemis_crib/installation/requirements/index.html"
  },
  {
    "content": "Artemis uses ROOT library.\nWe confirmed that version 6.28 of the ROOT will work well, but if the ROOT updates, we are not sure that the ARTEMIS will work well, so we recommend to build from the sources.\nFor detailded information, please refer Installing ROOT Recommendations are described below.\n# The latest stable branch gets updated automatically on each release. # You may update your local copy by issuing a `git pull` command from within `root_src/`. cd hoge # where you want to install ROOT git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src mkdir root_build root_install \u0026\u0026 cd root_build cmake -DCMAKE_INSTALL_PREFIX=../root_install ../root_src # \u0026\u0026 check cmake configuration output for warnings or errors cmake --build . -- install -j4 # if you have 4 cores available for compilation source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}If there are any problems at the compile, additional packages may need to be installed. See also dependencies.\nsource thisroot.sh part will be written in thisartemis.sh (this is created after artemis installation), so you don’t have to execute this command for each time.\n",
    "description": "",
    "tags": null,
    "title": "Root",
    "uri": "/artemis_crib/installation/root/index.html"
  },
  {
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Setting",
    "uri": "/artemis_crib/setting/index.html"
  },
  {
    "content": "Current version of the artemis use yaml-cpp-0.7. If your package system (like apt or dnf) cannot install version 0.7, please install from the source.\nSee also Github repo and README of the artemis Please install it as a shared object like below commands.\ncd path/to/the/directory/you/want/to/install/yaml-cpp git clone https://github.com/jbeder/yaml-cpp.git cd yaml-cpp mkdir build \u0026\u0026 cd build cmake -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF .. make sudo make installDefault install path is /usr/local/lib or /usr/local/lib64. If you do not want to pollute the general environment, specify CMAKE_INSTALL_PREFIX and set PATH environment variable.\ncmake -DCMAKE_INSTALL_PREFIX=/foo/bar -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..",
    "description": "",
    "tags": null,
    "title": "Yaml-cpp",
    "uri": "/artemis_crib/installation/yaml-cpp/index.html"
  },
  {
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Basic",
    "uri": "/artemis_crib/basic/index.html"
  },
  {
    "content": " WarningNot recommended From the current situation, CRIB experiment doesn’t use GET system, so we describe how to install it without linking it to GET decoder.\nAlso, it can link to openMPI, but the below commands assume not using openMPI. See artemis repo for more information.\ncd hoge git clone https://github.com/artemis-dev/artemis.git -b develop cd artemis mkdir build cd build cmake -DCMAKE_INSTALL_PREFIX=../install .. make -j8 make installThen, \u003cCMAKE_INSTALL_PREFIX\u003e/bin/thisartemis.sh will be created and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.\n(It means you don’t have to write like export PATH=${yaml-cpp path}:$PATH or source thisroot.sh in .zshrc or .bashrc.)\nAnother option is to use module command to manage the environment. It is also written in artemis repo.\nThe following methods are not recommended!!\nFor Ubuntu case, somehow it seems that there are some linking problem.\nTo avoid it, if I changed like below, the artemis will work well…\n[Mod] artemis/sources/main/CMakeLists.txt - add_executable(artemis main.cc TArtRint.cc) + add_executable(artemis main.cc dummy.cc TArtRint.cc) [Add] artemis/sources/main/dummy.cc #include \u003cTModuleDecoderV1190.h\u003e #include \u003cTParameterLoader.h\u003e #include \u003cTTreeProjection.h\u003e #include \u003cTRDFEventStore.h\u003e #include \u003cTRIDFEventStore.h\u003e // any class seems okay void dummy() { art::TModuleDecoderV1190 *dummy_decoder = new art::TModuleDecoderV1190(); art::TParameterLoader *dummy_param = new art::TParameterLoader(); art::TTreeProjection *dummy_hist = new art::TTreeProjection(); art::TRDFEventStore *dummy_rdf = new art::TRDFEventStore(); art::TRIDFEventStore *dummy_ridf = new art::TRIDFEventStore(); }Libraries that are not directly involved in the artemis executable do not seem to be linked, despite using target_link_library(hoge) in CMakeLists.txt.\n",
    "description": "",
    "tags": null,
    "title": "Artemis",
    "uri": "/artemis_crib/installation/artemis/index.html"
  },
  {
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "CRIB_parts",
    "uri": "/artemis_crib/crib_parts/index.html"
  },
  {
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Processors",
    "uri": "/artemis_crib/processors/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Directory",
    "uri": "/artemis_crib/installation/directory/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Art_analysis",
    "uri": "/artemis_crib/installation/art_analysis/index.html"
  },
  {
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Example",
    "uri": "/artemis_crib/example/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Energyloss_calculator",
    "uri": "/artemis_crib/installation/energyloss_calculator/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tag :: data_class",
    "uri": "/artemis_crib/tags/data_class/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tags",
    "uri": "/artemis_crib/tags/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Tag :: environment",
    "uri": "/artemis_crib/tags/environment/index.html"
  },
  {
    "content": "",
    "description": "",
    "tags": null,
    "title": "Categories",
    "uri": "/artemis_crib/categories/index.html"
  }
]
