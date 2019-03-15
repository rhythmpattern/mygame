#ifndef OPTIONS
#define OPTIONS
//-----------------------------------------------------------------------------
//
//  Name:   UserOptions.h
//
//  Author: Shaun Hose
//
//  Desc:   singleton class to control a number of menu options
//-----------------------------------------------------------------------------


#define Options UserOptions::Instance()

class UserOptions
{
private:

  UserOptions();

  //copy ctor and assignment should be private
  UserOptions(const UserOptions&);
  UserOptions& operator=(const UserOptions&);


public:

  static UserOptions* Instance();
  
  bool m_bShowGraph;

  bool m_bShowNodeIndices;

  bool m_bShowPathOfSelectedBot;

  bool m_bShowTargetOfSelectedBot;

  bool m_bShowOpponentsSensedBySelectedBot;

  bool m_bOnlyShowBotsInTargetsFOV;

  bool m_bShowGoalsOfSelectedBot;

  bool m_bShowGoalAppraisals;

  bool m_bShowWeaponAppraisals;

  bool m_bSmoothPathsQuick;
  bool m_bSmoothPathsPrecise;

  bool m_bShowBotIDs;

  bool m_bShowBotHealth;

  bool m_bShowScore;
};


#endif
