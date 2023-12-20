/*
   @File name     : TUserGeoInitializer.cc
   @description   :
   @Author        : Kodai Okawa<okawa@cns.s.u-tokyo.ac.jp>
   @Created date  : 2023-08-01 11:02:18
   @Last modified : 2023-12-19 14:14:06
*/

#include "TUserGeoInitializer.h"
#include "TDetectorParameter.h"
#include <TArtTypes.h>
#include <TGeoMaterial.h>
#include <TGeoMatrix.h>
#include <TGeoMedium.h>

#include <yaml-cpp/yaml.h>

#include <TDirectory.h>
#include <TGeoManager.h>
#include <TSystem.h>
#include <TVector3.h>

using art::TUserGeoInitializer;

ClassImp(art::TUserGeoInitializer);

// definition of constant strings for the key of each node
namespace {
const char *kNodeKeyMaterial = "material";
const char *kNodeKeyConposition = "conposition";
const char *kNodeKeyVolume = "volume";
const char *kNodeKeyName = "name";
const char *kNodeKeyAMass = "atomic_mass";
const char *kNodeKeyANum = "atomic_num";
const char *kNodeKeyDensity = "density";
const char *kNodeKeyThickness = "thickness";
const char *kNodeKeyCenterRot = "center_rotation";
const char *kNodeKeyDistance = "distance";
const char *kNodeKeyAngle = "angle";
const char *kNodeKeyTop = "top";
const char *kNodeKeyDetector = "detector";
const char *kNodeKeyTrackDetector = "tracking_detector"; // not yet
const char *kNodeKeyTarget = "target";                   // not yet
const char *kNodeKeyType = "type";
const char *kNodeKeySize = "size";
const char *kNodeKeyOffset = "offset";
const char *kNodeKeyStrip = "strip";
} // namespace

TUserGeoInitializer::TUserGeoInitializer() : fGeom(NULL) {
    RegisterProcessorParameter("Name", "parameter name", fPrmName, TString(""));
    RegisterProcessorParameter("FileName", "parameter file of detector geometry", fFileName, TString(""));
}

TUserGeoInitializer::~TUserGeoInitializer() {
    delete fGeom;
    delete fParameterArray;
}

void TUserGeoInitializer::Init(TEventCollection *col) {
    Info("Init", "geometry parameter is loaded from %s", fFileName.Data());
    if (gGeoManager)
        delete gGeoManager;
    fGeom = new TGeoManager("geometry", "Detector Geometry");

    Info("Init", "detector parameters are produced to %s", fPrmName.Data());
    fParameterArray = new TClonesArray("art::TDetectorParameter");

    GeometryFromYaml(fFileName);

    col->Add("geom", fGeom, fOutputIsTransparent);

    fParameterArray->SetName(fPrmName);
    col->AddInfo(fPrmName, fParameterArray, fOutputIsTransparent);
}

void TUserGeoInitializer::Process() {}

