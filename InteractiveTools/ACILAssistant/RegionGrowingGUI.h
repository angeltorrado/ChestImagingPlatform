// generated by Fast Light User Interface Designer (fluid) version 1.0302

#ifndef RegionGrowingGUI_h
#define RegionGrowingGUI_h
#include <FL/Fl.H>
#include <vector>
using namespace std;
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Spinner.H>

class RegionGrowingGUI {
public:
  RegionGrowingGUI();
  Fl_Double_Window *regionGrowingWindow;
  Fl_Group *thresholdsGroup;
  Fl_Value_Input *minThresholdInput;
  Fl_Value_Input *maxThresholdInput;
  Fl_Choice *chestRegionChoice;
  Fl_Choice *chestTypeChoice;
  Fl_Spinner *roiRadiusSpinner;
  unsigned char GetChestRegion();
  unsigned char GetChestType();
  unsigned int GetROIRadius();
private:
  unsigned char m_ChestRegion; 
  unsigned char m_ChestType; 
public:
  short GetMinThreshold();
  short GetMaxThreshold();
private:
  static void undefinedRegionMenuItem_CB( Fl_Widget* o, void* v );
  void undefinedRegionMenuItem_CB_i();
  static void wholeLungMenuItem_CB( Fl_Widget* o, void* v );
  void wholeLungMenuItem_CB_i();
  static void airwayMenuItem_CB( Fl_Widget* o, void* v );
  void airwayMenuItem_CB_i();
};
#endif