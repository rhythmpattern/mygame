#include "GraveManager.h"
#include "Scriptor.h"

GraveManager* GraveManager::pInstance = 0;

void GraveManager::Clear()
{
  delete m_pGraveMarkers;
}

void GraveManager::Update()
{
  m_pGraveMarkers->Update();
}

void GraveManager::Render()
{
  m_pGraveMarkers->Render();
}

void GraveManager::AddGrave(Vector2D pos)
{
  m_pGraveMarkers->AddGrave(pos);
}

void GraveManager::load()
{
  Clear();
  m_pGraveMarkers = new GraveMarkers(script->getNum("gravelifetime"));
}
