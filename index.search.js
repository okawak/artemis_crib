var relearn_search_index = [
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
    "content": "last modified: 2023-10-29 by Kodai Okawa The following machines have been tested for operation.\n1. Writer’s (Okawa’s) machine Almalinux 9.2 zsh 5.8 gcc 11.3.1 cmake 3.20.2 ROOT 6.28/04 yaml-cpp 0.7.0 2. CRIB’s analysis machine CentOS Linux release 7.9.2009 (Core) zsh 5.5.1 gcc 9.3.1 (using devtoolset-9) cmake 3.28 (install manually) ROOT 6.28/06 yaml-cpp 0.8.0 NOTE:\nFrom 2023/10, Ubuntu system is also avaliable. (issue48) Scripts for some automate operation are written in zsh format. ",
    "description": "",
    "tags": null,
    "title": "Requirements",
    "uri": "/artemis_crib/installation/requirements/index.html"
  },
  {
    "breadcrumb": "",
    "content": "This chapter describes how to set up the artemis environment for the CRIB experiment.\n",
    "description": "",
    "tags": null,
    "title": "Installation",
    "uri": "/artemis_crib/installation/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-29 by Kodai Okawa Generally, dnf install cmake or brew install cmake support latest version of the cmake, but for some older machine like CentOS 7, it is too old to install ROOT.\nThe latest ROOT require CMake 3.16 or higher, and if your system doesn’t support this version, you need to install manually.\nYou can get more information from here.\ngit clone https://github.com/Kitware/Cmake.git cd Cmake ./bootstrap make -j8 sudo make installIf you want to set the version, you can change the branch. The default branch is master.\n",
    "description": "",
    "tags": [],
    "title": "Cmake",
    "uri": "/artemis_crib/installation/cmake/index.html"
  },
  {
    "breadcrumb": "",
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Setting",
    "uri": "/artemis_crib/setting/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-29 by Kodai Okawa Artemis uses ROOT library.\nWe confirmed that version 6.28 of the ROOT will work well, but if the ROOT updates, we are not sure that the ARTEMIS will work well, so we recommend to build from the sources.\nFor detailded information, please refer Installing ROOT Recommendations are described below.\n# The latest stable branch gets updated automatically on each release. # You may update your local copy by issuing a `git pull` command from within `root_src/`. cd hoge # where you want to install ROOT git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git root_src mkdir root_build root_install \u0026\u0026 cd root_build cmake -DCMAKE_INSTALL_PREFIX=../root_install ../root_src # \u0026\u0026 check cmake configuration output for warnings or errors cmake --build . -- install -j4 # if you have 4 cores available for compilation source ../root_install/bin/thisroot.sh # or thisroot.{fish,csh}If there are any problems at the compile, additional packages may need to be installed. See also dependencies.\nInfo If errors related to xrootd, TBB and clad occur, the cmake options -Dxrootd=OFF, -Dimt=OFF and -Dclad=OFF may work respectively.\nsource thisroot.sh part will be written in thisartemis.sh (this is created after artemis installation), but before installing artemis, you need to type this once.\nafter completing the installation of the artemis, you don’t have to execute this command for each time.\n",
    "description": "",
    "tags": null,
    "title": "Root",
    "uri": "/artemis_crib/installation/root/index.html"
  },
  {
    "breadcrumb": "",
    "content": "Lorem Ipsum.\n",
    "description": "",
    "tags": null,
    "title": "Basic",
    "uri": "/artemis_crib/basic/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-29 by Kodai Okawa Current version of the artemis use yaml-cpp-0.7. If your package system (like apt or dnf) cannot install version 0.7, please install from the source.\nSee also Github repo and README of the artemis Please install it as a shared object like below commands.\ncd path/to/the/directory/you/want/to/install/yaml-cpp git clone https://github.com/jbeder/yaml-cpp.git cd yaml-cpp mkdir build \u0026\u0026 cd build cmake -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF .. make sudo make installDefault install path is /usr/local/lib or /usr/local/lib64. If you do not want to pollute the general environment, specify CMAKE_INSTALL_PREFIX and set PATH environment variable.\ncmake -DCMAKE_INSTALL_PREFIX=/foo/bar -DYAML_BUILD_SHARED_LIBS=ON -DBUILD_TESTING=OFF ..",
    "description": "",
    "tags": null,
    "title": "Yaml-cpp",
    "uri": "/artemis_crib/installation/yaml-cpp/index.html"
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
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-29 by Kodai Okawa From the current situation, CRIB experiment doesn’t use GET system, so we describe how to install it without linking it to GET decoder.\nAlso, it can link to openMPI, but the below commands assume not using openMPI. See artemis repo for more information.\ncd hoge git clone https://github.com/artemis-dev/artemis.git -b develop cd artemis mkdir build cd build cmake -DCMAKE_INSTALL_PREFIX=../install .. make -j8 make install source ../install/bin/thisartemis.shThen, \u003cCMAKE_INSTALL_PREFIX\u003e/bin/thisartemis.sh will be created and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.\n(It means you don’t have to write like export PATH=${yaml-cpp path}:$PATH or source thisroot.sh in .zshrc or .bashrc.)\nAnother option is to use module command to manage the environment. It is also written in artemis repo.\nNote This is 2023/10/29 current information\nOkawa think there is a grammatical error in the sources/main/thisartemis.sh.in, so I changed like:\n-if [ \"@BUILD_GET@\" == \"ON\" ]; then +if [[ \"@BUILD_GET@\" == \"ON\" ]]; then export LD_LIBRARY_PATH=@GET_LIB_DIR@:$LD_LIBRARY_PATH fi -if [ \"@MPI_CXX_FOUND@\" == \"TRUE\" ]; then +if [[ \"@MPI_CXX_FOUND@\" == \"TRUE\" ]]; then dir=@MPI_CXX_LIBRARIES@ libdir=\"$(dirname $dir)\" ",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "Artemis",
    "uri": "/artemis_crib/installation/artemis/index.html"
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
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-30 by Kodai Okawa For the convinience, we use one directory to store raw data (ridf files) and make symbolic link to each user work directory. So first, we need to make raw data directory.\nThere are three option to do so.\nuse the default SSD/HDD of analysis PC use the external SSD/HDD of analysis PC (need to mount it) use network file system (NFS) and mount it 1 and 2 options are mainly used for offline analysis, while 3 option is used for online analysis.\n1. use the default SSD/HDD of analysis PC If you have large size of main storage, the one option is easiest way. Just like:\ncd ~ mkdir data (or where you want to put) cd data rsync hoge (cp or scp to put the raw data)The symbolic link process will be done in the next process.\n2. use the external SSD/HDD of analysis PC (need to mount it) When your main storage is not so large, you may think to use external storage. For example, main storage is used for OS installation and external storage is used for experimental data. (I think this case is for personal analysis using your own PC.)\nIn that case, you need to do:\nmount the external storage check and set the file permission to be able to read or write it. The format and mount process is very depend on the situation, so please check the way in other place. One important point is that we have output root file when we start to analysis, so it may need to make the directory for outputed root files in the external storage.\n3. use network file system (NFS) and mount it For online analysis, the best option is to get the data via a file server, as there is no time to transfer the raw data files each time.\nThis is example of CRIB system.\n--- title: Network system of CRIB --- graph LR; A(MPV E7) --\u003e D{\u003cstrong\u003eDAQ main PC\u003c/strong\u003e\u003cbr\u003e\u003c/br\u003efile server} B(MPV1 J1) --\u003e D C(MPV2 J1) --\u003e D D --\u003e E[Analysis PC] As this figure, we use file server in the DAQ main PC.\n3.1 server setting The OS of the DAQ PC is CentOS7, but I think it can be applied for current OS. (like yum -\u003e dnf) First, please install required package.\nsudo yum install -y rpcbind nfs-utilsThen prepare the raw data file directory for sharing.\nmkdir /data (any location) And setting file for nfs is /etc/exports, and here is the example.\n/data 192.168.1.5 /data 192.168.2.0/24(rw)The first one means the host of 192.168.1.5 can access the shared directory “/data”. In the default setting, users cannot write to this directory.\nThe host of the second line means the range that can access. If we add rw option, users can write to this directory. For the other options, please check the official site.\nFinally, the following command is used to reflect the settings.\nfirewall-cmd --permanent --zone=public --add-service=nfs firewall-cmd --reload systemctl start rpcbind systemctl enable rpcbind systemctl start nfs systemctl enable nfsIf you do not have a firewall set up, you do not need the relevant commands.\n3.2 client setting The package is also needed for client PC.\nsudo yum install -y nfs-utilsPrepare the mounted directory and mount it.\nmkdir /mnt/data sudo mount -t nfs host_IP_address:/data /mnt/data df -hIf you see the mounted configuration, your nfs configuration is complete.\nTo reflect the mount settings when the system is rebooted, add a setting to /etc/fstab.\n​ /etc/fstab /etc/fstab + host_IP_address:/data /mnt/data nfs defaults 0 0 sudo mount -a",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "Mount setting",
    "uri": "/artemis_crib/installation/mount/index.html"
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
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-30 by Kodai Okawa Some CRIB-specific files use energy loss libraries. In particular, a library called SRIMlib has been developed by Okawa and contains settings to load this library.\ngit clone https://github.com/okawak/SRIMlib.git cd SRIMlib mkdir build cd build cmake .. make make installBefore using this library, you need to make database file (just .root file)\ncd .. source thisSRIMlib.sh updateIf you want to make energy loss figures, “f” option will work.\nupdate -f",
    "description": "",
    "tags": [
      "CRIB"
    ],
    "title": "Energyloss_calculator",
    "uri": "/artemis_crib/installation/energyloss_calculator/index.html"
  },
  {
    "breadcrumb": "Installation",
    "content": "last modified: 2023-10-30 by Kodai Okawa With this command, all settings are made interactively.\ncurl --proto '=https' --tlsv1.2 -sSf https://okawak.github.io/artemis_crib/installation/init.sh | sh",
    "description": "",
    "tags": [
      "CRIB",
      "unsettled"
    ],
    "title": "Art_analysis",
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
    "content": "This section explain the example of the online analysis in the CRIB experiment.\n",
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
    "title": "Tag :: data_class",
    "uri": "/artemis_crib/tags/data_class/index.html"
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
    "title": "Tag :: CRIB",
    "uri": "/artemis_crib/tags/crib/index.html"
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