void TUserGeoInitializer::GeometryFromYaml(TString yamlfile) {
    FileStat_t info;
    if (gSystem->GetPathInfo(yamlfile.Data(), info) != 0) {
        SetStateError(Form("File %s does not exist.", yamlfile.Data()));
        return;
    }

    YAML::Node yaml_all = YAML::LoadFile(yamlfile.Data());

#if 0
  YAML::Emitter emitter;
  emitter << yaml_all;
  std::cout << emitter.c_str() << std::endl;
  std::cout << yaml_all.size() << std::endl;
#endif

    // TGeo material setting
    YAML::Node yaml_mat = yaml_all[kNodeKeyMaterial].as<YAML::Node>();
    std::vector<TGeoMaterial *> mat_vec;
    std::vector<TGeoMedium *> med_vec;
    for (Int_t i = 0; i < yaml_mat.size(); i++) {
        TString name = yaml_mat[i][kNodeKeyName].as<std::string>();
        Double_t atm_mass = yaml_mat[i][kNodeKeyAMass].as<double>();
        Double_t atm_num = yaml_mat[i][kNodeKeyANum].as<double>();
        Double_t density = yaml_mat[i][kNodeKeyDensity].as<double>();
        mat_vec.emplace_back(new TGeoMaterial(name.Data(), atm_mass, atm_num, density));
        med_vec.emplace_back(new TGeoMedium(name.Data(), i + 1, mat_vec[mat_vec.size() - 1]));
    }

    // TGeo top setting
    YAML::Node yaml_top = yaml_all[kNodeKeyVolume][kNodeKeyTop].as<YAML::Node>();
    TString top_name = yaml_top[kNodeKeyName].as<std::string>();
    Int_t top_mat_id = yaml_top[kNodeKeyMaterial].as<int>();
    DoubleVec_t top_size = yaml_top[kNodeKeySize].as<std::vector<double>>();
    if (top_size.size() != 3) {
        SetStateError("input yaml error");
        return;
    }

    TGeoVolume *top =
        fGeom->MakeBox(top_name.Data(), med_vec[top_mat_id], top_size[0] / 2., top_size[1] / 2., top_size[2] / 2.);
    fGeom->SetTopVolume(top);

    // TGeo detector setting
    YAML::Node yaml_prm = yaml_all[kNodeKeyConposition][kNodeKeyDetector].as<YAML::Node>();
    YAML::Node yaml_det = yaml_all[kNodeKeyVolume][kNodeKeyDetector].as<YAML::Node>();
    if (yaml_prm.size() != yaml_det.size()) {
        SetStateError("in yaml, conposition number and detector number is different");
        return;
    }

    for (Int_t i = 0; i < yaml_det.size(); i++) {
        if (yaml_prm[i][kNodeKeyName].as<std::string>() != yaml_det[i][kNodeKeyName].as<std::string>()) {
            SetStateError("in yaml, set same order for composition and detector");
            return;
        }
        TString det_name = yaml_det[i][kNodeKeyName].as<std::string>();
        Int_t det_mat_id = yaml_det[i][kNodeKeyMaterial].as<int>();
        DoubleVec_t det_size = yaml_det[i][kNodeKeySize].as<std::vector<double>>();
        if (det_size.size() != 3) {
            SetStateError("input yaml error");
            return;
        }

        TGeoVolume *det =
            fGeom->MakeBox(det_name.Data(), med_vec[det_mat_id], det_size[0] / 2., det_size[1] / 2., det_size[2] / 2.);
        DoubleVec_t rot_point = yaml_prm[i][kNodeKeyCenterRot].as<std::vector<double>>();
        DoubleVec_t offset = yaml_prm[i][kNodeKeyOffset].as<std::vector<double>>();
        IntVec_t det_strip = yaml_prm[i][kNodeKeyStrip].as<std::vector<int>>();
        if (rot_point.size() != 3 || offset.size() != 3 || det_strip.size() != 2) {
            SetStateError("input yaml error");
            return;
        }
        Double_t distance = yaml_prm[i][kNodeKeyDistance].as<double>();
        Double_t angle = yaml_prm[i][kNodeKeyAngle].as<double>() * deg2rad;

        TVector3 det_pos(offset[0], offset[1], distance + offset[2]);
        det_pos.RotateY(angle);
        TVector3 rot_point_vec(rot_point[0], rot_point[1], rot_point[2]);
        det_pos += rot_point_vec;

        TGeoCombiTrans *det_trans =
            new TGeoCombiTrans(det_pos.X(), det_pos.Y(), det_pos.Z(), new TGeoRotation("rot", 90.0, angle / deg2rad, 0.0));
        top->AddNode(det, i, det_trans);

        // parameter input
        TDetectorParameter *prm = static_cast<TDetectorParameter *>(fParameterArray->ConstructedAt(i));
        DoubleVec_t thickness = yaml_prm[i][kNodeKeyThickness].as<std::vector<double>>();
        std::vector<std::string> material = yaml_prm[i][kNodeKeyMaterial].as<std::vector<std::string>>();
        StringVec_t material_vec;
        for (Int_t j = 0; j < thickness.size(); j++) {
            if (material.size() == 1) {
                material_vec.emplace_back(material[0]);
            } else if (material.size() == thickness.size()) {
                material_vec.emplace_back(material[j]);
            } else {
                SetStateError("input yaml error");
                return;
            }
        }

        if (thickness.size() != material_vec.size()) {
            SetStateError("system error");
            return;
        }

        prm->SetMaxRadius(top_size[2]);
        prm->SetMaterial(material_vec);
        prm->SetThickness(thickness);
        prm->SetCenterRotPos(rot_point);
        prm->SetOffset(offset);
        prm->SetDistance(distance);
        prm->SetAngle(angle); // radian
        prm->SetSize(det_size);
        prm->SetStripNum(det_strip);
    }

    fGeom->CloseGeometry();
    fGeom->SetTopVisible();
    top->SetLineColor(kRed);

    gDirectory->Add(top);
}
