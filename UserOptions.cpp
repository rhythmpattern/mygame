#include "UserOptions.h"

 
UserOptions* UserOptions::Instance()
{
  static UserOptions instance; 
  return &instance;
}

UserOptions::UserOptions():m_bShowGraph(false),
                      m_bShowPathOfSelectedBot(true),
                      m_bSmoothPathsQuick(false),
                      m_bSmoothPathsPrecise(false),
                      m_bShowBotIDs(false),
                      m_bShowBotHealth(true),
                      m_bShowTargetOfSelectedBot(false),
                      m_bOnlyShowBotsInTargetsFOV(false),
                      m_bShowScore(false),
                      m_bShowGoalsOfSelectedBot(true),
                      m_bShowGoalAppraisals(true),
                      m_bShowNodeIndices(false),
                      m_bShowOpponentsSensedBySelectedBot(true),
                      m_bShowWeaponAppraisals(false)
{}
