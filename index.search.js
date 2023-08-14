var relearn_search_index = [
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
    "content": "From the current situation, CRIB experiment doesn’t use GET system, so we describe how to install it without linking it to GET decoder.\nAlso, it can link to openMPI, but the below commands assume not using openMPI. See artemis repo for more information.\ncd hoge git clone https://github.com/artemis-dev/artemis.git -b develop cd artemis mkdir build cd build cmake -DCMAKE_INSTALL_PREFIX=../install .. make -j8 make installThen, \u003cCMAKE_INSTALL_PREFIX\u003e/bin/thisartemis.sh will be created and this shell script can configure the environment (ROOT, yaml-cpp, artemis libraries) to use artemis.\n(It means you don’t have to write like export PATH=${yaml-cpp path}:$PATH or source thisroot.sh in .zshrc or .bashrc.)\nAnother option is to use module command to manage the environment. It is also written in artemis repo.\nThe following methods are not recommended!!\nFor Ubuntu case, somehow it seems that there are some linking problem.\nTo avoid it, if I changed like below, the artemis will work well…\n[Mod] artemis/sources/main/CMakeLists.txt - add_executable(artemis main.cc TArtRint.cc) + add_executable(artemis main.cc dummy.cc TArtRint.cc) [Add] artemis/sources/main/dummy.cc #include \u003cTModuleDecoderV1190.h\u003e #include \u003cTParameterLoader.h\u003e #include \u003cTTreeProjection.h\u003e #include \u003cTRDFEventStore.h\u003e #include \u003cTRIDFEventStore.h\u003e // any class seems okay void dummy() { art::TModuleDecoderV1190 *dummy_decoder = new art::TModuleDecoderV1190(); art::TParameterLoader *dummy_param = new art::TParameterLoader(); art::TTreeProjection *dummy_hist = new art::TTreeProjection(); art::TRDFEventStore *dummy_rdf = new art::TRDFEventStore(); art::TRIDFEventStore *dummy_ridf = new art::TRIDFEventStore(); }Libraries that are not directly involved in the artemis executable do not seem to be linked, despite using target_link_library(hoge) in CMakeLists.txt.\n",
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
    "content": "",
    "description": "",
    "tags": null,
    "title": "Directory",
    "uri": "/artemis_crib/installation/directory/index.html"
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
    "title": "Tag :: environment",
    "uri": "/artemis_crib/tags/environment/index.html"
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
    "title": "Categories",
    "uri": "/artemis_crib/categories/index.html"
  }
]
