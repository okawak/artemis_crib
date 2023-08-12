/**
 * @file   linkdef_user.h
 * @brief
 *
 * @date   Created:       2013-08-12 14:48:07
 *         Last Modified: Apr 16, 2015 04:19:02 JST (ota)
 * @author Shinsuke OTA <ota@cns.s.u-tokyo.ac.jp>
 *
 *    Copyright (C) 2013 KAWASE Shoichiro, OTA Shinsuke All rights reserved
 */
#ifndef LINKDEF_USER_H
#define LINKDEF_USER_H

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

//hist
#pragma link C++ class art::TH1FNormalTreeProj+;
#pragma link C++ class art::TH2FNormalTreeProj+;
#pragma link C++ class art::TH3FNormalTreeProj+;
#pragma link C++ class art::TNormalAttTreeProj+;
#pragma link C++ class art::TNormalTreeProjection+;
#pragma link C++ class art::TNormalTreeProjectionProcessor;

#endif // __CINT__

#endif // LINKDEF_USER_H
